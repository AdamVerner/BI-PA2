//
// Created by vernead2 on 19.06.20.
//

#pragma once

#include <string>
#include <utility>

#include "../Image/Image.h"
#include "../dataTypes.h"
#include "Plugin.h"

/** Image rotation using nearest neighbor interpolation
 * */
class Plugin_Rotate: public Plugin{
public:

    explicit Plugin_Rotate( ssize_t x, ssize_t y, double direction): Plugin( "Rotation"), mXCenter( x), mYCenter( y), mDirection( direction) { }
    void processImage( Image & img ) const override;

protected:
private:
    ssize_t mXCenter, mYCenter;
    double mDirection;
};