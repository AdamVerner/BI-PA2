//
// Created by vernead2 on 21.06.20.
//


#include <string>
#include "LoadImage.h"

#include "Image.h"
#include "Image_PNG.h"
#include "Image_JPG.h"
#include "Image_ASCII.h"


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
