#include <myselfc.h>

typedef int Element;

typedef struct linked_node_s{
    Element data;
    struct linked_node_s *next;
}LinkedNode;

typedef struct{
    LinkedNode *head;
}LinkedList;

LinkedList* linkedlist_create(void){
    LinkedList* head = (LinkedList *)calloc(1, sizeof(LinkedList));
    if(head == NULL){
        exit(1);
    }
    return head;
}

void linkedlist_destroy(LinkedList *list){
    LinkedNode *current = list->head;

    while(current != NULL){
        LinkedNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void linkedlist_insert_before_haed(LinkedList *list, Element data){
    LinkedNode *new_node = (LinkedNode *)malloc(sizeof(LinkedNode));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
}

void linkedlist_print(const LinkedList *list){
    LinkedNode *current = list->head;

    while(current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}



void *routine(void *arg){
    LinkedList *list = (LinkedList *)arg;

    linkedlist_print(list);


    pthread_exit(NULL);
}


int main(void){

    LinkedList *my_list = linkedlist_create();
    for(int i = 0; i < 5; ++i){
        linkedlist_insert_before_haed(my_list, i);
    }

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, routine, (void *)my_list);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    sleep(5);

    pthread_join(tid, NULL);
    linkedlist_destroy(my_list);
    return 0;
}
