#include <myselfc.h>
#include <stdbool.h>

#define QUEUE_INIT_SIZE 8
#define QUEUE_MAX_SIZE 10
#define PRODUCER_NUMS 3
#define CONSUMER_NUMS 2

typedef int Element;


typedef struct queue_node_s{
    Element data;
    struct queue_node_s *next;
}QueueNode;

typedef struct{
    QueueNode *front;
    QueueNode *rear;
    int size;
}Queue;

typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Queue *queue;
    int *routines_id;
    int routine_id_index;
}SharedRes;

Queue *queue_create(void){
    return (Queue *)calloc(1, sizeof(Queue));
}

void queue_destroy(Queue *queue){
    QueueNode *current = queue->front;
    while(current != NULL){
        QueueNode *next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}

bool queue_is_empty(const Queue *queue){
    return queue->front == NULL;
}

Element enqueue(Queue *queue){
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    new_node->data = rand() % 100;
    new_node->next = NULL;
    if(queue_is_empty(queue)){
        queue->front = new_node;
    }
    else{
        queue->rear->next = new_node;
    }
    queue->rear = new_node;
    queue->size++;

    return new_node->data;
}

Element dequeue(Queue *queue){
    ERROR_CHECK(queue_is_empty(queue), true, "Error: Failed to dequeue cause queue was empty!\n");

    QueueNode *deleted_node = queue->front;
    Element data = deleted_node->data;
    queue->front = deleted_node->next;
    if(queue->front == NULL){
        queue->rear = NULL;
    }

    free(deleted_node);

    queue->size--;
    return data;
}

int *routine_id_init(void){
    int total_routines = PRODUCER_NUMS + CONSUMER_NUMS;

    int *routines_id = (int *)malloc(total_routines * sizeof(int));

    for(int i = 0; i < PRODUCER_NUMS; ++i){
        routines_id[i] = i + 1;
    }

    for(int i = PRODUCER_NUMS; i < total_routines; ++i){
        routines_id[i] = i - PRODUCER_NUMS + 1;
    }

    return routines_id;
}

SharedRes *shared_res_init(void){
    SharedRes *pshared_res = (SharedRes *)malloc(sizeof(SharedRes));
    int ret;
    ret = pthread_mutex_init(&pshared_res->mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&pshared_res->cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");

    pshared_res->routines_id = routine_id_init();
    pshared_res->routine_id_index = 0;

    Queue *queue = queue_create();
    for(int i = 0; i < QUEUE_INIT_SIZE; ++i){
        enqueue(queue);
    }

    pshared_res->queue = queue;
    return pshared_res;
}

void shared_res_destroy(SharedRes *pshared_res){
    pthread_mutex_destroy(&pshared_res->mutex);
    pthread_cond_destroy(&pshared_res->cond);
    queue_destroy(pshared_res->queue);
    free(pshared_res->routines_id);
}

void queue_display(const Queue *queue){
    QueueNode *current = queue->front;
    while(current != NULL){
        printf("%02d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

void *routine_producer(void *arg){
    SharedRes *pshared_res = (SharedRes *)arg;

    pthread_mutex_lock(&pshared_res->mutex);
    int current_id = pshared_res->routines_id[pshared_res->routine_id_index++];
    pthread_cond_broadcast(&pshared_res->cond);
    pthread_mutex_unlock(&pshared_res->mutex);


    while(1){
        sleep(3);
        pthread_mutex_lock(&pshared_res->mutex);
        while(pshared_res->queue->size == QUEUE_MAX_SIZE){
            pthread_cond_wait(&pshared_res->cond, &pshared_res->mutex);
        }
        printf("Before producer%d generate, product nums = %d\n", current_id, pshared_res->queue->size);
        printf("Current queue: ");
        queue_display(pshared_res->queue);
        Element product_id = enqueue(pshared_res->queue);
        printf(" After producer%d generate, product nums = %d, new product's id = %d\n", current_id, pshared_res->queue->size, product_id);
        printf("Current queue: ");
        queue_display(pshared_res->queue);
        printf("\n");
        pthread_cond_broadcast(&pshared_res->cond);
        pthread_mutex_unlock(&pshared_res->mutex);
    }
   pthread_exit(NULL); 
}

void *routine_consumer(void *arg){
    SharedRes *pshared_res = (SharedRes *)arg;
    pthread_mutex_lock(&pshared_res->mutex);
    int current_id = pshared_res->routines_id[pshared_res->routine_id_index++];
    pthread_mutex_unlock(&pshared_res->mutex);
    
    sleep(5);
    while(1){
        pthread_mutex_lock(&pshared_res->mutex);
        while(queue_is_empty(pshared_res->queue)){
            pthread_cond_wait(&pshared_res->cond, &pshared_res->mutex);
        }
        printf("Before consumer%d consume, product nums = %d\n", current_id, pshared_res->queue->size);
        printf("Current queue: ");
        queue_display(pshared_res->queue);
        Element product_id = dequeue(pshared_res->queue);
        printf(" After consumer%d consume, product nums = %d, consumed product id = %d\n", current_id, pshared_res->queue->size, product_id);
        printf("Current queue: ");
        queue_display(pshared_res->queue);
        printf("\n");
        pthread_cond_broadcast(&pshared_res->cond);
        pthread_mutex_unlock(&pshared_res->mutex);
        sleep(1);
    }


   pthread_exit(NULL); 
}


int main(void)
{
    srand(time(NULL));

    SharedRes *shared_res = shared_res_init();

    int total_tid = PRODUCER_NUMS + CONSUMER_NUMS;
    pthread_t *tid_set = (pthread_t *)malloc(total_tid * sizeof(pthread_t));
    ERROR_CHECK(tid_set, NULL, "malloc");
    
    int ret;
    for(int i = 0; i < PRODUCER_NUMS; ++i){
        ret = pthread_create(tid_set + i, NULL, routine_producer, shared_res);
        printf("create a new producer, id = %d.\n", i + 1);
        THREAD_ERROR_CHECK(ret, "pthread_create");
    }

    for(int i = PRODUCER_NUMS; i < total_tid; ++i){
        printf("create a new consumer, id = %d.\n", i - PRODUCER_NUMS + 1);
        ret = pthread_create(tid_set + i, NULL, routine_consumer, shared_res);
        THREAD_ERROR_CHECK(ret, "pthread_create");
    }

    pthread_mutex_lock(&shared_res->mutex);
    while(shared_res->routine_id_index != PRODUCER_NUMS){
        pthread_cond_wait(&shared_res->cond, &shared_res->mutex);
    }
    pthread_mutex_unlock(&shared_res->mutex);

    for(int i = 0; i < total_tid; ++i){
        pthread_join(tid_set[i], NULL);
    }

    shared_res_destroy(shared_res);
    printf("join complete.\n");
    return 0;
}
