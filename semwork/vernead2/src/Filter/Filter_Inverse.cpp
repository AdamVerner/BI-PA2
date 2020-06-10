//
// Created by vernead2 on 06.06.20.
//

#include "Filter_Inverse.h"

template <typename ColorSpace>
ColorSpace Filter_Inverse<ColorSpace>::processPixel( ColorSpace value ) const {
    return ColorSpace(-1) - value;
}
