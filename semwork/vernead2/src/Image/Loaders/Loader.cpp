//
// Created by vernead2 on 08.06.20.
//

#include <vector>
#include <fstream>

#include "Loader.h"
#include "../Image.h"

/* TODO move to cmd.cpp */


/*
 *
std::unique_ptr<Image> getImageFromFilename(const std::string & filename, ImageType type) {

    if(type == AUTO ){
        if (ends_with(filename, ".ascii")) type = ASCII;
        else if (ends_with(filename, ".png")) type = PNG;
        else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg")) type = JPG;
        else throw std::logic_error("Cannot autodetect image based on filename");
    }

    switch (type){
        case(ASCII):
            return std::make_unique<Image_ASCII>(filename);
        case(PNG):
            return std::make_unique<Image_PNG>(filename);
        case(JPG):
            return std::make_unique<Image_JPG>(filename);
        default:
            throw std::logic_error("Invalid type");
    }
}

*/
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

void SaveAs( const std::shared_ptr<Image> & imgPtr, const std::string & filename, ImageType imgType ) {

    if (imgType == AUTO)
        imgType = ImageTypeFromFilename(filename);

    Image * imgCopy = nullptr;

    switch(imgType){
        case(JPG):
            imgCopy = new Image_JPG(*imgPtr);
            break;
        case(PNG):
            imgCopy = new Image_PNG(*imgPtr);
            break;
        case(ASCII):
            imgCopy = new Image_ASCII(*imgPtr);
            break;
        default:
            throw FileException("Can't deduce type from filename (" + filename + ")");
    }

    imgCopy->saveAs(filename);

}
