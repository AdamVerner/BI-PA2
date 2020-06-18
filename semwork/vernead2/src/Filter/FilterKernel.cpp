//
// Created by vernead2 on 11.06.20.
//

#include "FilterKernel.h"

FilterKernel::FilterKernel( std::vector<double> square ) : Filter( CENTER) {
    for(size_t i = 0; i < 9; i++)
        mSquare[i] = square[i];
}

pixel_t FilterKernel::processPixelBox( imgData_t box ) const {

    // needs more space to prevent overflows
    int16_t sum_r = 0;
    int16_t sum_g = 0;
    int16_t sum_b = 0;

    for(size_t i = 0; i < 9; i++) {
        sum_r += box[i].r * mSquare[i];
        sum_g += box[i].g * mSquare[i];
        sum_b += box[i].b * mSquare[i];
    }


    // if(sum_r > 255) sum_r += 255;
    // if(sum_g > 255) sum_g += 255;
    // if(sum_b > 255) sum_b += 255;
    sum_r = std::min((int16_t)UINT8_MAX, std::max((int16_t)0, sum_r));
    sum_g = std::min((int16_t)UINT8_MAX, std::max((int16_t)0, sum_g));
    sum_b = std::min((int16_t)UINT8_MAX, std::max((int16_t)0, sum_b));

    return {(uint8_t)sum_r, (uint8_t)sum_g, (uint8_t)sum_b, box[5].a};

}
