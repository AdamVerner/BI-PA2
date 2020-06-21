//
// Created by vernead2 on 06.06.20.
//

#include "Plugin_Resize.h"

pixel_t Plugin_Resize::getBilinearPixel( const Image & img, double x, double y ) {

    auto xi = (size_t)x;
    auto yi = (size_t)y;
    double xf = x - xi;
    double yf = y - yi;

    size_t xiNext = std::min(xi + 1, img.getWidth() - 1);
    size_t yiNext = std::min( (size_t)y + 1, img.getHeight() - 1);

    pixel_t bl = img.Pixel(xi, y);
    pixel_t br = img.Pixel(xiNext, y);
    pixel_t tl = img.Pixel(xi, yiNext);
    pixel_t tr = img.Pixel(xiNext, yiNext);

    // weighted combine pixels per channel
    uint8_t bottom_r = xf * br.r + (1.0 - xf) * bl.r;
    uint8_t bottom_g = xf * br.g + (1.0 - xf) * bl.g;
    uint8_t bottom_b = xf * br.b + (1.0 - xf) * bl.b;
    uint8_t bottom_a = xf * br.a + (1.0 - xf) * bl.a;

    uint8_t top_r = xf * tr.r + (1.0 - xf) * tl.r;
    uint8_t top_g = xf * tr.g + (1.0 - xf) * tl.g;
    uint8_t top_b = xf * tr.b + (1.0 - xf) * tl.b;
    uint8_t top_a = xf * tr.a + (1.0 - xf) * tl.a;

    uint8_t pxf_r = yf * top_r + (1.0 - yf) * bottom_r;
    uint8_t pxf_g = yf * top_g + (1.0 - yf) * bottom_g;
    uint8_t pxf_b = yf * top_b + (1.0 - yf) * bottom_b;
    uint8_t pxf_a = yf * top_a + (1.0 - yf) * bottom_a;

    return {(uint8_t)pxf_r, (uint8_t)pxf_g, (uint8_t)pxf_b, (uint8_t)pxf_a};

}


void Plugin_Resize::processImage( Image & img ) const {

    auto OldImage = img.copy();

    img.resizeCanvas(mReqWidth, mReqHeight);

    double scaleX = (double)OldImage->mWidth / mReqWidth;
    double scaleY = (double)OldImage->mHeight / mReqHeight;

    for( size_t y = 0; y < mReqHeight; y++ ) {
        for( size_t x = 0; x < mReqWidth; x++ ) {
            img.Pixel(x, y) = getBilinearPixel(*OldImage, x * scaleX, y * scaleY);
        }
    }

    // All was successful report the finished widths and heights.
    //img.mWidth = mReqWidth;
    //img.mHeight = mReqHeight;

}
