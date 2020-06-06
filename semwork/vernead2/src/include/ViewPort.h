//
// Created by vernead2 on 30.04.20.
//

/* wouldn't it be better to just overload `<<` instead ?  */

#pragma once

#include "CImage/CImage.h"
#include "Sequence.h"

class ViewPort{
public:

    ViewPort(const ViewPort &) = default;
    explicit ViewPort(std::ostream & os = std::cout): output(os) {};

    virtual void displayImage(const CImage &) = 0;
    virtual void displaySequence(const CSequence &) = 0;
    virtual void clear() = 0;

protected:

    std::ostream & output;

private:

};

class ViewPort_Terminal: public ViewPort{
public:
    explicit ViewPort_Terminal(std::ostream & os = std::cout): ViewPort(os) {};
    ViewPort_Terminal(const ViewPort_Terminal &) = default;

    void displayImage(const CImage &) override;
    void displaySequence(const CSequence &) override ;
    void clear() override ;


protected:


private:

};


/**
 * ANSI Terminal viewport.
 * ANSI control sequences from: http://www.termsys.demon.co.uk/vtansi.htm
 *
 * */
class ViewPort_ANSI: public ViewPort_Terminal{
public:
    void displayImage(const CImage &) override;
};

class FileViewPort: public ViewPort{


};
