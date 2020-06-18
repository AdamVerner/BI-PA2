//
// Created by home-6 on 14.06.20.
//

#include "Image_PNG.h"

Image_PNG::Image_PNG( const std::string & filename ) : filename(filename) {


    // destroy the created structs no matter what happens
    try {

        // Create png structures we'll use for image Loading
        if( !(png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr )))
            throw BaseException( "png_create_read_struct" );
        if( !(info_ptr = png_create_info_struct( png_ptr )))
            throw BaseException( "png_create_info_struct" );
        if( setjmp( png_jmpbuf( png_ptr )))
            throw BaseException( "Error during init_io" );

        LoadPNG( );
    }
    catch (std::exception & e) {
        png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
        throw;
    }

    png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );

}

void Image_PNG::save( ) {

    FILE * fp = fopen(filename.c_str(), "wb");
    if (!fp) throw FileException("File could not be opened for reading");

    if( !(png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr )))
        throw BaseException( "png_create_read_struct" );
    if( !(info_ptr = png_create_info_struct( png_ptr )))
        throw BaseException( "png_create_info_struct" );
    if( setjmp( png_jmpbuf( png_ptr )))
        throw BaseException( "Error during init_io" );

    png_init_io(png_ptr, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
            png_ptr,
            info_ptr,
            mWidth, mHeight,
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png_ptr, info_ptr);

    std::unique_ptr<png_bytep[]> row_pointers(new png_bytep [mHeight]);
    std::unique_ptr<png_byte[]> rawData(new png_byte [png_get_rowbytes(png_ptr, info_ptr) * mHeight]);

    for(size_t i = 0; i < mWidth*mHeight; i++) {
        rawData[i*4  ] = mData[i].r;
        rawData[i*4+1] = mData[i].g;
        rawData[i*4+2] = mData[i].b;
        rawData[i*4+3] = mData[i].a;
    }

    for (size_t y = 0; y < mHeight; y++)
        row_pointers[y] = &rawData[y * png_get_rowbytes(png_ptr, info_ptr)];

    png_write_image(png_ptr, row_pointers.get());
    png_write_end(png_ptr, info_ptr);

    fclose(fp);

    png_destroy_write_struct(&png_ptr, &info_ptr);

}

void Image_PNG::parseRawData( const std::unique_ptr<png_byte[]> & rawData ) {

    this->mData = imgData_t(mWidth * mHeight, 0);
    uint8_t color_type = png_get_color_type(png_ptr, info_ptr);
    switch(color_type){
        case(PNG_COLOR_TYPE_RGB_ALPHA):
            for(size_t i = 0; i < mHeight * mWidth; i++){
                this->mData[i].r = rawData[i*4];
                this->mData[i].g = rawData[i*4+1];
                this->mData[i].b = rawData[i*4+2];
                this->mData[i].a = rawData[i*4+3];
            }
            break;
        case(PNG_COLOR_TYPE_RGB):
            for(size_t i = 0; i < mHeight * mWidth; i++){
                this->mData[i].r = rawData[i*3];
                this->mData[i].g = rawData[i*3+1];
                this->mData[i].b = rawData[i*3+2];
                this->mData[i].a = 255;
            }
        break;
        case(PNG_COLOR_TYPE_GRAY):

            for(size_t i = 0; i < mHeight * mWidth; i++){
                this->mData[i] = pixel_t(rawData[i]);
            }

            break;
        default:
            throw FileException("Invalid PNG Format");
    }
    // throw std::logic_error("Failed");
}

void Image_PNG::normalizePNG( ) {

    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth  = png_get_bit_depth(png_ptr, info_ptr);


    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);

    if(bit_depth == 16)
        png_set_strip_16(png_ptr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);

    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

    if (bit_depth == 16)
        png_set_strip_16(png_ptr);

}

void Image_PNG::LoadPNG() {

    /* open file and test for it being a png */
    FILE * fp = fopen(filename.c_str(), "rb");
    if (!fp) throw FileException("File could not be opened for reading");

    png_init_io(png_ptr, fp);

    png_read_info(png_ptr, info_ptr);

    // normalizePNG();

    png_read_update_info(png_ptr, info_ptr);


    // TODO support for different depths
    if (png_get_bit_depth(png_ptr, info_ptr) != 8)
        throw FileException("only images with depth 8 are supported");

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        throw FileException("Error during read_image");

    mWidth = png_get_image_width(png_ptr, info_ptr);
    mHeight = png_get_image_height(png_ptr, info_ptr);

    // structures required by libPNG

    std::unique_ptr<png_byte[]> rawData(new png_byte [png_get_rowbytes(png_ptr, info_ptr) * mHeight]);
    std::unique_ptr<png_bytep[]> row_pointers(new png_bytep [mHeight]);
    for (size_t y = 0; y < mHeight; y++)
        row_pointers[y] = &rawData[y * png_get_rowbytes(png_ptr, info_ptr)];

    png_read_image(png_ptr, row_pointers.get());
    png_read_end(png_ptr, info_ptr);

    fclose(fp);

    parseRawData( rawData );

}

void Image_PNG::saveAs( const std::string & fn ) {
    this->filename = fn;
    save();
}
