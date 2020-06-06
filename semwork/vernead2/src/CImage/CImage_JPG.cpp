
#include <csetjmp>
#include <string>
#include <jpeglib.h>

#include <CImage/CImage_JPG.h>

struct my_error_mgr {
    struct jpeg_error_mgr pub;    /* "public" fields */
    jmp_buf setjmp_buffer;    /* for return to caller */
};


//-------------------------------------------------------------------------------------------------
void my_error_exit(j_common_ptr cinfo) {
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
    auto * myerr = (my_error_mgr *) cinfo->err;

    /* Always display the message. */
    /* We could postpone this until after returning, if we chose. */
    (*cinfo->err->output_message)(cinfo);

    /* Return control to the setjmp point */
    longjmp(myerr->setjmp_buffer, 1);
}


CImage_JPG::CImage_JPG(const std::string & fileName){
    mName = fileName;

    struct jpeg_decompress_struct cinfo{};
    struct my_error_mgr jerr{};
    FILE * fp;


    if ((fp = fopen(fileName.c_str(), "rb")) == nullptr) {
        throw std::logic_error("failed to open Image");
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    /* Establish the setjmp return context for my_error_exit to use. */

    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        fclose(fp);
        throw std::logic_error("failed to set jump");
    }

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

    // convert data to mData
    // mWidth * mHeight * 3

    mData = std::vector< std::vector<uint8_t> > (mHeight, std::vector<uint8_t>(mWidth, 0));

    for(size_t y = 0; y < mHeight; y++ ){

        for(size_t x = 0; x < mWidth; x++ ){

            size_t idx = sizeof(uint8_t) * (y * mWidth * 3 + x * 3);

            uint16_t avg = (data[ idx + 0 * sizeof(uint8_t) ]);
            avg +=         (data[ idx + 1 * sizeof(uint8_t) ]);
            avg +=         (data[ idx + 2 * sizeof(uint8_t) ]);

            avg /= 3;
            avg = 255 - avg;

            mData[y][x] = avg;

        }
    }
    delete[] data;

}



