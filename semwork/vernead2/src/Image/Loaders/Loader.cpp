//
// Created by vernead2 on 08.06.20.
//

#include <vector>
#include <fstream>

#include "Loader.h"

bool ends_with( std::string const & value, std::string const & ending ) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}

ImageType ImageTypeFromFilename( const std::string & filename ) {
    if (ends_with(filename, ".ascii"))
        return ASCII;
    else if (ends_with(filename, ".png"))
        return PNG;
    else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg"))
        return JPG;
    return UNKNOWN;
    // TODO try exif information
}

std::shared_ptr<Image> LoadImage( const std::string & filename, const ImageType & type ) {
    ImageType imgType = type;

    if (imgType == AUTO || imgType == UNKNOWN)
        imgType = ImageTypeFromFilename(filename);

    switch(imgType){
        case(JPG):
            return std::shared_ptr<Image>(new Image_JPG(filename));
        case(PNG):
            return std::shared_ptr<Image>(new Image_PNG(filename));
        case(ASCII):
            return std::shared_ptr<Image>(new Image_ASCII(filename));
        default:
            throw FileException("Can't deduce type from filename (" + filename + ")");
    }

}
