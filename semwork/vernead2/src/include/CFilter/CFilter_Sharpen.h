//
// Created by home-6 on 06.06.20.
//

#pragma once

#include "CImage/CImage.h"
#include "dataTypes.h"

class CFilter_Sharpen: public CFilter{
public:
    CFilter_Sharpen(): CFilter(AVERAGE){ }; // : CFilter() {}

private:
    /** Simple high pass filter implementation.
     * ```
     * +----+----+----+
     * |-1/9|-1/9|-1/9|
     * +----+----+----+
     * |-1/9| +1 |-1/9|
     * +----+----+----+
     * |-1/9|-1/9|-1/9|
     * +----+----+----+
     * ```
     * */
    pixel_t processPixelBox(pixel_t [3][3]) const override;

};
