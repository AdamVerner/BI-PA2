/**
 * Most of filtering was sourced from
 *   https://northstar-www.dartmouth.edu/doc/idl/html_6.2/Filtering_an_Imagehvr.html
 *   https://northstar-www.dartmouth.edu/doc/idl/html_6.2/Sharpening_an_Image.html
 * */

#pragma once


#include "../dataTypes.h"
class Image;

/**
 * Filter an Image.
 * Base class to for image filtering process.
 *
 * There are two ways an image can be filtered.
 * Either per-pixel or wia search box, where every new pixel is calculated using it's nearest neighbours.
 * If `m_usePixelBlock` is set as true, the filter will use `processPixelBox` method to evaluate the filter.
 * @see SidePolicy
 * otherwise the `processPixel` is used.
 *
 * When creating new Filters, the class should be reference in the menu as option.
 * @see
 *
 * */
class Filter{
public:

    /**
     * Control the behaviour of pixel box construction.
     * If the part of the pixel box is not inside the image, the values are calculated to fit into the box.
     * */
    enum SidePolicy {
        CENTER,     /**< Value of the center pixel is used */
        AVERAGE,  /**< Value is averaged from nearest pixels */
        ZERO,     /**< Pixels are set to zero */
        MAX,      /**< Maximum value that can be represented by pixel is used */
    };


    Filter() = default;
    explicit Filter(enum SidePolicy sidePolicy): m_usePixelBlock(true), m_sidePolicy(sidePolicy) {};

    /**
     * Take the image and modify each pixel according to the selected filter policy
     * */
    void processImage( Image & img ) const;



protected:
    bool m_usePixelBlock = false;

private:

    virtual pixel_t processPixel(pixel_t & p) const { return p; };
    virtual pixel_t processPixelBox(imgData_t box) const { return box[5]; };

    imgData_t generatePixelBlock( Image&, size_t, size_t) const;

    SidePolicy m_sidePolicy = ZERO;
};


