//
// Created by vernead2 on 19.06.20.
//

#include <iostream>
#include <iomanip>
#include <limits>

#include "Selector.h"

void Selector::Add( int id, const std::string & name, const std::function<void( void )> & callback ) {
    options.insert(std::make_pair(id, std::make_pair(name, callback)));
}

void Selector::prompt( bool intro ) {
    printPrompt(intro);

    int selection = 0;
    while ( !promptInteger(selection) || !options.count(selection) ) {
        std::cout << "Invalid Selection." << std::endl;
    }

    std::cout << "'" << options.find(selection)->second.first << "' selected." << std::endl;

    // execute the option
    options.find(selection)->second.second();
}



void Selector::prompt( const std::string & prompt ) {
    std::cout << prompt;
    this->prompt( false);

}

void Selector::printPrompt( bool intro ) {
    if(intro)
        std::cout << "Please select what do you want to do:" << std::endl;

    for(const auto & a: options){
        std::string op = "(" + std::to_string(a.first) + ")";
        std::cout << std::setw(5) << std::right << op << " " << a.second.first << std::endl;
    }
    std::cout << "Your selection?" << std::endl;
}

bool promptInteger( int & out ) {

    if ( !(std::cin >> out) ) {
        std::cin.clear();
        std::cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
        return false;
    }
    return true;
}
