//
// Created by home-6 on 21.06.20.
//

#pragma once

#include <cstdio>

struct FileWrap{
    FileWrap(const char *, const char * flags);
    ~FileWrap();
    FILE * fp;
};