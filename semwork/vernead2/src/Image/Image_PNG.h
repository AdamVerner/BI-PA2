//
// Created by home-6 on 14.06.20.
//

#pragma once

#include <png.h>
#include <cstdarg>
#include <string>
#include <iostream>
#include <vector>

#include "Exceptions.h"
#include "Image.h"

class Image_PNG: public Image{
public:

    explicit Image_PNG(const Image & img): Image(img) { }

    explicit Image_PNG(const std::string & filename);

    void save() override;
    void saveAs(const std::string & fn) override;

    std::shared_ptr<Image> copy() const override{ return std::make_shared<Image_PNG>(*this); }

private:

    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;


    void parseRawData( const std::unique_ptr<png_byte[]> & rawData );

    /**
     * Normalize PNG for easier loading.
     * Convert all input types to RGBA.
     *
     * */
    void normalizePNG();

    std::string filename;

    /** Load PNG into this from filename. Throw Exceptions when something bad happens.
     * */
    void LoadPNG();

    /** Throw exception to interrupt the flow*/
    static inline void pngReadError(png_structp png_ptr, png_const_charp error_msg){
        throw FileException("Failed reading PNG");
    }

};