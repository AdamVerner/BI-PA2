//
// Created by vernead2 on 01.05.20.
//

#pragma once
#include <cstddef>

class CScaler{

    CScaler(size_t width, size_t height): reqWidth(width), reqHeight(height) {}

private:
    size_t reqWidth;
    size_t reqHeight;
};


/** Scaler using Bilinear interpolation.
 *  https://rosettacode.org/wiki/Bilinear_interpolation#C
 *
 *
 * */
class CScaler_BilinearInterpolation{

};


/** Pixel art scaling algorithm.
 * https://en.wikipedia.org/wiki/Hqx
 * http://forums.nesdev.com/viewtopic.php?p=82770#82770
 * */
class CScaler_HQX{


};