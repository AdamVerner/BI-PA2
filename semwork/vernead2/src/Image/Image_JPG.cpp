//
// Created by home-6 on 14.06.20.
//

#include "Image_JPG.h"
#include "Exceptions.h"

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

    struct jpeg_decompress_struct cinfo{};
    struct jpegErrorManager jerr{};
    FILE * fp;


    if ((fp = fopen(filename.c_str(), "rb")) == nullptr) {
        throw FileException("failed to open Image");
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpegErrorExit;


    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress (&cinfo);


    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_src(&cinfo, fp);

    /* Step 3: read file parameters with jpeg_read_header() */
    (void) jpeg_read_header(&cinfo, TRUE);


    /* Step 4: set parameters for decompression */
    /* In this example, we don't need to change any of the defaults set by
     * jpeg_read_header(), so we do nothing here.
     */

    /* Step 5: Start decompressor */
    (void) jpeg_start_decompress(&cinfo);

    if (cinfo.output_components != 3) { // only RGB images supported in this example
        jpeg_destroy_decompress(&cinfo);
        fclose(fp);
        throw std::logic_error("Only RGB images are supported");
    }

    unsigned int row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */

    mWidth = cinfo.output_width;
    mHeight = cinfo.output_height;

    auto * data = new uint8_t[mWidth * mHeight * 3];
    long counter = 0;

    // step 6, read the image line by line
    while (cinfo.output_scanline < cinfo.output_height) {
        JSAMPROW buffer[1] = {(JSAMPROW) (data + counter)};
        jpeg_read_scanlines(&cinfo, buffer, 1);
        counter += row_stride;
    }
    /* Step 7: Finish decompression */

    (void) jpeg_finish_decompress(&cinfo);
    /* Step 8: Release JPEG decompression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);

    /* And we're done! */
    mData = imgData_t(mWidth * mHeight, 0);


    for(size_t i = 0; i < mWidth*mHeight; i++) {
        mData[i].r = data[i*3];
        mData[i].g = data[i*3 + 1];
        mData[i].b = data[i*3 + 2];
        mData[i].a = 255;
    }

    delete[] data;

}

void Image_JPG::save( ) {

    jpeg_compress_struct cinfo{};
    jpeg_error_mgr jerr{};

    FILE * outfile = nullptr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    cinfo.image_width = mWidth;
    cinfo.image_height = mHeight;
    cinfo.input_components = 4;		/* # of color components per pixel */
    cinfo.in_color_space = JCS_EXT_RGBA;

    jpeg_set_defaults(&cinfo);

    std::unique_ptr<JSAMPLE []> rawData = getRawData();

    if ((outfile = fopen(filename.c_str(), "wb")) == nullptr)
        throw FileException("Can't open " + filename +" for writing");

    jpeg_stdio_dest(&cinfo, outfile);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {

        JSAMPROW row_pointer = &(rawData)[cinfo.next_scanline * mWidth * 4];
        (void) jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */

    /* Step 7: release JPEG compression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&cinfo);

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
