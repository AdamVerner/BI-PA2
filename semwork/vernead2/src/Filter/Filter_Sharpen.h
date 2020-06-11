//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"

/**
 * Sharpen filter.
 * Increase the contrast between bright and dark regions which brings out features.
 * */
class Filter_Sharpen : public FilterKernel {
public:
    Filter_Sharpen( double weight = 1 ) : FilterKernel( { -1/9, -1/9, -1/9, -1/9, weight, -1/9, -1/9, -1/9, -1/9 } ) { }
};
