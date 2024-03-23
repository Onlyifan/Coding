#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Person {
  public:
    Person(const char *name, int age)
        : _name(new char[strlen(name) + 1]( ))
        , _age(age) {
        strcpy(_name, name);
    }

    Person(const Person &rhs)
        : _name(new char[1 + strlen(rhs._name)]( ))
        , _age(rhs._age) {
        strcpy(_name, rhs._name);
        cout << "finish Person(const Person &rhs)" << endl;
    }

    virtual ~Person( ) {
        if (_name) {
            delete[] _name;
            _name = nullptr;
        }
        cout << "finish ~Person()" << endl;
    }

    virtual void display( ) const {
        cout << "Name: " << _name << " Age: " << _age << endl;
    }

    Person &operator=(const Person &rhs) {
        if (this != &rhs) {
            _age = rhs._age;

            delete[] _name;
            _name = new char[1 + strlen(rhs._name)]( );
            strcpy(_name, rhs._name);
        }

        cout << "finish Person::operator=" << endl;
        return *this;
    }


  private:
    char *_name;
    int _age;
};

class Employee : public Person {
  public:
    Employee(const char *name, int age, const char *department, double salary)
        : Person(name, age)
        , _department(new char[1 + strlen(department)]( ))
        , _salary(salary) {
        strcpy(_department, department);
        ++_employeeNum;
        _totalSalary += salary;
    }

    Employee(const Employee &rhs)
        : Person(rhs)
        , _department(new char[1 + strlen(rhs._department)]( ))
        , _salary(rhs._salary) {
        strcpy(_department, rhs._department);
        ++_employeeNum;
        _totalSalary += _salary;
    }

    ~Employee( ) {
        if (_department) {
            delete[] _department;
            _department = nullptr;
            --_employeeNum;
            _totalSalary -= _salary;
        }
        cout << "finish ~Employee()" << endl;
    }

    Employee &operator=(const Employee &rhs) {
        if (this != &rhs) {
            Person::operator=(rhs);
            _totalSalary -= _salary;
            _salary = rhs._salary;
            _totalSalary += _salary;

            delete[] _department;
            _department = new char[1 + strlen(rhs._department)]( );
            strcpy(_department, rhs._department);
        }

        return *this;
    }


    static void showAveSalary( ) {
        if (_employeeNum == 0) {
            cout << "No employee" << endl;
            return;
        }
        cout << "Ave salary is " << _totalSalary / _employeeNum << endl;
    }

    void display( ) const override {
        Person::display( );
        cout << "Department: " << _department << " Salary: " << _salary << endl;
    }

  private:
    char *_department;
    double _salary;
    static int _employeeNum;
    static double _totalSalary;
};
double Employee::_totalSalary = 0.0;
int Employee::_employeeNum = 0;


int test0(void) {
    Employee emp1("Alice Smith", 35, "HR", 50000.00);
    emp1.display( );
    Employee emp2("Bob Johnson", 42, "IT", 75000.00);
    Person &p2 = emp2;
    p2.display( );

    Person *p3 = new Employee("Charlie Brown", 28, "Finance", 60000.00);
    Employee::showAveSalary( );
    p3->display( );
    delete p3;


    Employee emp4 = emp2;
    emp4.display( );
    Employee::showAveSalary( );

    emp1 = emp2;

    emp4.display( );
    Employee::showAveSalary( );

    return 0;
}

int main(void) {
    test0( );
    Employee::showAveSalary( );
}
