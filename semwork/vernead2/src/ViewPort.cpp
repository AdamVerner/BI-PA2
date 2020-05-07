//
// Created by vernead2 on 30.04.20.
//

#include <sys/ioctl.h>
#include <iostream>
#include <thread>
// #include <unistd.h>

#include "ViewPort.h"

void ViewPort_Terminal::displayImage(const class CImage & img ) {

    for (size_t y = 0; y < img.getHeight(); y++){
        for(const auto & x: img.getRow(y))
            output << img.LUT[x] << " ";
        output << std::endl;
    }

}

void ViewPort_Terminal::displaySequence(const CSequence &) {

}

void ViewPort_Terminal::clear() {

}


void ViewPort_ANSI::displayImage(const CImage & image) {

    struct winsize w{};
    ioctl(fileno(stdout), TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    for (int y = 0; y < w.ws_row; y++){
        std::cout << "\033[" << y << ";" << 0 << "H" << std::string(w.ws_col, '.') << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}

