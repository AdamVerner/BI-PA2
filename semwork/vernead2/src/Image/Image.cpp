//
// Created by vernead2 on 08.06.20.
//

#include <cmath>
#include <ostream>
#include "Image.h"

Image::Image( size_t width, size_t height) {
    mWidth = width;
    mHeight = height;
    mData = std::vector<pixel_t>(mWidth * mHeight, 0);
}

char Image::LUTLookup( const pixel_t & idx ) const {
    size_t max = pixel_t(-1).getGray();
    size_t step = mLUT.length();
    size_t gray = idx.getGray();
    return mLUT[gray * step / max ];
}

bool Image::merge( const Image & other ) {

    if(mWidth != other.mWidth || mHeight != other.mHeight)
        return false;

    for(size_t y = 0; y < mHeight; y++ )
        for( size_t x = 0; x < mWidth; x++ )
            mData[y * mWidth + x].merge(other.mData[y * mWidth + x]);
    return true;
}

double Image::difference( const Image & other ) const {

    if(mWidth != other.mWidth || mHeight != other.mHeight){
        return 1;
    }

    double sum = 0;

    for (size_t i = 0; i < mWidth * mHeight; i++){
        sum += abs(mData[i].getGray() - other.mData[i].getGray());
    }

    return sum / (double)(mWidth * mHeight * 255);
}

std::ostream & operator<<( std::ostream & os, const Image & img ) {
    os << "Image <" << img.mHeight << " x " << img.mWidth << ">" << std::endl;

    for (size_t y = 0; y < img.mHeight; y++){
        for( size_t x = 0; x < img.mWidth ; x++ ) {
            os << img.LUTLookup( img.Pixel( x, y ));
            if (x != img.mWidth - 1) os << " "; // TODO instead of printing space, rescale image by ~60%
        }
        os << std::endl;
    }
    return os;
}

Image::Image( size_t width, size_t height, const char * src ) {
    mWidth = width;
    mHeight = height;
    mLUT = DEFAULT_LUT;
    mData = std::vector<pixel_t>(width * height);
    for(size_t y = 0; y < mHeight; y++ )
        for( size_t x = 0; x < mWidth; x++ )
            mData[y * mWidth + x] = reverseLUTLookup(src[y * mWidth + x]);
}

pixel_t Image::reverseLUTLookup( char c ) const {
    // TODO optimize by pre-calculating the reverse lookup table(or save as map)

    uint8_t max = pixel_t(255).getGray();
    uint8_t lut_len = mLUT.length();

    uint8_t inc =  std::ceil((double)max / lut_len);
    uint8_t val = inc / 2; // start in the middle of the range

    for (const auto & l: mLUT){
        if(l == c) return {val};
        val += inc;
    }

    throw std::logic_error("character not in LUT");
}

