//
// Created by vernead2 on 13.05.20.
//

#pragma once

#include <exception>
#include <ostream>

/** Something went wrong with program.
 *  Don't throw, only derive. Use as last resort when catching children is not needed.
 * */
class BaseException : public std::exception{
public:
    /* Call to `this->print` and return */
    friend std::ostream & operator<< (std::ostream & oss, const BaseException& c) { c.print(oss); return oss; }

private:
    /** just subclass this */
    virtual void print(std::ostream & where) const;
};

class FileException : public BaseException{

};

class ImageFormatException : public FileException{

};

class UnsupportedFileFormatException : public ImageFormatException{

};

class InvalidInputException : public BaseException{

};



