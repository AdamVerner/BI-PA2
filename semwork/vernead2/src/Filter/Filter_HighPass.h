//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"
#include "FilterKernel.h"

/**
 * High pass filter
 * */
class Filter_HighPass : public FilterKernel {
public:
    Filter_HighPass( ) : FilterKernel( { 0, -1/4.0, 0, -1/4.0, -1/4.0, -1/4.0, 0, -1/4.0, 0 } ) { }
};