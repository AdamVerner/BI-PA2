//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include "Image/Image.h"

class CSequence{
public:
    CSequence();

    void push_back(const Image &);
    Image & pop_back(const Image &);
    Image & operator[](size_t);

};