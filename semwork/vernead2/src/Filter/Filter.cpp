//
// Created by vernead2 on 30.04.20.
//

#include <stdexcept>
#include "Filter.h"

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

}
