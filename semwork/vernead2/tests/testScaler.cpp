//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "Scaler/Scaler_BilinearInterpolation.h"
#include "Image/Loaders/Loader.h"
#include "../src/Image/Image.h"
#include "../src/Filter/Filter_Inverse.h"
#include "../src/Filter/Filter_LowPass.h"
#include "../src/Filter/Filter_HighPass.h"
#include "../src/Filter/Filter_Sharpen.h"

int main(){

    ImagePtr img = LoadImage( "examples/kitty.jpg", AUTO);
    img->applyScaler(Scaler_BilinearInterpolation(150, 150));

    img->saveAs("tests/new.png");

    std::cout << *img;

}