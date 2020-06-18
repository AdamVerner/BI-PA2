//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

class Filter_Inverse: public Filter {
public:
    Filter_Inverse() = default; // : Filter() {}

private:
    virtual pixel_t processPixel(pixel_t & value) const {
        return {(uint8_t)(255 - value.r), (uint8_t)(255 - value.g), (uint8_t)(255 - value.b), value.a};
    }
};