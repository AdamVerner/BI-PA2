//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

template <typename ColorSpace = pixel_rgba_t<uint8_t>>
class Filter_HighPass: public Filter<ColorSpace>{
public:
    Filter_HighPass()= default; // : Filter() {}

private:
    /** Simple high pass filter implementation.
     * ```
     * +----+----+----+
     * | 0  |-1/4| 0  |
     * +----+----+----+
     * |-1/4| +2 |-1/4|
     * +----+----+----+
     * | 0  |-1/4| 0  |
     * +----+----+----+
     * ```
     * */
    ColorSpace processPixelBox(ColorSpace [3][3]) const override;

};