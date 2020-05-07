#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <csetjmp>
#include <jpeglib.h>
#include <png.h>
#include <cstdarg>

#include "Image.h"

/* One extra byte for null terminator (eases up things) */
extern const char ASCIITranslation [257] =
        R"(####$$$$@@@@%%%%8888&&&&WWWWMMMM####****ooooaaaahhhhkkkkddddppppqqqqwwwwmmmmZZZZ0000QQQQLLLLJJJJUUUUYYYYXXXXzzzzccccvvvvuuuuxxx)"
        R"())))1111{{}}[[]]????<<<<>>>>iiii!!!!++++;;;;::::~~~~~~~~--------,,,,,,,,""""""""^^^^^^^^''''''''````````........______           )"
;




inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}


std::unique_ptr<CImage> getImageFromFilename(const std::string & filename, CImageType type) {

    if(type == AUTO ){
        if (ends_with(filename, ".ascii")) type = ASCII;
        else if (ends_with(filename, ".png")) type = PNG;
        else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg")) type = JPG;
        else throw std::logic_error("Cannot autodetect image based on filename");
    }

    switch (type){
        case(ASCII):
            return std::make_unique<CImage_ASCII>(filename);
        case(PNG):
            return std::make_unique<CImage_PNG>(filename);
        case(JPG):
            return std::make_unique<CImage_JPG>(filename);
        default:
            throw std::logic_error("Invalid type");
    }
}

std::ostream & operator<<(std::ostream & os, const CImage & img) {
    os << "CImage <" << img.mName << " " << img.mHeight << " x " << img.mWidth << ">";
    return os;
}

imgDataRow_t CImage::getRow(size_t idx) const {
    return mData.at(idx);
}

size_t CImage::getHeight() const {
    return mHeight;
}

size_t CImage::reverseLUTLookup(const char c) const {
    // TODO optimize

    auto const stringLUT = std::string(LUT);

    auto const first = stringLUT.find_first_of(c);
    auto const last = stringLUT.find_first_of(c);

    if(first == std::string::npos || last == std::string::npos) throw std::logic_error("invalid LUT format");

    return (first + last) / 2;
}

CImage_ASCII::CImage_ASCII(const std::string & filename){
    mName = filename;

    std::ifstream src;
    src.open(filename, std::ios::in | std::ios::binary);

    if (! src.is_open()) throw std::logic_error("Cannot open file " + filename);

    std::string tmp;

    getline(src, tmp, '\n');

    int s = tmp.size() ;
    if ( s != 255) throw std::logic_error("invalid image format");
    if (strncmp(tmp.c_str(), LUT, 255) != 0) throw std::logic_error("different LUTs are not supported");
    // TODO add support for different LUTs


    // get first line so we can test that all the other lines are same width as per specification
    getline(src, tmp, '\n');
    mWidth = tmp.size();

    std::vector<uint8_t> tmpVec (mWidth);

    for(size_t x = 0; x < mWidth; x ++){
        tmpVec[x] = reverseLUTLookup(tmp[x]);
    }
    mData.push_back(tmpVec);

    while (getline(src, tmp, '\n')) {
        if (mWidth != tmp.size()) throw std::logic_error("line length differs");

        std::vector<uint8_t> tmpVec2 (mWidth);

        for(size_t x = 0; x < mWidth; x ++){
            tmpVec2[x] = reverseLUTLookup(tmp[x]);
        }
        mData.push_back(tmpVec2);
    }
    mHeight = mData.size();
}

struct my_error_mgr {
    struct jpeg_error_mgr pub;    /* "public" fields */
    jmp_buf setjmp_buffer;    /* for return to caller */
};


//-------------------------------------------------------------------------------------------------
void my_error_exit(j_common_ptr cinfo) {
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
    my_error_mgr * myerr = (my_error_mgr *) cinfo->err;

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


void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}


CImage_PNG::CImage_PNG(const std::string & filename){
    mName = filename;

    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        abort_("[read_png_file] File %s could not be opened for reading", filename.c_str());
    fread(header, 1, 8, fp);

    if (png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, 8))
        abort_("[read_png_file] File %s is not recognized as a PNG file", filename.c_str());


    /* initialize stuff */
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (!png_ptr)
        abort_("[read_png_file] png_create_read_struct failed");

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        abort_("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    mWidth = png_get_image_width(png_ptr, info_ptr);
    mHeight = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    int number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[read_png_file] Error during read_image");

    auto * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * mHeight);
    for (size_t y = 0; y < mHeight; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, info_ptr);
    // png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    fclose(fp);

    std::cout << "row_pointers = " << row_pointers << std::endl;
    std::cout << "png_get_rowbytes(png_ptr, info_ptr) = " << png_get_rowbytes(png_ptr, info_ptr) << std::endl;
    std::cout << color_type << std::endl;
    std::cout << bit_depth << std::endl;
    std::cout << number_of_passes << std::endl;

    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
        abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
               "(lacks the alpha channel)");

    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
        abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
               PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));

    mData = std::vector< std::vector<uint8_t> > (mHeight, std::vector<uint8_t>(mWidth, 0));

    for (size_t y = 0; y < mHeight; y++) {
        png_byte* row = row_pointers[y];
        for (size_t x = 0; x < mWidth; x++) {
            png_byte* ptr = &(row[x*4]);

            std::cout << "Pixel at position [ " << x << " - " << y << " ] has RGBA values: " << +ptr[0] << " - " << +ptr[1] << " - " << +ptr[2] << " - " << +ptr[3] << std::endl;

            mData[y][x] += ptr[0] * 0.33;
            mData[y][x] += ptr[1] * 0.33;
            mData[y][x] += ptr[2] * 0.33;
            mData[y][x] = mData[y][x] * ptr[3] / 256;

            /* set red value to 0 and green value to the blue one */
        }
    }

}
