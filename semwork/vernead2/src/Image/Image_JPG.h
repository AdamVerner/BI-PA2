//
// Created by vernead2 on 14.06.20.
//

#pragma once

#include <csetjmp>
#include <string>
#include <stdexcept>
#include <vector>
#include <jpeglib.h>

#include "Exceptions.h"
#include "Image.h"

class Image_JPG: public Image{
public:

    explicit Image_JPG(const Image & img): Image(img) { }
    explicit Image_JPG(const std::string & filename);

    void save() override;

    void saveAs(const std::string & fn) override;

    std::shared_ptr<Image> copy() const override{ return std::make_shared<Image_JPG>(*this); }


private:

    struct my_error_mgr {
        struct jpeg_error_mgr pub;    /* "public" fields */
        jmp_buf setjmp_buffer;    /* for return to caller */
    };

    std::unique_ptr<JSAMPLE[]> getRawData( );
    std::string filename;
};