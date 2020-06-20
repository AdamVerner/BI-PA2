//
// Created by vernead2 on 19.06.20.
//

#include "Plugin_Rotate.h"

void Plugin_Rotate::processImage( Image & img ) const {

    auto imgCopy = img.copy();

    double radians = (mDirection * M_PI) / 180;
    double sinf = sin(radians);
    double cosf = cos(radians);

    // rotation
    for (size_t x = 0; x < img.getWidth(); x++) {
        for (size_t y = 0; y < img.getHeight(); y++) {

            long double xf = x - mXCenter;
            long double yf = y - mYCenter;

            size_t xx = (+xf * cosf - yf * sinf + mXCenter);
            size_t yy = (+xf * sinf + yf * cosf + mYCenter);

            if (xx >= 0 && xx < img.getWidth() && yy >= 0 && yy < img.getHeight()) {
                img.Pixel(x,y) = imgCopy->Pixel(xx, yy);
            }
            else
                img.Pixel(x,y) = 0;
        }
    }

}
