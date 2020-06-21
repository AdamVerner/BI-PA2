//
// Created by vernead2 on 19.06.20.
//

#include "Plugin_Rotate.h"


void Plugin_Rotate::processImage( Image & img ) const {

    if (mDirection == 0)
        return;

    auto imgCopy = img.copy();

    double radians = (mDirection * M_PI) / 180;
    double sinf = sin(radians);
    double cosf = cos(radians);

    // rotation
    for (int x = 0; x < (int)img.getWidth(); x++) {
        for (int y = 0; y < (int)img.getHeight(); y++) {

            double xf = x - (int)mXCenter;
            double yf = y - (int)mYCenter;

            int xx = (+xf * cosf - yf * sinf + (int)mXCenter);
            int yy = (+xf * sinf + yf * cosf + (int)mYCenter);

            if (xx >= 0 && xx < (int)imgCopy->getWidth() && yy >= 0 && yy < (int)imgCopy->getHeight()) {
                img.Pixel(x,y) = imgCopy->Pixel(xx, yy);
            }
            else
                img.Pixel(x,y) = 0;
        }
    }

}
