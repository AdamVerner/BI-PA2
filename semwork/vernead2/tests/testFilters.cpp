//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include "../src/Image/Image.h"
#include "../src/Filter/Filter_Inverse.h"
#include "../src/Filter/Filter_LowPass.h"
#include "../src/Filter/Filter_HighPass.h"
#include "../src/Filter/Filter_Sharpen.h"

int main(){

    std::ostringstream oss;
    Image img(3, 3, " # ### # ");

    assert (img.getWidth() == 3);
    assert (img.getHeight() == 3);

    oss << img;
    assert(oss.str() == "  #  \n# # #\n  #  \n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_Inverse());
    oss.clear();
    oss << img;
    assert(oss.str() == "#   #\n     \n#   #\n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_Inverse());
    oss.clear();
    oss << img;
    assert(oss.str() == "  #  \n# # #\n  #  \n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_LowPass());
    img.applyFilter(Filter_HighPass());
    img.applyFilter(Filter_Sharpen());

    std::cout << img;

    Image first(3, 3, " # ### # ");
    Image second(3, 3, " # ### # ");

    first.applyScaler(Scaler(15, 15));
    second.applyScaler(Scaler(15, 15));

    second.applyFilter(Filter_Sharpen());

    first.merge(second);

    std::cout << first;

}