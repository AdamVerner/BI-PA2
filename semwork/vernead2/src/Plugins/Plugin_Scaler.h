//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "dataTypes.h"
#include "Plugin.h"
#include "Image/Image.h"

/** Plugin for image scaling
 *  https://en.wikipedia.org/wiki/Bilinear_interpolation
 *
 *  // TODO add 2x scaling that does not produce edge blur
 * */
class Plugin_Scaler: public Plugin {
public:
    explicit Plugin_Scaler( int width, int height ): Plugin( "Scaler" ), mReqWidth(width), mReqHeight(height) {}

    void processImage( Image & img ) const override;

private:


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
     * @param img Image to get pixel from
     * @param x X coordinate
     * @param y Y coordinate
     * @return pixel_r calculated pixel value
     * */
    static pixel_t getBilinearPixel( const Image & img, double x, double y ) ;

    size_t mReqWidth;
    size_t mReqHeight;


};