//
// Created by vernead2 on 12.05.20.
//

#pragma once

#include <vector>
#include <cstdint>
#include <memory>

// #define DEFAULT_LUT R"(############%%%%8888&&&&WWWWMMMM####****ooooaaaahhhhkkkkddddppppqqqqwwwwmmmmZZZZ0000QQQQLLLLJJJJUUUUYYYYXXXXzzzzccccvvvvuuuuxxx))))1111{{}}[[]]????<<<<>>>>iiii!!!!++++;;;;::::~~~~~~~~--------,,,,,,,,""""""""^^^^^^^^''''''''````````........______           )"
#define DEFAULT_LUT "#@WLIoji+;:'\"_. "

const char * default_lut = DEFAULT_LUT;
char * global_lut = nullptr;


struct pixel_t{

    virtual pixel_t operator+(const pixel_t & rhs) const { return pixel_t(); }
    virtual pixel_t & operator+=(const pixel_t & rhs) { return *this; }

    inline friend std::ostream & operator<<(std::ostream & os, const pixel_t & px) {
        if (global_lut)
            os << global_lut[px.getGray()];
        else
            os << default_lut[px.getGray()];
        return os;
    }

    virtual uint8_t getGray() const { return 0; }

} __attribute__((packed, aligned(1)));


struct pixel_bw_t: public pixel_t {
    uint8_t b = 0; /**< Black channel */

    pixel_bw_t() = default;

    inline pixel_bw_t( uint8_t b ) { this->b = b; }
    virtual uint8_t getGray() const { return b; }


    pixel_bw_t operator+(const pixel_bw_t & rhs) const { return pixel_bw_t(b/2 + rhs.b/2); }
    pixel_bw_t & operator+=(const pixel_bw_t & rhs) { b = b/2 + rhs.b/2; return *this; }

    inline friend bool operator==(const pixel_bw_t& lhs, const pixel_bw_t& rhs){ return lhs.b == rhs.b; }


} __attribute__((packed, aligned(1)));


struct pixel_rgb_t: public pixel_t {
    uint8_t r; /**< Red channel */
    uint8_t g; /**< Green channel */
    uint8_t b; /**< Blue channel */

    pixel_rgb_t() = default;

    inline pixel_rgb_t( uint8_t b ) { this->r = b; this->g = b; this->b = b; }
    inline pixel_rgb_t( uint8_t r, uint8_t g, uint8_t b ) { this->r = r; this->g = g; this->b = b; }

    pixel_rgb_t operator+(const pixel_rgb_t & rhs) const { return pixel_rgb_t(r/2+rhs.r/2, g/2+rhs.g/2, b/2+rhs.b/2 ); }
    pixel_rgb_t & operator+=(const pixel_rgb_t & rhs) { r = r/2 + rhs.r/2; g = g/2 + rhs.g/2; b = b/2 + rhs.b/2; return *this; }

    bool operator==(const pixel_rgb_t& rhs){ return r == rhs.r && g == rhs.g && b == rhs.b; }

    uint8_t getGray() const { return (r * 0.33 + g * 0.33 + b * 0.33); }


} __attribute__((packed, aligned(1)));


struct pixel_rgba_t: public pixel_rgb_t{
    uint8_t a; /**< Alpha channel */

    inline pixel_rgba_t( uint8_t b ): pixel_rgb_t(b) { this->a = uint8_t(-1); }
    inline pixel_rgba_t( uint8_t r, uint8_t g, uint8_t b,  uint8_t a) : pixel_rgb_t(r, g, b) { this -> a = a; }

    /**
     * Alpha composition algorithm sourced from Ohio state university
     * http://web.cse.ohio-state.edu/~parent.1/classes/581/Lectures/13.TransparencyHandout.pdf
     *
     * Basic alpha blending is used
     * Alpha pre-computation is not needed as we are not rendering pixels often.
     * */
    pixel_rgba_t operator+(const pixel_rgba_t & rhs) const {
        return pixel_rgba_t(
                (this->r * this->a / 255) + (rhs.r * rhs.a * (255 - this->a) / (255 * 255)),
                (this->g * this->a / 255) + (rhs.g * rhs.a * (255 - this->a) / (255 * 255)),
                (this->b * this->a / 255) + (rhs.b * rhs.a * (255 - this->a) / (255 * 255)),
                this->a + (rhs.a * (255 - this->a) / 255)
                );
    }

    /**
     * Same as `operator+=`
     * @see pixel_rgba_t operator+
     * */
    pixel_rgba_t & operator+=(const pixel_rgba_t & rhs) {
        this->r = (this->r * this->a / 255) + (rhs.r * rhs.a * (255 - this->a) / (255 * 255));
        this->g = (this->g * this->a / 255) + (rhs.g * rhs.a * (255 - this->a) / (255 * 255));
        this->b = (this->b * this->a / 255) + (rhs.b * rhs.a * (255 - this->a) / (255 * 255));
        this->a = this->a + (rhs.a * (255 - this->a) / 255);
        return *this;
    }

    bool operator==(const pixel_rgba_t& rhs){ return pixel_rgb_t::operator==(rhs) && a == rhs.a; }

    uint8_t getGray() const { return (this->r * 0.33 + this->g * 0.33 + this->b * 0.33) * a / 255; }

    // TODO export to RGB with calculated background and such

} __attribute__((packed, aligned(1)));


// typedef uint8_t pixel_t;
typedef std::vector<std::shared_ptr<pixel_t>> imgData_t;
