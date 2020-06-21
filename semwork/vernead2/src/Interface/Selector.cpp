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
        out << "Invalid Selection." << std::endl;
    }

    out << "'" << options.find(selection)->second.first << "' selected." << std::endl;

    // execute the option
    options.find(selection)->second.second();
}


void Selector::promptCustom( const std::string & prompt ) {
    std::cout << prompt << std::endl;
    this->prompt( false);
}

void Selector::printPrompt( bool intro ) {
    if(intro)
        out << "Please select what do you want to do:" << std::endl;

    for(const auto & a: options){
        std::string op = "(" + std::to_string(a.first) + ")";
        out << std::setw(5) << std::right << op << " " << a.second.first << std::endl;
    }
    out << "Your selection?" << std::endl;
}

bool promptInteger( int & out ) {

    if ( !(std::cin >> out) ) {
        std::cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
        return false;
    }
    return true;
}

int PromptIntegerValue( int min, int max ) {
    int value;
    while( !promptInteger( value ) || value < min || value > max )
        std::cout << "Invalid value." << std::endl;
    return value;
}
