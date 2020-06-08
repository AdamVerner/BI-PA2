//
// Created by home-6 on 12.05.20.
//

#pragma once

#include <vector>
#include <cstdint>

#define PIXEL_MAX UINT8_MAX

/* must be even so that the pixel that's being examined is right in the middle */
#define PX_BOX_SIZE 3


typedef uint8_t pixel_t;
typedef std::vector<std::vector<pixel_t>> imgData_t;
typedef std::vector<pixel_t> imgDataRow_t;

