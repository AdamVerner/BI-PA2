//
// Created by vernead2 on 06.06.20.
//

#include "Filter_HighPass.h"

template <typename ColorSpace>
ColorSpace Filter_HighPass<ColorSpace>::processPixelBox( ColorSpace box [3][3] ) const {

    double sum = 0;

    sum -= box[0][1];
    sum -= box[1][0];
    sum -= box[1][2];
    sum -= box[2][1];

    return std::abs(sum/4.0 + 2.0 * box[1][1]);

}
