//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Filter.h"
#include "FilterKernel.h"

/**
 * High pass filter
 * */
class Filter_Edge : public FilterKernel {
public:
    Filter_Edge( ) : FilterKernel( { +1, 0, -1, +1, 0, -1, -+1, 0, -1 } ) { }

};