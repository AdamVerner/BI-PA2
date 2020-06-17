//
// Created by vernead2 on 08.06.20.
//

#pragma once

#include <string>
#include <memory>

#include "Image/Image.h"
#include "Image/Image_JPG.h"
#include "Image/Image_PNG.h"
#include "Image/Image_ASCII.h"

bool ends_with(std::string const & value, std::string const & ending);

ImageType ImageTypeFromFilename(const std::string & filename);

std::shared_ptr<Image> LoadImage(const std::string & filename, const ImageType & type);

void SaveAs(const std::shared_ptr<Image> & imgPtr, const std::string & filename, ImageType imgType);