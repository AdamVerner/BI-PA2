//
// Created by home-6 on 06.06.20.
//

#pragma once

#include "CImage/CImage.h"
#include "dataTypes.h"

class CFilter_HighPass: public CFilter{
public:
    CFilter_HighPass(): CFilter(AVERAGE){ }; // : CFilter() {}

private:
    /** Simple high pass filter implementation.
     * ```
     * +----+----+----+
     * | 0  |-1/4| 0  |
     * +----+----+----+
     * |-1/4| +2 |-1/4|
     * +----+----+----+
     * | 0  |-1/4| 0  |
     * +----+----+----+
     * ```
     * */
    pixel_t processPixelBox(pixel_t [3][3]) const override;

};