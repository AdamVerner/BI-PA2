#include <CImage/CImage_ASCII.h>
#include <cstring>
#include <fstream>


CImage_ASCII::CImage_ASCII( const std::string & filename){
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
