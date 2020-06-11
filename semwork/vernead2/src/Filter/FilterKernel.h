//
// Created by home-6 on 11.06.20.
//

#pragma once


#include "Filter.h"

/**
 *  Used for processing images wia kernel.
 *  The filter iterates over all pixels and creates and kernel box.
 *  Each square contains an coefficient with which each pixel value is multiplied.
 *  The output is sum of all squares.
 *
 * e.g. an kernel
 * +-----+-----+-----+
 * | 1/9 | 1/9 | 1/9 |
 * +-----+-----+-----+
 * | 1/9 | 1/9 | 1/9 |
 * +-----+-----+-----+
 * | 1/9 | 1/9 | 1/9 |
 * +-----+-----+-----+
 *
 * calculates an average value of the 3x3 square, this is used for lowpass filtering.
 * */
class FilterKernel: public Filter{
public:
    FilterKernel( std::vector<double> square ): Filter( CENTER) {
        for(size_t i = 0; i < 9; i++)
            mSquare[i] = square[i];
    }


protected:
    std::vector<double> mSquare= {0, 0, 0, 0, 0, 0, 0, 0, 0}; /**< flattened square kernel*/

private:
    /**
     * Calculate new value for each pixel. preserve alpha channel.
     * */
    pixel_t processPixelBox(imgData_t box) const override{

        // needs more space to prevent overflows
        uint16_t sum_r = 0;
        uint16_t sum_g = 0;
        uint16_t sum_b = 0;

        for(size_t i = 0; i < 9; i++) {
            sum_r += box[i].r * mSquare[i];
            sum_g += box[i].g * mSquare[i];
            sum_b += box[i].b * mSquare[i];
        }

        return {(uint8_t)sum_r, (uint8_t)sum_g, (uint8_t)sum_b, box[5].a};

    }

};