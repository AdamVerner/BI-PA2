//
// Created by vernead2 on 08.06.20.
//

#pragma once

#include <string>
#include <memory>

bool ends_with( const std::string &, const std::string &);

/*
std::unique_ptr<Image> getImageFromFilename(const std::string &, ImageType = AUTO);
*/

std::shared_ptr<Image> LoadImage(const std::string & filename){

    if (ends_with(filename, ".ascii")){
        return std::shared_ptr<Image> ( new Image_ASCII(3, 3, "## ##    "));
    }
    else if (ends_with(filename, ".png")){
        return std::shared_ptr<Image> ( new Image_ASCII(3, 3, "## ##    "));
    }
    else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg")){
        return std::shared_ptr<Image> ( new Image_ASCII(3, 3, "## ##    "));
    }
    else throw std::logic_error("Cannot autodetect image based on filename");
}
