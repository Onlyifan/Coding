#ifndef _TEST_HPP_
#define _TEST_HPP_

#include <iostream>

class myClass{
    public:
        void print() {
            std::cout<<"hello"<<std::endl;
            print();
        }
};


#endif // _TEST_HPP_
