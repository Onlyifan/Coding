#include <iostream>
using std::cout;
using std::endl;

class Student {
    public:
        Student() = default;
        Student(long id, const char *name,int age, int test)
            :_test(_age)
             ,_id(id)
             ,_name(new char[strlen(name) + 1]())
             ,_age(age)
             ,_haha(age)
    {
        memcpy(_name, name, strlen(name));
        cout << "success new a student" << endl;
        //cout << "id: " << _id << ";name: " << _name << ";age: " << _age << endl;
    }

        Student(Student &stu);
        Student(const Student &stu)
            :_id(stu._id)
             ,_age(stu._age)
             ,_name(new char[strlen(stu._name) + 1]())
             , _test(stu._test){
                 memcpy(_name, stu._name, strlen(stu._name));

                 cout << "success copy a student" << endl;
                 //cout << "id: " << _id << ";name: " << _name << ";age: " << _age << endl;
             }
        ~Student() {
            if(_name) {
                cout << "success kill a student" << endl;
                cout << "id: " << _id << ";name: " << _name << ";age: " << _age << endl;
                delete[] _name;
                _name = nullptr;
            }
        }

        void showInfo() {
            //cout << "id: " << _id << ";name: " << _name << ";age: " << _age << ";test: " <<_test << endl;
            cout << "id: " << _id <<";age: " << _age << ";test: " <<_test << endl;
        }

        Student  operator=(const Student  rhs) {
            cout << "after into operator=" << endl;
            if(this != &rhs){
                _id = rhs._id;
                _age = rhs._age;
                delete [] _name;
                _name = new char[strlen(rhs._name)]();
                strcpy(_name,rhs._name);
            }
            cout << "success = a student" << endl;
            //cout << "id: " << _id << ";name: " << _name << ";age: " << _age << endl;
            cout << "before return *this" << endl;
            return *this;
        }

        static void testhahaha(int ) {
            return;
        }

    private:
        int _test;
        long _id;
        char *_name;
        int _age;
        int _haha;
};

int main(void){
    Student aaa;
    aaa.showInfo();

    //int a = 2;
    //Student s1(12345, "s1", 18, a);
    //s1.showInfo();
    ////    Student s2(2, "s2", 22);
    //    Student s3(3, "s3", 33);
    //    Student s4(4, "s4", 44);
    //    //const Student stmp = Student(222, "dneiw", 22222);
    //    s4 = s1 = s2 = s3;
    //
    //
    //
    return 0;
}
