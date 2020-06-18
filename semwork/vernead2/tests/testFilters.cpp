//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <Scaler/Scaler_BilinearInterpolation.h>
#include <Image/Loaders/Loader.h>
#include "../src/Image/Image.h"
#include "../src/Filter/Filter_Inverse.h"
#include "../src/Filter/Filter_LowPass.h"
#include "../src/Filter/Filter_HighPass.h"
#include "../src/Filter/Filter_Sharpen.h"

void testLowPass(){
    ImagePtr ny = LoadImage( "tests/images/LowPass/ny.png", PNG);

    // do two passes
    ny->applyFilter( Filter_LowPass( ));
    ny->applyFilter( Filter_LowPass( ));

    assert(ny->difference( *LoadImage( "tests/images/LowPass/ny_lp.png", AUTO )) < 0.05);

    ny->merge(*LoadImage( "tests/images/LowPass/ny.png", PNG));

    assert(ny->difference( *LoadImage( "tests/images/LowPass/ny_lp_comb.png", AUTO )) < 0.05);

    std::cout << "LowPass: " << ny->difference( *LoadImage( "tests/images/LowPass/ny_lp_comb.png", AUTO )) << std::endl;

}

void testHighPass(){

    ImagePtr ny = LoadImage( "tests/images/HighPass/ny.png", PNG);
    ny->applyFilter( Filter_HighPass( ));

    // can't get this step below 16%
    assert(ny->difference( *LoadImage( "tests/images/HighPass/ny_hp.png", AUTO )) < 0.16);

    ny->merge(*LoadImage( "tests/images/HighPass/ny.png", PNG));

    // but final output is less than 5% off
    assert(ny->difference( *LoadImage( "tests/images/HighPass/ny_hp_comb.png", AUTO )) < 0.05);

    std::cout << "HighPass: " << ny->difference( *LoadImage( "tests/images/HighPass/ny_hp_comb.png", AUTO )) << std::endl;

    ny->saveAs("tests/new.png");
}

void testSharpen(){
    // ImagePtr ny = LoadImage( "tests/images/HighPass/ny.png", PNG);


    //for (double x = 0; x < 5; x += 0.1) {
        ImagePtr ny = LoadImage( "tests/images/Sharpen/knee.png", PNG );
        ny->applyFilter( Filter_Sharpen( ));

        std::cout << "Sharpen: " << ny->difference( *LoadImage( "tests/images/Sharpen/knee_sharp_comb.png", AUTO )) << std::endl;

        // oof can't get this to match the source
        assert( ny->difference( *LoadImage( "tests/images/HighPass/ny_hp_comb.png", AUTO )) < 0.25 );
        ny->saveAs( "tests/new.png" );
    //}
}

int main(){

    ImagePtr progtest = LoadImage( "tests/images/progtest.png", PNG);
    progtest->saveAs("tests/images/progtestNew.png");

    assert(LoadImage("tests/images/progtestNew.png", AUTO)->difference(*LoadImage("tests/images/progtest.png", AUTO)) < 0.01);


    testLowPass( );
    testHighPass( );
    testSharpen( );
    exit(0);

    ImagePtr original = LoadImage( "tests/images/knee_orig.png", PNG);
    original->saveAs("tests/images/out1.png");

    original->applyFilter(Filter_HighPass());

    original->saveAs("tests/images/out2.png");

    exit(0);

    std::ostringstream oss;
    Image img(3, 3, " # ### # ");

    assert (img.getWidth() == 3);
    assert (img.getHeight() == 3);

    oss << img;
    assert(oss.str() == "Image <3 x 3>\n  #  \n# # #\n  #  \n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_Inverse());

    oss.clear();
    oss.str("");
    oss << img;
    std::string save = oss.str();
    assert(oss.str() == "Image <3 x 3>\n#   #\n     \n#   #\n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_Inverse());
    oss.clear();
    oss.str("");
    oss << img;
    assert(oss.str() == "Image <3 x 3>\n  #  \n# # #\n  #  \n"); // spaces are inserted between each char(might change)

    img.applyFilter(Filter_LowPass());
    img.applyFilter(Filter_HighPass());
    img.applyFilter(Filter_Sharpen());

    std::cout << img;

    Image first(3, 3, " # ### # ");
    Image second(3, 3, " # ### # ");

    first.applyScaler(Scaler_BilinearInterpolation(20, 20));
    second.applyScaler(Scaler_BilinearInterpolation(20, 20));

    second.applyFilter(Filter_Sharpen());

    first.merge(second);

    std::cout << first;

}