//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>
#include <CFilter/CFilter_Sharpen.h>

#include "CImage/CImage.h"
#include "CFilter/CFilter_Inverse.h"
#include "CScaler/CScaler_HQX.h"
#include "CFilter/CFilter_LowPass.h"
#include "CFilter/CFilter_HighPass.h"
#include "ViewPort.h"


int main(){

    std::ostringstream oss;
    ViewPort_Terminal ossView( oss);
    ViewPort_Terminal coutView( std::cout);

    CImage img(3, 3, " # ### # ");

    assert (img.getWidth() == 3);
    assert (img.getHeight() == 3);

    ossView.displayImage( img);

    assert(oss.str() == "  #  \n# # #\n  #  \n"); // spaces are inserted between each char


    img.applyFilter(CFilter_Inverse());
    ossView.displayImage( img);

    img.applyFilter(CFilter_Inverse());
    std::cout << img << std::endl;
    ossView.displayImage( img);

    img.applyScaler(CScaler(6, 6));
    std::cout << img << std::endl;
    ossView.displayImage( img);

    img.applyScaler(CScaler(3, 3));
    std::cout << img << std::endl;
    ossView.displayImage( img);

    img.applyScaler(CScaler(15, 15));
    std::cout << img << std::endl;
    coutView.displayImage( img);

    img.applyFilter(CFilter_LowPass());
    img.applyFilter(CFilter_HighPass());
    img.applyFilter(CFilter_Sharpen());

    coutView.displayImage( img);


    CImage first(3, 3, " # ### # ");
    CImage second(3, 3, " # ### # ");

    first.applyScaler(CScaler(15, 15));
    second.applyScaler(CScaler(15, 15));

    second.applyFilter(CFilter_Sharpen());

    first.merge(second);

    coutView.displayImage( first);


}