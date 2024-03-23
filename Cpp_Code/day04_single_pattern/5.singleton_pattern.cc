#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class City {
    City &operator= (const City &) = delete;
    City (const City &) = delete;

  public:
    static City *getInstance (int population = 0, const char *name = "Default") {
        if (_pInstance == nullptr) {
            _pInstance = new City (population, name);
            return _pInstance;
        }

        _pInstance->_population = population;
        if (strcmp (name, "Default") == 0) {
            return _pInstance;
        }

        delete[] _pInstance->_name;
        _pInstance->_name = new char[strlen (name) + 1]( );
        strcpy (_pInstance->_name, name);

        return _pInstance;
    }

    static void destroy ( ) {
        if (_pInstance == nullptr) {
            cout << "duplicate clean "
                    "object"
                 << endl;
            return;
        }
        delete _pInstance;
        _pInstance = nullptr;
        cout << "success clean object" << endl;
    }

    static void printInfo ( ) {
        if (_pInstance == nullptr) {
            cout << "object no exist, "
                    "failed to print"
                 << endl;
            return;
        }
        cout << "Population: " << _pInstance->_population << "; City name: " << _pInstance->_name << endl;
    }

  private:
    City (int population, const char *name)
        : _population (population)
        , _name (new char[strlen (name) + 1]( )) {
        strcpy (_name, name);
        cout << "success register city "
                "information"
             << endl;
    }
    ~City ( ) {
        if (_name) {
            delete[] _name;
            _name = nullptr;
            cout << "true";
        }
        cout << " ~City()" << endl;
    }

  private:
    int _population;
    char *_name;
    static City *_pInstance;
};
City *City::_pInstance = nullptr;

int main (void) {
    City::getInstance ( )->getInstance ( )->printInfo ( );
    City::getInstance (123);
    City::getInstance ( )->printInfo ( );
    City::getInstance (1234, "Wu Han")->printInfo ( );
    City::getInstance (321);
    City::printInfo ( );
    City::destroy ( );
    City::destroy ( );
    City::printInfo ( );
    City::getInstance (233, "aa")->printInfo ( );

    City::destroy ( );
    return 0;
}
