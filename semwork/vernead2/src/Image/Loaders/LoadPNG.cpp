//
// Created by home-6 on 08.06.20.
//

#include <png.h>
#include <cstdarg>
#include <string>
#include <iostream>
#include <vector>

#include "LoadPNG.h"



void abort_( const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}


void LoadPNG(const std::string & filename){
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
