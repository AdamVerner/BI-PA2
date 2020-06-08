//
// Created by home-6 on 06.06.20.
//

#pragma once

#include "CImage/CImage.h"
#include "dataTypes.h"

class CFilter_LowPass: public CFilter {
public:
    CFilter_LowPass(): CFilter(AVERAGE){ }; // : CFilter() {}

private:
    /** Low pass filtering. The output is calculated as an average of all pixels inside the PixelBox.
     * */
    pixel_t processPixelBox(pixel_t [PX_BOX_SIZE][PX_BOX_SIZE]) const override;
};