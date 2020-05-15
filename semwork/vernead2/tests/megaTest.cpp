//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "ViewPort.h"
#include "Image.h"
#include "Scaler.h"


int main(){

    std::unique_ptr<CImage> jpegImage = getImageFromFilename("examples/kitty.jpg", AUTO);

    std::ostringstream oss;

    ViewPort_Terminal simpleView(std::cout);

    jpegImage->scale(CScaler(350, 350));
    simpleView.displayImage(*jpegImage);

    assert(jpegImage->getHeight() <= 350);
    assert(jpegImage->getWidth() <= 350);

    // jpegImage->scale(CScaler(200, 200));
    //simpleView.displayImage(*jpegImage);


}