//
// Created by vernead2 on 08.06.20.
//

#pragma once

#include <memory>
#include <string>
#include <cstring>
#include <cmath>
#include <memory>
#include <iostream>

#include "../Constants.h"
#include "../dataTypes.h"
#include "../Filter/Filter.h"
#include "../Plugins/Plugin.h"

enum ImageType{ JPG, PNG, ASCII, AUTO, UNKNOWN };


/**
 * Base Image class.
 * Holds image information, can perform transformations, filtering and other image editing processes
 */
class Image{
public:

    Image( ) = default;

    Image( const Image & other)= default;

    Image(size_t, size_t);

    /** Create Image from string data. e.g. `Image(3, 3, " * *** * ")` to crete a star.  */
    Image(size_t width, size_t height, const char * src );

    /**Filter image using specified filter.
     * @param filter
     * @see Filter
     * */
    inline void applyFilter( const Filter & filter ){ filter.processImage( *this ); }

    /** Apply Plugin on the Image
     * @param plugin instance of plugin to edit the image with
     * @see Plugin
     * */
    inline void applyPlugin( const Plugin & plugin){ plugin.processImage(*this); };

    inline size_t getWidth() const { return mWidth; }

    inline size_t getHeight() const { return mHeight; }
    inline pixel_t & Pixel(size_t x, size_t y) { return mData.at(y * mWidth + x); }
    inline const pixel_t & Pixel(size_t x, size_t y) const { return mData.at(y * mWidth + x); }

    /** Transforms a pixel to ASCII representation */
    char LUTLookup(const pixel_t & idx) const;

    /**
     * Merge two images of same size.
     * @return false on failure
     * */
    bool merge( const Image & other);


    /**
     * Calculate difference between two images
     * @return difference normalized to 0-1 where 0 means same, 1 means totally different
     * */
    double difference(const Image & other) const;

    friend std::ostream &operator<<(std::ostream & os, const Image & img);

    /** Transform a ASCII letter into pixel */
    pixel_t reverseLUTLookup(char c) const;

    virtual void save() {};
    virtual void saveAs(const std::string & ) {};

    /** Create new copy of class */
    inline virtual std::shared_ptr<Image> copy() const{ return std::make_shared<Image>(*this); }

    /** Resize canvas to specific size. if enlarging, set background. */
    void resizeCanvas(size_t width, size_t height, pixel_t background = 0);

    /** Generate histogram.
     * @returns vector of pixel count.
     * */
    std::vector<size_t> getHistogram(int steps = 255) const;


    size_t mWidth = 0;   /**< image width */
    size_t mHeight = 0;  /**< image height */

    std::string mLUT = DEFAULT_LUT;
protected:

    imgData_t mData {}; /**< images RAW data */
    /**< Lookup table for pixel to ascii translation */
};

typedef std::shared_ptr<Image> ImagePtr;
