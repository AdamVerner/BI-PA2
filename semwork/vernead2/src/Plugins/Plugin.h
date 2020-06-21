//
// Created by vernead2 on 19.06.20.
//

#pragma once

#include <string>
#include <utility>

#include "../dataTypes.h"
class Image;

/**Image editing plugin base class.
 * Similar to filter, except that plugins can operate over the whole images, while Filters are only for value filtering.
 * */
class Plugin{
public:

    Plugin() = default;
    explicit Plugin(std::string name){ mName = std::move(name); }

    virtual void processImage( Image & img ) const = 0;

protected:

private:

    std::string mName;

};