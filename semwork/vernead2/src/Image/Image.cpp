//
// Created by vernead2 on 08.06.20.
//

#include <cmath>
#include <ostream>
#include "Image.h"

Image::Image( const Image & other) {
    mData = other.mData;
    mLUT = other.mLUT;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
}

Image::Image( size_t width, size_t height) {
    mWidth = width;
    mHeight = height;
    mData = std::vector<std::shared_ptr<pixel_t>>(mWidth * mHeight);

}

