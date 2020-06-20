//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

class Filter_Grayscale: public Filter {
public:
    Filter_Grayscale() = default; // : Filter() {}

private:
    pixel_t processPixel(pixel_t & value) const override {
        return {value.getGray(), value.getGray(), value.getGray(), value.a};
    }
};