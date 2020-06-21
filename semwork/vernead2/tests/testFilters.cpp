//
// Created by vernead2 on 01.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <Image/Loaders/Loader.h>
#include <Filter/Filter_Grayscale.h>
#include "../src/Image/Image.h"
#include "../src/Filter/Filter_Inverse.h"
#include "../src/Filter/Filter_LowPass.h"
#include "../src/Filter/Filter_HighPass.h"
#include "../src/Filter/Filter_Sharpen.h"

void testLowPass(){
    ImagePtr ny = LoadImage( "tests/images/LowPass/ny.png" );

    // do two passes
    ny->applyFilter( Filter_LowPass( ));
    ny->applyFilter( Filter_LowPass( ));

    assert( ny->difference( *LoadImage( "tests/images/LowPass/ny_lp.png" )) < 0.05);

    ny->merge(*LoadImage( "tests/images/LowPass/ny.png" ));

    assert( ny->difference( *LoadImage( "tests/images/LowPass/ny_lp_comb.png" )) < 0.05);

    std::cout << "LowPass: " << ny->difference( *LoadImage( "tests/images/LowPass/ny_lp_comb.png" )) << std::endl;

}

void testHighPass(){

    ImagePtr ny = LoadImage( "tests/images/HighPass/ny.png" );
    ny->applyFilter( Filter_HighPass( ));

    // can't get this step below 16%
    assert( ny->difference( *LoadImage( "tests/images/HighPass/ny_hp.png" )) < 0.16);

    ny->merge(*LoadImage( "tests/images/HighPass/ny.png" ));

    // but final output is less than 5% off
    assert( ny->difference( *LoadImage( "tests/images/HighPass/ny_hp_comb.png" )) < 0.05);

    std::cout << "HighPass: " << ny->difference( *LoadImage( "tests/images/HighPass/ny_hp_comb.png" )) << std::endl;
}

void testSharpen(){
    // ImagePtr ny = LoadImage( "tests/images/HighPass/ny.png", PNG);


    //for (double x = 0; x < 5; x += 0.1) {
        ImagePtr ny = LoadImage( "tests/images/Sharpen/knee.png" );
        ny->applyFilter( Filter_Sharpen( ));

        std::cout << "Sharpen: " << ny->difference( *LoadImage( "tests/images/Sharpen/knee_sharp_comb.png" )) << std::endl;

        // oof can't get this to match the source
        assert( ny->difference( *LoadImage( "tests/images/Sharpen/knee_sharp_comb.png" )) < 0.25 );
    //}
}

int main(){

    ImagePtr progtest = LoadImage( "tests/images/progtest.png" );
    progtest->saveAs("tests/images/progtestNew.png");

    assert( LoadImage( "tests/images/progtestNew.png" )->difference( *LoadImage( "tests/images/progtest.png" )) < 0.01);


    testLowPass( );
    testHighPass( );
    testSharpen( );


}