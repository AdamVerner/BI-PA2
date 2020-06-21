//
// Created by home-6 on 21.06.20.
//

#include <Exceptions.h>
#include "FileWrap.h"

FileWrap::FileWrap( const char * f, const char * flags ) {
    fp = std::fopen(f, flags);
    if(!fp) throw FileException("Can't open file");
}

FileWrap::~FileWrap( ) {
    if(fp) fclose(fp);
}