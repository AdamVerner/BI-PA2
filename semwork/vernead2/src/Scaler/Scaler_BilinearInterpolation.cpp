//
// Created by vernead2 on 06.06.20.
//

#include "Scaler/Scaler_BilinearInterpolation.h"

pixel_t Scaler_BilinearInterpolation::getBilinearPixel( imgData_t & data, size_t width, size_t height, double x,
                                                        double y ) const {

    size_t xi = (int)x;
    size_t yi = (int)y;
    double xf = x - xi;
    double yf = y - yi;

    size_t xiNext = std::min(xi + 1, width - 1);
    size_t yiNext = std::min( (size_t)y + 1, height - 1);

    pixel_t bl = getPixel(data, width, xi, y);
    pixel_t br = getPixel(data, width, xiNext, y);
    pixel_t tl = getPixel(data, width, xi, yiNext);
    pixel_t tr = getPixel(data, width, xiNext, yiNext);

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

void Scaler_BilinearInterpolation::processData( imgData_t & data, size_t & width, size_t & height ) const {

    auto old_data = data; // deep copy

    data = imgData_t(mReqWidth * mReqHeight);

    double scaleX = (double)width / mReqWidth;
    double scaleY = (double)height / mReqHeight;

    for( size_t y = 0; y < mReqWidth; y++ ) {
        for( size_t x = 0; x < mReqHeight; x++ ) {
            getPixel(data, mReqWidth, x, y) = getBilinearPixel(old_data, width, height, x * scaleX, y * scaleY);
        }
    }

    // All was successful report the finished widths and heights.
    width = mReqWidth;
    height = mReqHeight;

}
