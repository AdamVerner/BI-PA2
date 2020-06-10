//
// Created by home-6 on 09.06.20.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include "../src/dataTypes.h"

/**
 *  Test basic functionality of pixels
 *
 *
 *
 * */
int main(){

    // Print out sizes for debugging purposes
    std::cout << "sizeof( pixel_t<uint8_t > ) =       " << sizeof(pixel_t<uint8_t >) << std::endl;
    std::cout << "sizeof( pixel_t<uint16_t > ) =      " << sizeof(pixel_t<uint16_t >) << std::endl;
    std::cout << "sizeof( pixel_bw_t<uint8_t > ) =    " << sizeof(pixel_bw_t<uint8_t >) << std::endl;
    std::cout << "sizeof( pixel_bw_t<uint16_t > ) =   " << sizeof(pixel_bw_t<uint16_t >) << std::endl;
    std::cout << "sizeof( pixel_rgb_t<uint8_t > ) =   " << sizeof(pixel_rgb_t<uint8_t >) << std::endl;
    std::cout << "sizeof( pixel_rgb_t<uint16_t > ) =  " << sizeof(pixel_rgb_t<uint16_t >) << std::endl;
    std::cout << "sizeof( pixel_rgba_t<uint8_t > ) =  " << sizeof(pixel_rgba_t<uint8_t >) << std::endl;
    std::cout << "sizeof( pixel_rgba_t<uint16_t > ) = " << sizeof(pixel_rgba_t<uint16_t >) << std::endl;


    /* black&white pixels can be used as uint_8t (or any other if depth specified) */

    /* Black & White pixel operations */
    {
        pixel_bw_t<> p1( 10 );
        pixel_bw_t<> p2 = 20;

        pixel_bw_t<> p3 = p1 + p2;
        assert( p1 == 10 );
        assert( p2 == 20 );
        assert( p3 == 15 );

        pixel_bw_t<> p4( p2 + p1 );

        assert( p1 == 10 );
        assert( p2 == 20 );
        assert( p4 == 15 );

        std::ostringstream oss;

        oss.clear( );
        oss << p3;

        assert( oss.str( )[0] == default_lut[pixel_bw_t<>( 15 ).getGray( )] );
    }

    /* Do the same for pixel_rgb_t */
    {
        pixel_rgb_t<> p1( 10 );
        pixel_rgb_t<> p2 = 20;

        // black-white similar API
        pixel_rgb_t<> p3 = p1 + p2;
        assert( p1 == 10 );
        assert( p2 == 20 );
        assert( p3 == 15 );

        pixel_rgb_t<> p4(0, 255, 250);
        pixel_rgb_t<> p5(0, 0, 200);
        pixel_rgb_t<> p6 = p4 + p5;

        assert(p6.r == 0);
        assert(p6.g == 127);
        assert(p6.b == 225);

    }

    /* Test RGBA alpha composition  */
    {
        // TODO test composition
        pixel_rgba_t<> p1( 10 );
        pixel_rgba_t<> p2 = 20;
        p1.a = 127;
        p2.a = 127;

        // test alpha calculation
        pixel_rgba_t<> p3 = p1 + p2;
        assert( p1 == pixel_rgba_t<>(10, 10, 10, 127) );
        assert( p2 == pixel_rgba_t<>(20, 20, 20, 127) );
        assert( p3 == pixel_rgba_t<>(8, 8, 8, 190) );

    }

    assert(pixel_rgba_t<uint8_t>(-1) == UINT8_MAX);

}