//
// Created by vernead2 on 09.06.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>


#include "../src/Image/Image.h"


int main(){

    Image<pixel_bw_t<uint8_t>> img(3, 3, " # ### # ");


    std::unique_ptr<Image> jpegImage = getImageFromFilename("examples/kitty.jpg", AUTO);

    std::ostringstream oss;

    ViewPort_Terminal simpleView(std::cout);

    jpegImage->applyScaler(CScaler_HQX(350, 350));
    jpegImage->applyFilter(Filter_Inverse());
    simpleView.displayImage(*jpegImage);

    assert(jpegImage->getHeight() <= 350);
    assert(jpegImage->getWidth() <= 350);

    Image img(3, 3, " # ### # ");
    simpleView.displayImage(img);
    img.applyFilter(Filter_Inverse());
    simpleView.displayImage(img);

    img.applyFilter(Filter_Inverse());
    std::cout << img << std::endl;
    simpleView.displayImage(img);

    img.applyScaler(CScaler(6, 6));
    std::cout << img << std::endl;
    simpleView.displayImage(img);

    img.applyScaler(CScaler(3, 3));
    std::cout << img << std::endl;
    simpleView.displayImage(img);

    img.applyScaler(CScaler(6, 6));
    std::cout << img << std::endl;
    simpleView.displayImage(img);

}