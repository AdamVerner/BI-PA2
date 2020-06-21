//
// Created by vernead2 on 13.05.20.
//

#pragma once

#include <exception>
#include <ostream>

/** Something went wrong with program.
 *  Don't throw, only derive. Use as last resort when catching children is not needed.
 * */
class BaseException : public std::logic_error{
public:

    explicit BaseException(const std::string & what): std::logic_error(what) {}

    /* Call to `this->print` and return */
    friend std::ostream & operator<< (std::ostream & oss, const BaseException& c) { c.print(oss); return oss; }

private:
    /** just subclass this */
    virtual void print(std::ostream & os) const{ os << "Failed: " << this->what() << std::endl; }
};

class FileException : public BaseException{
public:
    explicit FileException(const std::string & what): BaseException(what) { }

private:
    void print( std::ostream & os) const override { os << "Reading File failed: " << this->what() << std::endl; }
};

class InvalidInputException : public BaseException{
public:
    explicit InvalidInputException(const std::string & what): BaseException(what) { }

private:
    void print( std::ostream & os) const override { os << "Invalid Input: " << this->what() << std::endl; }
};

class InvalidParam: public InvalidInputException{
public:
    explicit InvalidParam(const std::string & what): InvalidInputException(what) { }
private:
    void print( std::ostream & os) const override { os << "Parsing Failed: " << this->what() << std::endl; }
};


