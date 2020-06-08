#include <dataTypes.h>
#include <CImage/CImage.h>
#include <CImage/CImage_ASCII.h>
#include <CImage/CImage_PNG.h>
#include <CImage/CImage_JPG.h>

/* One extra byte for null terminator (eases up things) */
extern const char ASCIITranslation [257] =
        R"(############%%%%8888&&&&WWWWMMMM####****ooooaaaahhhhkkkkddddppppqqqqwwwwmmmmZZZZ0000QQQQLLLLJJJJUUUUYYYYXXXXzzzzccccvvvvuuuuxxx)"
        R"())))1111{{}}[[]]????<<<<>>>>iiii!!!!++++;;;;::::~~~~~~~~--------,,,,,,,,""""""""^^^^^^^^''''''''````````........______           )"
;


/**
 * reverse LUT Lookup.
 * Find out index
 *
 * */
size_t CImage::reverseLUTLookup(const char c) const {
    // TODO optimize by pre-calculating the reverse lookup table(or save as map)

    auto const stringLUT = std::string(LUT);

    auto const first = stringLUT.find_first_of(c);
    auto const last = stringLUT.find_first_of(c);

    if(first == std::string::npos || last == std::string::npos) throw std::logic_error("character not in LUT");

    return (first + last) / 2;
}

void CImage::applyScaler( const CScaler & scaler) {
    scaler.processData(mData, mWidth, mHeight);
}

std::ostream & operator<<(std::ostream & os, const CImage & img) {
    os << "CImage <" << img.mName << " " << img.mHeight << " x " << img.mWidth << ">";
    return os;
}

CImage::CImage( const CImage & other) {
    mName = other.mName;
    mData = other.mData;
    mWidth = other.mWidth;
    mHeight = other.mHeight;

    LUT = other.LUT; // TODO copy the LUT

}

CImage::CImage( size_t width, size_t height, const char * src ) {

    mWidth = width;
    mHeight = height;
    mData = std::vector< std::vector<uint8_t> > (mHeight, std::vector<uint8_t>(mWidth, 0));

    for(size_t y = 0; y < mHeight; y++ )
        for( size_t x = 0; x < mWidth; x++ )
            mData[y][x] = reverseLUTLookup(src[y * width + x]);
}

bool CImage::merge( const CImage & other) {

    if(mWidth != other.mWidth || mHeight != other.mHeight)
        return false;

    for(size_t y = 0; y < mHeight; y++ )
        for( size_t x = 0; x < mWidth; x++ )
            mData[y][x] = (mData[y][x] + other.mData[y][x]) / 2;

    return true;
}

/* TODO move to cmd.cpp */
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

/* TODO move to cmd.cpp */
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}