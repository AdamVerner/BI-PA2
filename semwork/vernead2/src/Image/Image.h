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

#include "../dataTypes.h"
#include "../Scaler/Scaler.h"
#include "../Filter/Filter.h"

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


    /**Filter image using specified filter.
     * @param filter
     * @see Filter
     * */
    inline void applyFilter( const Filter & filter ){
        filter.processImage( *this );
    }

    /**Scale image to required size.
     * @param scaler instance of Scaler to scale the image with
     * @see Scaler
     * */
    inline void applyScaler( const Scaler & scaler){ scaler.processData(mData, mWidth, mHeight); };

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

    /** Create Image from string data. e.g. `Image(3, 3, " * *** * ")` to crete a star.  */
    Image(size_t width, size_t height, const char * src );

    /** Transform a ASCII letter into pixel */
    pixel_t reverseLUTLookup(char c) const;

    virtual void save() {};
    virtual void saveAs(const std::string & ) {};

    virtual std::shared_ptr<Image> copy() const{ return std::make_shared<Image>(*this); }


    size_t mWidth = 0;   /**< image width */
    size_t mHeight = 0;  /**< image height */

protected:

    imgData_t mData {}; /**< images RAW data */
    std::string mLUT = DEFAULT_LUT; /**< Lookup table for pixel to ascii translation */
};

typedef std::shared_ptr<Image> ImagePtr;