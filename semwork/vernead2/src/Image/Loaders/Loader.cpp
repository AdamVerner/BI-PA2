//
// Created by vernead2 on 08.06.20.
//

#include <vector>
#include <fstream>

#include "Loader.h"
#include "../Image.h"

/* TODO move to cmd.cpp */
bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}


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