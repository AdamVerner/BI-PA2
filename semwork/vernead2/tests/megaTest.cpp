//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <CImage/CImage.h>
#include <CFilter/CFilter_Inverse.h>
#include <CScaler/CScaler_HQX.h>

#include "ViewPort.h"


int main(){

    std::unique_ptr<CImage> jpegImage = getImageFromFilename("examples/kitty.jpg", AUTO);

    std::ostringstream oss;

    ViewPort_Terminal simpleView(std::cout);

    jpegImage->applyScaler(CScaler_HQX(350, 350));
    jpegImage->applyFilter(CFilter_Inverse());
    simpleView.displayImage(*jpegImage);

    assert(jpegImage->getHeight() <= 350);
    assert(jpegImage->getWidth() <= 350);

    CImage img(3, 3, " # ### # ");
    simpleView.displayImage(img);
    img.applyFilter(CFilter_Inverse());
    simpleView.displayImage(img);

    img.applyFilter(CFilter_Inverse());
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