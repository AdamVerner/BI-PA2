//
// Created by vernead2 on 30.04.20.
//

#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "Image.h"

extern const char ASCIITranslation [256] =
        R"($$$$@@@@%%%%8888&&&&WWWWMMMM####****ooooaaaahhhhkkkkbbbbddddppppqqqqwwwwmmmmZZZZ0000Q)"
        R"(QQQLLLLJJJJUUUUYYYYXXXXzzzzccccvvvvuuuuxxxxrrrrjjjjfffftttt////||||(((())))1111{{}}[[)"
        R"(]]????----____++++~~~~<<<<>>>>iiii!!!!llllIIII;;;;::::,,,""""^^^^''''````....        )"
        // TODO less repeating chars
;




inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}


std::unique_ptr<CImage> getImageFromFilename(const std::string & filename, CImageType type) {

    if(type == AUTO ){
        if (ends_with(filename, ".ascii")) type = ASCII;
        else if (ends_with(filename, ".png")) type = PNG;
        else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg")) type = JPG;
        else throw std::logic_error("Cannot autodetect image based on filename");
    }

    switch (type){
        case(ASCII):
            return std::make_unique<CImage_ASCII>(filename);
        case(PNG):
            return std::make_unique<CImage_PNG>(filename);
        case(JPG):
            return std::make_unique<CImage_JPG>(filename);
        default:
            throw std::logic_error("Invalid type");
    }
}

std::ostream & operator<<(std::ostream & os, const CImage & img) {
    os << "CImage <" << img.mName << " " << img.mHeight << " x " << img.mWidth << ">";
    return os;
}

imgDataRow_t CImage::getRow(size_t idx) const {
    return mData.at(idx);
}

size_t CImage::getHeight() const {
    return mHeight;
}

size_t CImage::reverseLUTLookup(const char c) const {
    // TODO optimize

    auto const stringLUT = std::string(LUT);

    auto const first = stringLUT.find_first_of(c);
    auto const last = stringLUT.find_first_of(c);

    if(first == std::string::npos || last == std::string::npos) throw std::logic_error("invalid LUT format");

    return (first + last) / 2;
}

CImage_ASCII::CImage_ASCII(const std::string & filename){
    mName = filename;

    std::ifstream src;
    src.open(filename, std::ios::in | std::ios::binary);

    if (! src.is_open()) throw std::logic_error("Cannot open file " + filename);

    std::string tmp;

    getline(src, tmp, '\n');

    int s = tmp.size() ;
    if ( s != 255) throw std::logic_error("invalid image format");
    if (strncmp(tmp.c_str(), LUT, 255) != 0) throw std::logic_error("different LUTs are not supported");
    // TODO add support for different LUTs


    // get first line so we can test that all the other lines are same width as per specification
    getline(src, tmp, '\n');
    mWidth = tmp.size();

    std::vector<uint8_t> tmpVec (mWidth);

    for(size_t x = 0; x < mWidth; x ++){
        tmpVec[x] = reverseLUTLookup(tmp[x]);
    }
    mData.push_back(tmpVec);

    while (getline(src, tmp, '\n')) {
        if (mWidth != tmp.size()) throw std::logic_error("line length differs");

        std::vector<uint8_t> tmpVec2 (mWidth);

        for(size_t x = 0; x < mWidth; x ++){
            tmpVec2[x] = reverseLUTLookup(tmp[x]);
        }
        mData.push_back(tmpVec2);
    }
    mHeight = mData.size();
}
