//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include <cstdio>
#include <cstdint>
#include <vector>
#include <ostream>
#include <bits/unique_ptr.h>

#include "CFilter/CFilter.h"
#include "CScaler/CScaler.h"
#include "dataTypes.h"

extern const char ASCIITranslation [257]; /**< LUT for raw to ASCII translation */

enum CImageType{ JPG, PNG, ASCII, AUTO };


/**
 * Base Image class.
 * Holds image information, can perform transformations, filtering and other image editing processes
 */
class CImage{
public:

    CImage() = default;
    CImage(const CImage & );
    explicit CImage(const std::string &);

    /**
     * Create CImage from raw data. e.g. `CImage(3, 3, " * *** * ")` to crete a star.
     * */
    CImage(size_t, size_t, const char *);

    /**
     * Save Image to location.
     *
     *
     */
    bool save(const std::string);


    /**
     * Filter image using specified filter.
     * @param scaler
     * @see CFilter
     * */
    inline void applyFilter( const CFilter & filter ){ filter.processImage( *this ); }

    /**
     * Scale image to required size.
     * @param scaler instance of CScaler to scale the image with
     * @see CScaler
     */
    void applyScaler( const CScaler &);

    inline size_t getWidth() const { return mWidth; }
    inline size_t getHeight() const { return mHeight; }

    inline pixel_t getPixel(size_t x, size_t y) const { return mData.at(y).at(x); };
    inline void setPixel(size_t x, size_t y, pixel_t value) { mData.at(y).at(x) = value; };

    /**
     * Merge other image into itself.
     * Each pixel is averaged between these two.
     * */
    bool merge(const CImage &);

    uint8_t LUTLookup(size_t idx) const{ return LUT[idx]; }

    friend std::ostream &operator<<(std::ostream &, const CImage &);

protected:

    size_t reverseLUTLookup(char) const;

    std::string mName;   /**< original image filename. Can be None if sourced from terminal*/

    imgData_t mData;     /**< images RAW data */

    size_t mWidth = 0;   /**< image width */
    size_t mHeight = 0;  /**< image height */

    const char * LUT = ASCIITranslation; /**< lookup table for raw to ascii translation */

};


bool ends_with(const std::string &, const std::string &);

std::unique_ptr<CImage> getImageFromFilename(const std::string &, CImageType = AUTO);
