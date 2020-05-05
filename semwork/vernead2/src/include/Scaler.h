//
// Created by vernead2 on 01.05.20.
//

#pragma once
#include <cstddef>

class CScaler{

    CScaler(size_t width, size_t height): reqWidth(width), reqHeight(height) {}

private:
    size_t reqWidth;
    size_t reqHeight;
};