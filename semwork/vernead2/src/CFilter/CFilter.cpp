//
// Created by vernead2 on 30.04.20.
//

#include "CFilter/CFilter.h"
#include "CImage/CImage.h"

void CFilter::processImage( CImage & img ) const {

    CImage img_copy;
    // construct copy only if really needed.
    // this could be optimized by only having copy of the bytes we need (size of PixelBox)
    if(m_usePixelBlock)
        img_copy = CImage(img); // todo replace with operator= ?

    for(size_t y = 0; y < img.getHeight(); y++){
        for(size_t x = 0; x < img.getWidth(); x++){
            if (m_usePixelBlock) {
                pixel_t pixelBox [3][3];
                generatePixelBlock(img_copy, x, y, pixelBox);
                img.setPixel( x, y, processPixelBox(pixelBox));
            }
            else{
                img.setPixel(x, y, processPixel(img.getPixel(x, y)));
            }
        }
    }
}


void CFilter::generatePixelBlock( CImage & img, size_t img_x, size_t img_y, pixel_t pixelBox [PX_BOX_SIZE][PX_BOX_SIZE] ) const {

    // TODO PX_BOX_SIZE variable size

    for(ssize_t y = -1; y <= 1; y++){
        for(ssize_t x = -1; x <= 1; x++){

            // Bound checking is done in `array.at` method.
            // This should be efficient because of the Zero-Cost Exception Model.
            try {
                pixelBox [y+1][x+1] = img.getPixel(img_x + x, img_y + y);
            }
            catch(std::out_of_range & err){
                switch(m_sidePolicy){
                    case(ZERO):
                        pixelBox [y+ 1][x+1] = 0;
                    break;
                    case(MAX):
                        pixelBox [y+1][x+1] = PIXEL_MAX;
                    break;
                    case (AVERAGE): // TODO
                    case (CENTER):
                        pixelBox[y+1][x+1] = img.getPixel(img_x, img_y);

                        break;
                    default:
                        throw std::logic_error("Not implemented");
                }
            }
        }
    }

}
