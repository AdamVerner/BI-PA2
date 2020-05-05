//
// Created by vernead2 on 30.04.20.
//

#pragma once

#include "Image.h"
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


class ViewPort_ANSI: public ViewPort_Terminal{
public:
    void displayImage(const CImage &) override;
    // TODO
};

class FileViewPort: public ViewPort{


};

class ViewPort_NCurses: public ViewPort{
    // TODO
};