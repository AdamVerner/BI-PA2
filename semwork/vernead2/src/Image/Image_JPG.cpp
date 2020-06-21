//
// Created by vernead2 on 14.06.20.
//

#include "../Exceptions.h"
#include "../Constants.h"
#include "Image_JPG.h"
#include "FileWrap.h"

std::unique_ptr<JSAMPLE[]> Image_JPG::getRawData( ) {

    std::unique_ptr<JSAMPLE []> rawData(new JSAMPLE [mHeight * mWidth * 4]);
    for(size_t i = 0; i < mWidth*mHeight; i++) {
        rawData[i*4  ] = mData[i].r;
        rawData[i*4+1] = mData[i].g;
        rawData[i*4+2] = mData[i].b;
        rawData[i*4+3] = mData[i].a;
    }
    return rawData;
}

Image_JPG::Image_JPG( const std::string & filename ) : filename(filename) {
    jerr = jpegErrorManager();

    FileWrap fw(filename.c_str(), "rb");
    JPGDecWrap jpg( jerr );

    jerr.pub.error_exit = jpegErrorExit;
    jpeg_stdio_src(&jpg.cinfo, fw.fp);
    jpeg_read_header(&jpg.cinfo, TRUE);
    jpeg_start_decompress(&jpg.cinfo);

    // TODO support for RGBA
    if (jpg.cinfo.output_components != 3) { // only RGB images supported
        throw std::logic_error("Only RGB images are supported");
    }

    mWidth = jpg.cinfo.output_width;
    mHeight = jpg.cinfo.output_height;


    unsigned int row_stride = mWidth * jpg.cinfo.output_components;
    auto data = new uint8_t[mWidth * mHeight * jpg.cinfo.output_components];
    long idx = 0;

    // read the image line by line
    while (jpg.cinfo.output_scanline < mHeight) {
        JSAMPROW buffer[1] = {(JSAMPROW) (data + idx)};
        jpeg_read_scanlines(&jpg.cinfo, buffer, 1);
        idx += row_stride;
    }

    jpeg_finish_decompress(&jpg.cinfo);

    ParseRawData(data, jpg);

}

void Image_JPG::save( ) {

    FileWrap fw(filename.c_str(), "wb");
    JPGComWrap jpg( jerr );

    jpg.cinfo.image_width = mWidth;
    jpg.cinfo.image_height = mHeight;
    jpg.cinfo.input_components = 4;		/* # of color components per pixel */
    jpg.cinfo.in_color_space = JCS_EXT_RGBA;

    jpeg_set_defaults(&jpg.cinfo);
    jpeg_set_quality(&jpg.cinfo, JPG_QUALITY, true);

    std::unique_ptr<JSAMPLE []> rawData = getRawData();

    jpeg_stdio_dest(&jpg.cinfo, fw.fp);
    jpeg_start_compress(&jpg.cinfo, TRUE);

    while (jpg.cinfo.next_scanline < jpg.cinfo.image_height) {
        JSAMPROW row_pointer = &(rawData)[jpg.cinfo.next_scanline * mWidth * 4];
        (void) jpeg_write_scanlines(&jpg.cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&jpg.cinfo);
}

void Image_JPG::saveAs( const std::string & fn ) {
    this->filename = fn;
    save();
}

void Image_JPG::jpegErrorExit( j_common_ptr cinfo ) {

    char what[JMSG_LENGTH_MAX];
    ( *(cinfo->err->format_message) ) (cinfo, what);

    throw FileException(what);

}

std::shared_ptr<std::FILE> Image_JPG::make_file( const char * f, const char * flags ) {
    std::FILE * const fp = std::fopen(f, flags);
    return fp ? std::shared_ptr<std::FILE>(fp, std::fclose) : std::shared_ptr<std::FILE>();
}

void Image_JPG::ParseRawData( uint8_t * data, const Image_JPG::JPGDecWrap & wrap ) {

    mData = imgData_t(mWidth * mHeight, 0);

    for(size_t i = 0; i < mWidth*mHeight; i++) {
        mData[i].r = data[i*3];
        mData[i].g = data[i*3 + 1];
        mData[i].b = data[i*3 + 2];
        mData[i].a = 255;
    }

    delete[] data;

}

Image_JPG::JPGDecWrap::JPGDecWrap( jpegErrorManager & jerr ) {
    cinfo = jpeg_decompress_struct();
    cinfo.err = jpeg_std_error(&jerr.pub);
    jpeg_create_decompress(&cinfo);
}

Image_JPG::JPGDecWrap::~JPGDecWrap( ) {
    jpeg_destroy_decompress(&cinfo);
}

Image_JPG::JPGComWrap::JPGComWrap(jpegErrorManager & jerr ) {
    cinfo = jpeg_compress_struct();
    cinfo.err = jpeg_std_error(&jerr.pub);
    jpeg_create_compress(&cinfo);
}

Image_JPG::JPGComWrap::~JPGComWrap( ) {
    jpeg_destroy_compress(&cinfo);
}

