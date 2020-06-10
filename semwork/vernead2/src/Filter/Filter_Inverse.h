//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

template <typename ColorSpace = pixel_rgba_t<uint8_t>>
class Filter_Inverse: public Filter<ColorSpace> {
public:
    Filter_Inverse() = default; // : Filter() {}

private:
    ColorSpace processPixel(ColorSpace value) const override ;

protected:

};