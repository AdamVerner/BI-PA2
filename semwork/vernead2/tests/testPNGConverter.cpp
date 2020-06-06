#include <iostream>
#include <sstream>
#include <cassert>

#include "ViewPort.h"


int main(){

    std::unique_ptr<CImage> jpegImage = getImageFromFilename("tests/progtest.png", AUTO);

    std::ostringstream oss;

    ViewPort_Terminal simpleView(oss);
    simpleView.displayImage(*jpegImage);

    std::cout << oss.str() << std::endl << std::flush;


    assert(oss.str() ==
    "                                \n"
    "# # # # #       # # # # #       \n"
    "# # # # #       # # # # #       \n"
    "# # # # #       # # # # #       \n"
    "# # # # # #   # # # # # #       \n"
    "# # # # # # # # # # # # # # #   \n"
    "    # # # # # # # # # # # # # # \n"
    "      # # # # # # # # # # # # # \n"
    "    # # # # # # # # # # # # # # \n"
    "# # # # # # # # # # # # # # #   \n"
    "# # # # # # # # # # # # #       \n"
    "# # # # # # # # # # # # #       \n"
    "# # # # # # # # # # # # #       \n"
    "        # # # # #               \n"
    "        # # # # #               \n"
    "          # # #                 \n"
    );

}