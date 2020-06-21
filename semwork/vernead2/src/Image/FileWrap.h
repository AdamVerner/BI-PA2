//
// Created by home-6 on 21.06.20.
//

#pragma once

#include <cstdio>

/** Resource manager for old c-style file pointers
 * */
struct FileWrap{
    FileWrap(const char *, const char * flags);
    ~FileWrap();
    FILE * fp;
};