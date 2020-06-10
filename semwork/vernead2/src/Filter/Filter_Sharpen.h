//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

template <typename ColorSpace>
class Filter_Sharpen: public Filter<ColorSpace>{
public:
    Filter_Sharpen()=default; // : Filter() {}

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
    ColorSpace processPixelBox(ColorSpace [3][3]) const override;

};
