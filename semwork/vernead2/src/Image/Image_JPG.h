//
// Created by vernead2 on 14.06.20.
//

#pragma once

#include <csetjmp>
#include <string>
#include <stdexcept>
#include <vector>
#include <jpeglib.h>
#include <functional>

#include "../Exceptions.h"
#include "Image.h"

/** Image JPG
 * uses libjpeg to load data from JPEG image.
 * */
class Image_JPG: public Image{
public:

    explicit Image_JPG(const Image & img): Image(img) { }
    explicit Image_JPG(const std::string & filename);

    void save() override;

    void saveAs(const std::string & fn) override;

    std::shared_ptr<Image> copy() const override{ return std::make_shared<Image_JPG>(*this); }

private:

    /** Custom error manager for libjpeg */
    struct jpegErrorManager {
        struct jpeg_error_mgr pub;    /* "public" fields */
        jmp_buf setjmp_buffer;    /* for return to caller */
    };
    jpegErrorManager jerr{};

    /** Jpeg lib error handler */
    static void jpegErrorExit(j_common_ptr);


    std::unique_ptr<JSAMPLE[]> getRawData( );

    std::string filename;

    static std::shared_ptr<std::FILE> make_file(const char * f, const char * flags);

    /** wrapper around jpeg_decompress_struct.
     * jpeglib does dynamic alocation on its side, but we need to make sure it gets destroyed */
    struct JPGDecWrap{
        explicit JPGDecWrap( jpegErrorManager & );
        ~JPGDecWrap();
        jpeg_decompress_struct cinfo;
    };

    /** wrapper around jpeg_compress_struct.
     *@see JPGDecWrap
     * */
    struct JPGComWrap{
        explicit JPGComWrap( jpegErrorManager & );
        ~JPGComWrap();
        jpeg_compress_struct cinfo { };
    };



    void ParseRawData( uint8_t * data, const JPGDecWrap & wrap );
};
