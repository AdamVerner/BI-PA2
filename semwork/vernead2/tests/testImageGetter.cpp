//
// Created by vernead2 on 02.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include "../src/dataTypes.h"
#include "../src/Image/Image.h"
// #include "../src/Image/Loaders/Loader.cpp"


void testConstructionAndMerge(){
    Image_ASCII img2(3, 3, " # ### # ");
    Image_ASCII img3(3, 3, "## ##    ");

    std::stringstream oss;
    oss << img2;
    assert(oss.str() == "Image <3 x 3>\n  #  \n# # #\n  #  \n");

    oss.str("");
    oss.clear();
    oss << img3;
    assert(oss.str() == "Image <3 x 3>\n"
                        "# #  \n"
                        "# #  \n"
                        "     \n");

    img2.merge(img3);

    oss.str("");
    oss.clear();
    oss << img2;
    std::cout << oss.str();
    assert(oss.str() == "Image <3 x 3>\n"
                        "+ #  \n"
                        "# # +\n"
                        "  +  \n");
}

int main(){
    testConstructionAndMerge();

    std::shared_ptr<Image> img1( new Image_ASCII(3, 3, "## ##    "));

    //std::shared_ptr<Image> img2 = LoadImage("progtest.png");

    // std::cout << *img2;

    Image_ASCII img3(3, 3, "## ##    ");


}