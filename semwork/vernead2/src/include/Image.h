//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include <cstdio>
#include <cstdint>
#include <vector>
#include <ostream>
#include <bits/unique_ptr.h>


typedef std::vector<std::vector<uint8_t>> imgData_t;
typedef std::vector<uint8_t> imgDataRow_t;

#include "Filter.h"
#include "Scaler.h"

class CFilter;

extern const char ASCIITranslation [257]; /**< LUT for raw to ASCII translation */

enum CImageType{ JPG, PNG, ASCII, AUTO };

/**
 * Image class.
 * Holds image information, can perform transformations, filtering and other image editing processes
 */
class CImage{
public:

    CImage() = default;
    CImage(const CImage & );
    explicit CImage(const std::string &);

    void applyFilter(const CFilter &);

    /**
     * Scale image to required size
     * @param scaler instance of CScaler to scale the image with
     * @param w requested width
     * @param h requested height
     * @see CScaler
     */
    void scale(const CScaler & scaler, size_t w, size_t h);
    imgDataRow_t getRow(size_t) const;
    size_t getHeight() const;


    friend std::ostream &operator<<(std::ostream &, const CImage &);

    const char * LUT = ASCIITranslation;

protected:
    std::string mName;   /**< original image filename. Can be None */
    imgData_t mData;     /**< images RAW data */
    size_t mWidth = 0;   /**< image width */

    size_t mHeight = 0;  /**< image height */

    size_t reverseLUTLookup(char) const;

};

class CImage_ASCII: public CImage{
public:
    explicit CImage_ASCII(const std::string &);
};


class CImage_PNG: public CImage{
public:

    explicit CImage_PNG(const std::string &);

};


class CImage_JPG: public CImage{
public:
    explicit CImage_JPG(const std::string &);


};


bool ends_with(const std::string &, const std::string &);

std::unique_ptr<CImage> getImageFromFilename(const std::string &, CImageType = AUTO);
