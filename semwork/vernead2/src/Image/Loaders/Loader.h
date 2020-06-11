//
// Created by vernead2 on 08.06.20.
//

#pragma once

#include <string>
#include <memory>

bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}

/*
std::unique_ptr<Image> getImageFromFilename(const std::string &, ImageType = AUTO);
*/

Image_ASCII LoadImage(const std::string & filename){

    if (ends_with(filename, ".ascii")){
        return Image_ASCII(filename);
    }
    else if (ends_with(filename, ".png")){

    }
    else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg")){

    }
    else throw std::logic_error("Cannot autodetect image based on filename");

    return {"asd"};
}
