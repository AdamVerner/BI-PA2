//
// Created by home-6 on 06.06.20.
//

#pragma once

#include "CImage/CImage.h"
#include "dataTypes.h"

class CFilter_Inverse: public CFilter {
public:
    CFilter_Inverse() = default; // : CFilter() {}

private:
    pixel_t processPixel(pixel_t value) const override ;

protected:

};