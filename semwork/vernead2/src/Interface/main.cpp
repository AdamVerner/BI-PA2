//
// Created by vernead2 on 20.06.20.
//

#include "CMDInterface.h"

int main( int argc, char ** argv ){

    //FILE * fp = freopen("examples/example_2_in.txt","r",stdin);
    //std::cout << fp << std::endl;

    std::cin.exceptions(std::ios::eofbit);

    CMDInterface cmdInterface;

    if(cmdInterface.ParseArguments( argc, argv))
        return 1;

    try {
        return cmdInterface.run( );
    }
    catch(std::ios::failure &){
        // EOF do nothing
    }


}