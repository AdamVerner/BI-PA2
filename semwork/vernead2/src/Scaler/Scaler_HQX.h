//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include <cstddef>

/** Pixel art scaling algorithm.
 * https://en.wikipedia.org/wiki/Hqx
 * http://forums.nesdev.com/viewtopic.php?p=82770#82770
 * https://pastebin.com/YXpmqvW5 (public domain)
 * */
class Scaler_HQX : public Scaler{
public:
    Scaler_HQX( size_t width, size_t height ): Scaler(width, height) { };

};