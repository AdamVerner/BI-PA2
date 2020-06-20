//
// Created by vernead2 on 30.04.20.
//

#include <stdexcept>

#include "Filter.h"
#include "Image/Image.h"

imgData_t Filter::generatePixelBlock( Image & img, size_t img_x, size_t img_y) const {

    // TODO PX_BOX_SIZE variable size

    imgData_t pixelBox(9, 0);

    for(ssize_t y = -1; y <= 1; y++){
        for(ssize_t x = -1; x <= 1; x++){

            // Bound checking is done in `array.at` method.
            // This should be efficient because of the Zero-Cost Exception Model.
            try {
                pixelBox [(y+1) * 3 + (x + 1)] = img.Pixel(img_x + x, img_y + y);
            }
            catch(std::out_of_range & err){
                switch(m_sidePolicy){
                    case(ZERO):
                        pixelBox [(y+1) * 3 + (x + 1)] = 0;
                    break;
                    case(MAX):
                        pixelBox [(y+1) * 3 + (x + 1)] = -1;
                    break;
                    case (AVERAGE): // TODO
                        pixelBox [(y+1) * 3 + (x + 1)] = img.Pixel(img_x, img_y);
                    case (CENTER):
                        pixelBox [(y+1) * 3 + (x + 1)] = img.Pixel(img_x, img_y);
                        break;
                    default:
                        throw std::logic_error("Not implemented");
                }
            }
        }
    }

    return pixelBox;

}

void Filter::processImage( Image & img ) const {

    // construct copy only if really needed.
    // this could be optimized by only having copy of the bytes we need (size of PixelBox)
    // if(m_usePixelBlock)
    ImagePtr img_copy = img.copy();

    for(size_t y = 0; y < img.mHeight; y++){
        for(size_t x = 0; x < img.mWidth; x++){
            if (m_usePixelBlock) {
                imgData_t pixelBox = generatePixelBlock(*img_copy, x, y);
                img.Pixel(x, y) = processPixelBox(pixelBox);
            }
            else{
                img.Pixel(x, y) = processPixel(img.Pixel( x, y));
            }
        }
    }
}
