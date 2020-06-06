#include <dataTypes.h>
#include <CImage/CImage.h>
#include <CImage/CImage_ASCII.h>
#include <CImage/CImage_PNG.h>
#include <CImage/CImage_JPG.h>

/* One extra byte for null terminator (eases up things) */
extern const char ASCIITranslation [257] =
        R"(####$$$$@@@@%%%%8888&&&&WWWWMMMM####****ooooaaaahhhhkkkkddddppppqqqqwwwwmmmmZZZZ0000QQQQLLLLJJJJUUUUYYYYXXXXzzzzccccvvvvuuuuxxx)"
        R"())))1111{{}}[[]]????<<<<>>>>iiii!!!!++++;;;;::::~~~~~~~~--------,,,,,,,,""""""""^^^^^^^^''''''''````````........______           )"
;


imgDataRow_t CImage::getRow(size_t idx) const {
    return mData.at(idx);
}

/**
 * reverse LUT Lookup.
 * Find out index
 *
 * */
size_t CImage::reverseLUTLookup(const char c) const {
    // TODO optimize

    auto const stringLUT = std::string(LUT);

    auto const first = stringLUT.find_first_of(c);
    auto const last = stringLUT.find_first_of(c);

    if(first == std::string::npos || last == std::string::npos) throw std::logic_error("character not in LUT");

    return (first + last) / 2;
}

void CImage::scale(const CScaler & scaler) {
    scaler.processData(mData, mWidth, mHeight);
}



std::ostream & operator<<(std::ostream & os, const CImage & img) {
    os << "CImage <" << img.mName << " " << img.mHeight << " x " << img.mWidth << ">";
    return os;
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

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}