//
// Created by vernead2 on 02.05.20.
//

#include <cassert>
#include <iostream>


class A{
public:
    virtual char get() { return 'a';}
};

class B: public A{
public:
    char get() { return 'b'; }

};


int main(){

    A a;
    B b;
    A & ref = b;

    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
    std::cout << ref.get() << std::endl;


    /*
    assert(ends_with("file.ASCII", ".ASCII"));
    assert(ends_with("file.ascii", ".ASCII"));
    assert(ends_with("file.aSCii", ".ASCII"));
    assert(!ends_with("file.NOTASCII", ".ASCII"));
    assert(!ends_with("file.png", ".ASCII"));
*/

}