//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include <cstddef>
#include <iostream>
#include "dataTypes.h"
#include "Scaler/Scaler.h"

/** Scaler using Bilinear interpolation.
 *  https://en.wikipedia.org/wiki/Bilinear_interpolation
 *
 *
 * */
class Scaler_BilinearInterpolation: public Scaler {
public:
    Scaler_BilinearInterpolation( int width, int height ): Scaler(width, height) {}

    /** Linearly Interpolate pixel value.
     *
     *   tl              tr
     *    +---------------+
     *    |               |
     *    |        (x,y)  |
     *    |       *       |
     *    |               |
     *    |               |
     *    +---------------+
     *   bl               br
     *
     *
     *  Firstly the value between top pixels and bottom pixels is interpolated,
     *  the output is then interpolated between these products.
     *
     * @param data pixel array
     * @param width width of the image stored in pixel array
     * @param width height of the image stored in pixel array
     * @param x X coordinate
     * @param y Y coordinate
     * @return pixel_r calculated pixel value
     * */
    pixel_t getBilinearPixel( imgData_t & data, size_t width, size_t height, double x, double y ) const;

    /** Get reference to single pixel from pixel array
     * @param data pixel array
     * @param width width of the image stored in pixel array
     * @param x X coordinate
     * @param y Y coordinate
     * @return selected pixel reference
     * @throws std::out_of_range
     * */
    pixel_t & getPixel( imgData_t & data, const size_t & width, const size_t & x, const size_t & y ) const{
        return data.at(y * width + x);
    }


    virtual void processData( imgData_t & data, size_t & width, size_t & height ) const;


};