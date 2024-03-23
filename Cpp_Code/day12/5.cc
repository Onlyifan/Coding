#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class Person {
  public:
    Person(const string &name, int age)
        : _name(name)
        , _age(age) {}

    void display( ) {
        cout << "Person's name is " << _name << ", age is " << _age << "."
             << endl;
    }

  private:
    string _name;
    int _age;
};

class Employee : public Person {
  public:
    Employee(const string &name, int age, const string &department,
             double salary)
        : Person(name, age)
        , _department(department)
        , _salary(salary) {}

    void showEmployeeInfo( ) {
        display( );
        cout << "department is " << _department << ", salary is " << _salary
             << "." << endl;
    }

    double getSalary( ) {
        return _salary;
    }

  private:
    string _department;
    double _salary;
};


int main(void) {


    Employee emp1("Alice Smith", 35, "HR", 50000.00);
    Employee emp2("Bob Johnson", 42, "IT", 75000.00);
    Employee emp3("Charlie Brown", 28, "Finance", 60000.00);

    emp1.showEmployeeInfo( );
    emp2.showEmployeeInfo( );
    emp3.showEmployeeInfo( );

    double totalSalary = 0.0;
    totalSalary += emp1.getSalary( );
    totalSalary += emp2.getSalary( );
    totalSalary += emp3.getSalary( );

    cout << "The 3 employees average salary is " << totalSalary / 3 << "."
         << endl;

    return 0;
}
