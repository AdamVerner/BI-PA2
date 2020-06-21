//
// Created by vernead2 on 21.06.20.
//

#pragma once

#include <string>

#include "Image.h"

/** Load image from file.
 *  It tries every know format and returns shared pointer on success;
 *
 * @throws FileException on failure
 * */
ImagePtr LoadImage( const std::string & filename );


/**
 * Load lookup table from specified file
 *
 * @throws FileException when file loading fails.
 * */
std::string LoadLut(const std::string & filename);