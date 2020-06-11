//
// Created by vernead2 on 08.06.20.
//

#include <cmath>
#include <ostream>
#include "Image.h"

Image::Image( size_t width, size_t height) {
    mWidth = width;
    mHeight = height;
    mData = std::vector<pixel_t>(mWidth * mHeight);
}

