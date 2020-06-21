//
// Created by vernead2 on 19.06.20.
//

#pragma once

#include <string>
#include <utility>

#include "Image/Image.h"
#include "dataTypes.h"
#include "Plugin.h"

/** Image rotation using nearest neighbor interpolation
 * */
class Plugin_Rotate: public Plugin{
public:

    explicit Plugin_Rotate(int x, int y, double direction): Plugin("Rotation"), mXCenter( x), mYCenter( y), mDirection( direction) { }
    void processImage( Image & img ) const override;

protected:
private:
    size_t mXCenter, mYCenter;
    double mDirection;
};