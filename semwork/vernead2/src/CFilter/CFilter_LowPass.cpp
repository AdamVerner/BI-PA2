//
// Created by vernead2 on 06.06.20.
//

#include "CFilter/CFilter_LowPass.h"

pixel_t CFilter_LowPass::processPixelBox( pixel_t box [PX_BOX_SIZE][PX_BOX_SIZE]  ) const {

    pixel_t sum = 0;

    for(int y = 0; y < PX_BOX_SIZE; y++)
        for(int x = 0; x < PX_BOX_SIZE; x++)
            sum += box[y][x] / (PX_BOX_SIZE * PX_BOX_SIZE);
    return sum;
}
