//
// Created by vernead2 on 08.06.20.
//

#pragma once

#include <string>
#include <cstring>
#include <cmath>
#include <memory>
#include "../dataTypes.h"
#include "../Scaler/Scaler.h"
#include "../Filter/Filter.h"

enum ImageType{ JPG, PNG, ASCII, AUTO };

/**
 * Base Image class.
 * Holds image information, can perform transformations, filtering and other image editing processes
 */
class Image{
public:

    Image( ) = default;

    Image( const Image & other);

    Image(size_t, size_t);

    virtual bool save(){ return false; };

    /**Filter image using specified filter.
     * @param filter
     * @see Filter
     * */
    inline void applyFilter( const Filter & filter ){ filter.processImage( *this ); }

    /**Scale image to required size.
     * @param scaler instance of Scaler to scale the image with
     * @see Scaler
     * */
    inline void applyScaler( const Scaler & scaler){ scaler.processData(mData, mWidth, mHeight); };

    inline size_t getWidth() const { return mWidth; }
    inline size_t getHeight() const { return mHeight; }

    inline pixel_t & Pixel(size_t x, size_t y) { return *mData.at(y * mWidth + x); }
    inline const pixel_t & Pixel(size_t x, size_t y) const { return *mData.at(y * mWidth + x); }

    /** Transforms a pixel to ASCII representation */
    char LUTLookup(const pixel_t & idx) const{
        size_t max = pixel_bw_t(-1).getGray();
        size_t step = mLUT.length();
        size_t gray = idx.getGray();
        return mLUT[gray * step / max ];
    }

    /**
     * Merge two images of same size.
     * @return false on failure
     * */
    bool merge( const Image & other){

        if(mWidth != other.mWidth || mHeight != other.mHeight)
            return false;

        for(size_t y = 0; y < mHeight; y++ )
            for( size_t x = 0; x < mWidth; x++ )
                *mData[y * mWidth + x] += *other.mData[y * mWidth + x];
        return true;
    }


    friend std::ostream &operator<<(std::ostream & os, const Image & img){
        os << "Image <" << img.mHeight << " x " << img.mWidth << ">" << std::endl;

        for (size_t y = 0; y < img.mHeight; y++){
            for( size_t x = 0; x < img.mWidth ; x++ ) {
                os << img.LUTLookup( img.Pixel( x, y ));
                if (x != img.mWidth - 1) os << " "; // TODO instead of printing space, rescale image by ~60%
            }
            os << std::endl;
        }
        return os;
    }



protected:

    imgData_t mData; /**< images RAW data */
    std::string mLUT = DEFAULT_LUT; /**< Lookup table for pixel to ascii translation */

    size_t mWidth;   /**< image width */
    size_t mHeight;  /**< image height */
};


class ImageBW: public Image{
public:

    ImageBW(){ };

    ImageBW( const Image & other ): Image( other ) { };

};

class Image_ASCII: public ImageBW{
public:

    /** Create Image from string data. e.g. `Image(3, 3, " * *** * ")` to crete a star.  */
    Image_ASCII(size_t width, size_t height, const char * src ){
        mWidth = width;
        mHeight = height;
        mLUT = DEFAULT_LUT;
        mData = std::vector<std::shared_ptr<pixel_t>>(width * height);
        for(size_t y = 0; y < mHeight; y++ )
            for( size_t x = 0; x < mWidth; x++ )
                mData[y * mWidth + x] = std::shared_ptr<pixel_bw_t>(new pixel_bw_t(reverseLUTLookup(src[y * mWidth + x])));
    }

    /** Transform a ASCII letter into pixel */
    pixel_bw_t reverseLUTLookup(char c) const{
        // TODO optimize by pre-calculating the reverse lookup table(or save as map)

        uint8_t max = pixel_bw_t(-1).getGray();
        uint8_t lut_len = mLUT.length();

        uint8_t inc =  std::ceil((double)max / lut_len);
        uint8_t val = inc / 2; // start in the middle of the range

        for (const auto & l: mLUT){
            if(l == c) return {val};
            val += inc;
        }

        throw std::logic_error("character not in LUT");
    }


};

class ImageRGB{

};

class ImageRGBA{

};

class Image_PNG{
    std::string mName;   /**< original image filename. Can be None if sourced from terminal*/
};