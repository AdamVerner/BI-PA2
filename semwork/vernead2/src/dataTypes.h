//
// Created by vernead2 on 12.05.20.
//

#pragma once

#include <vector>
#include <cstdint>
#include <memory>

/** Pixel memory representation. */
struct pixel_t{
    uint8_t r; /**< Red channel */
    uint8_t g; /**< Green channel */
    uint8_t b; /**< Blue channel */
    uint8_t a; /**< Alpha channel */

    /** Init as RGBA */
    inline pixel_t( uint8_t r, uint8_t g, uint8_t b,  uint8_t a) : r(r), g(g), b(b), a(a) { };

    /** Init as RGB */
    inline pixel_t( uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) { };

    /** Init as BW */
    inline pixel_t( uint8_t g) : r(g), g(g), b(g), a(255) { };

    inline pixel_t() : r(0), g(0), b(0), a(255) { };

    /**
     * Alpha composition algorithm sourced from Ohio state university
     * http://web.cse.ohio-state.edu/~parent.1/classes/581/Lectures/13.TransparencyHandout.pdf
     *
     * Basic alpha blending is used
     * Alpha pre-computation is not needed as we are not rendering pixels often.
     * */
    pixel_t operator+(const pixel_t & rhs) const {
        return pixel_t(
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
    pixel_t & operator+=(const pixel_t & rhs) {
        this->r = (this->r * this->a / 255) + (rhs.r * rhs.a * (255 - this->a) / (255 * 255));
        this->g = (this->g * this->a / 255) + (rhs.g * rhs.a * (255 - this->a) / (255 * 255));
        this->b = (this->b * this->a / 255) + (rhs.b * rhs.a * (255 - this->a) / (255 * 255));
        this->a = this->a + (rhs.a * (255 - this->a) / 255);
        return *this;
    }

    bool operator==(const pixel_t& rhs){ return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a; }

    /** Calculate grayscale value*/
    uint8_t getGray() const { return (this->r * 0.3 + this->g * 0.59 + this->b * 0.11) * a / 255; }

    void merge(const pixel_t & other){
        r = r/2 + other.r/2;
        g = g/2 + other.g/2;
        b = b/2 + other.b/2;
        a = a/2 + other.a/2;
    }


} __attribute__((packed, aligned(1)));


// typedef uint8_t pixel_t;
typedef std::vector<pixel_t> imgData_t;
