//
// Created by vernead2 on 02.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "ViewPort.h"


int main(){

    std::unique_ptr<CImage> asciiImage = getImageFromFilename("tests/img.ascii", AUTO);

    std::ostringstream oss1;
    std::ostringstream oss2;
    std::cout << *asciiImage << std::endl;

    oss1 << *asciiImage << std::endl;
    assert(oss1.str() == "CImage <tests/img.ascii 15 x 22>\n");


    ViewPort_Terminal simpleView(oss2);
    simpleView.displayImage(*asciiImage);


    std::cout << oss2.str() << std::endl << std::flush;

    assert(oss2.str() ==
           "###                   \n"
           "#  #                  \n"
           "#  # # ##   ###    ###\n"
           "###  ##    #   #  #  #\n"
           "#    #     #   #  #  #\n"
           "#    #     #   #  #  #\n"
           "#    #      ###    ###\n"
           "                     #\n"
           "                   ## \n"
           "                      \n"
           " #    ###   ###   #   \n"
           "###  #   # #     ###  \n"
           " #   #####  ###   #   \n"
           " #   #         #  #   \n"
           "  ##  ###   ###    ## \n");

}