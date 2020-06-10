//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

template <typename ColorSpace = pixel_rgba_t<uint8_t>>
class Filter_LowPass: public Filter<ColorSpace> {
public:
    Filter_LowPass()=default; // : Filter() {}

private:
    /** Low pass filtering. The output is calculated as an average of all pixels inside the PixelBox.
     * */
    ColorSpace processPixelBox(ColorSpace [3][3]) const override;
};