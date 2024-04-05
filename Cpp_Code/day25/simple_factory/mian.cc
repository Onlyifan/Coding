#include "Factory.h"
#include "Figure.h"
#include <iostream>

#include <string>
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;


void func(Figure *pfig) {
    pfig->showType( );
    cout << "的面积 : " << pfig->area( ) << endl;
}


int main(int argc, char **argv) {
    unique_ptr<Figure> prec(Factory::create(rectangle));
    unique_ptr<Figure> pcir(Factory::create(circle));

    cout << endl;
    func(prec.get( ));
    func(pcir.get( ));
    cout << endl;

    return 0;
}
