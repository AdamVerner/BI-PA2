//
// Created by vernead2 on 02.05.20.
//

#include <cassert>

#include "CImage/CImage.h"

int main(){


    assert(ends_with("file.ASCII", ".ASCII"));
    assert(ends_with("file.ascii", ".ASCII"));
    assert(ends_with("file.aSCii", ".ASCII"));
    assert(!ends_with("file.NOTASCII", ".ASCII"));
    assert(!ends_with("file.png", ".ASCII"));


}