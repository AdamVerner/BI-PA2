//
// Created by home-6 on 06.06.20.
//

#pragma once

#include <cstddef>
#include "dataTypes.h"
#include "CScaler/CScaler.h"

/** Pixel art scaling algorithm.
 * https://en.wikipedia.org/wiki/Hqx
 * http://forums.nesdev.com/viewtopic.php?p=82770#82770
 * https://pastebin.com/YXpmqvW5 (public domain)
 * */
class CScaler_HQX : public CScaler{
public:
    CScaler_HQX( size_t width, size_t height ): CScaler(width, height) { };

};