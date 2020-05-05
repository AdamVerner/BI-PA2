//
// Created by vernead2 on 02.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "ViewPort.h"
#include "Image.h"


int main(){

    std::unique_ptr<CImage> asciiImage = getImageFromFilename("tests/img.ascii", AUTO);

    std::cout << *asciiImage << std::endl;

    std::ostringstream oss;

    ViewPort_Terminal simpleView(oss);
    simpleView.displayImage(*asciiImage);

    std::cout << oss.str() << std::endl << std::flush;

    assert(oss.str() ==
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