//
// Created by vernead2 on 06.06.20.
//

#include "CFilter/CFilter_Inverse.h"

pixel_t CFilter_Inverse::processPixel( pixel_t value ) const {
    return PIXEL_MAX - value;
}
