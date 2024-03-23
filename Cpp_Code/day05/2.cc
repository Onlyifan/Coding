#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#include <unistd.h>

class City {
  public:
    void deleteInstance( ) {
        if (this) {
            delete this;
        }
    }

    void updateInfo(int population, const string &name = "") {
        _population = population;
        if (name != "") {
            _name = name;
        }
    }

    void showInfo( ) {
        cout << "Name: " << _name << "; Population: " << _population << endl;
    };

    City(int population, const string &name)
        : _population(population)
        , _name(name) {}

  private:
    ~City( ) = default;

  public:
    int _population;
    string _name;
};

int main(void) {

    City *c1 = new City(30, "wuhan");
    c1->showInfo( );
    c1->updateInfo(233);
    c1->showInfo( );
    c1->deleteInstance( );
    //c1->deleteInstance( );
    cout << c1->_name << endl;
    c1 = nullptr;
    City *c2 = new City(30, "changsha");
    c2->showInfo( );
    // c2->deleteInstance( );
    //c2 = nullptr;
    return 0;
}
