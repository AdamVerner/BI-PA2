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

    explicit FilterKernel( std::vector<double> square );


protected:
    std::vector<double> mSquare= {0, 0, 0, 0, 0, 0, 0, 0, 0}; /**< flattened square kernel*/

private:
    /**
     * Calculate new value for each pixel. preserve alpha channel.
     * */
    pixel_t processPixelBox(imgData_t box) const override;

};