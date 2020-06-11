//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"
#include "FilterKernel.h"

/**
 * Low pass filter.
 * Calculate an average value from the whole kernel
 * */
class Filter_LowPass : public FilterKernel {
public:
    Filter_LowPass( ) : FilterKernel( { 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9 } ) { }
};