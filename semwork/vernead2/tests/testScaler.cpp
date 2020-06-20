//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "Plugins/Plugin_Scaler.h"
#include "Image/Loaders/Loader.h"

int main(){

    ImagePtr img = LoadImage( "examples/kitty.jpg", AUTO);
    ImagePtr save = img->copy();
    std::cout << *img;

    img->saveAs("tests/new1.png");


    img->applyPlugin(Plugin_Scaler(50, 25));

    img->saveAs("tests/new2.png");
    save->saveAs("tests/new3.png");

    std::cout << *img;

}