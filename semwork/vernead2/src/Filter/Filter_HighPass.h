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
    Filter_HighPass( double weight = 2 ) : FilterKernel( { -1./9, -1./9, -1./9,
                                         -1./9,  weight, -1./9,
                                         -1./9, -1./9, -1./9} ) { }

};