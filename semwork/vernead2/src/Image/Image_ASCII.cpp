//
// Created by vernead2 on 14.06.20.
//



#include "Image.h"
#include "Image_ASCII.h"

void Image_ASCII::LoadFile( const std::string & filename ) {

    std::ifstream src;
    src.open(filename, std::ios::in | std::ios::binary);

    if (! src.is_open()) throw FileException("Cannot open file " + filename);


    // first line is LUT
    getline(src, mLUT, '\n');

    // TODO test mLUT
    std::string tmp;

    // get first line so we can test that all the other lines are same width as per specification
    getline(src, tmp, '\n');
    mWidth = tmp.size();

    // calculate the size of the file
    auto current = src.tellg();

    src.seekg (0, std::ios::end);
    auto end = src.tellg();
    src.seekg(current); //restore

    // calculate line count from width and file size (mWidth is image width without newline)
    mHeight = (end - current + mWidth + 1) / (mWidth + 1);

    // prepare data so that if they're valid, we can just move them.
    std::vector<pixel_t> stageData (mWidth * mHeight);

    // process tmp line
    for(size_t x = 0; x < mWidth; x ++) {
        stageData[x] = reverseLUTLookup(tmp[x]);
    }

    // process the rest of the file
    for(size_t y = 1; y < mHeight; y ++){
        for(size_t x = 0; x < mWidth; x ++) {
            char s = src.get();
            stageData[y * mWidth + x] = reverseLUTLookup(s);
        }
        if(src.get() != '\n') throw std::logic_error("line length differs");
    }

    mData = std::move(stageData);

}

void Image_ASCII::save( ) {

    std::cout << "Fake writing " << std::endl;
    //TODO
}
