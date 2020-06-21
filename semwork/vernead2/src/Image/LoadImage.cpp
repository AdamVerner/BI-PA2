//
// Created by vernead2 on 21.06.20.
//


#include <string>

#include "Image.h"
#include "Image_PNG.h"
#include "Image_JPG.h"
#include "Image_ASCII.h"
#include "LoadImage.h"


ImagePtr LoadImage( const std::string & filename ) {
    try {
        return std::make_shared<Image_PNG>( filename );
    }
    catch( BaseException & e ) {
        try {
            return std::make_shared<Image_JPG>( filename );
        }
        catch( BaseException & e ) {
            try {
                return std::make_shared<Image_ASCII>( filename );
            }
            catch( BaseException & e ) {
                throw FileException("Failed Loading Image ('" + filename + "')");
            }
        }
    }
}

std::string LoadLut( const std::string & filename ) {
    std::ifstream src;
    src.open(filename, std::ios::in | std::ios::binary);

    src.seekg (0, std::ios::end);
    auto end = src.tellg();
    src.seekg(0, std::ios::beg); //restore

    if(end > 256)
        throw BaseException("Can't load LUT from File");

    std::string str;
    str.assign((std::istreambuf_iterator<char>(src)), std::istreambuf_iterator<char>());
    return str;
}
