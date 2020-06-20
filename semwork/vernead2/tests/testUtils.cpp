//
// Created by vernead2 on 02.05.20.
//

#include <cassert>
#include <iostream>
#include <Interface/Selector.h>


int main(){

    std::cout.exceptions(std::iostream::goodbit);

    std::cout << "Input something: ";

    char c;

    while( std::cin >> c)
        std::cout << c << std::endl;

    std::cin.clear();
    fflush(stdin);

    while( !(std::cin >> c))
        std::cout << '-' << c << std::endl;

}