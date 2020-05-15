//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include "Image.h"

class CSequence{
public:
    CSequence();

    void push_back(const CImage &);
    CImage & pop_back(const CImage &);
    CImage & operator[](size_t);

};