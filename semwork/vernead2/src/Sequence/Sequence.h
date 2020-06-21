//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include <vector>

#include "Image/Image.h"

class Sequence{
public:
    Sequence();

    void push_back(const Image &);
    Image & pop_back(const Image &);
    Image & operator[](size_t);
    void insert(size_t);
    void size();

private:
    std::vector<ImagePtr> images;

};