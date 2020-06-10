//
// Created by vernead2 on 06.06.20.
//

#include "Filter_LowPass.h"

template <typename ColorSpace>
ColorSpace Filter_LowPass<ColorSpace>::processPixelBox( ColorSpace box [3][3]  ) const {

    ColorSpace sum = 0;

    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 3; x++)
            sum += box[y][x] / 9;
    return sum;
}
