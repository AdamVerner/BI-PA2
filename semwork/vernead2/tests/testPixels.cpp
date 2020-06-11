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
    std::cout << "sizeof( pixel_t<uint8_t > ) = " << sizeof(pixel_t) << std::endl;

    /* black&white pixels can be used as uint_8t (or any other if depth specified) */

    {
        pixel_t p1( 10 );
        pixel_t p2 = 20;

        // black-white similar API
        pixel_t p3 = p1 + p2;
        assert( p1 == 10 );
        assert( p2 == 20 );
        assert( p3 == 10 );

        p1.merge(p2);
        pixel_t pa(15);
        assert(p1 == pa);

        pixel_t p4(0, 255, 250);
        pixel_t p5(0, 0, 200);
        p4.merge(p5);

        assert(p4.r == 0);
        assert(p4.g == 127);
        assert(p4.b == 225);

    }

    /* Test RGBA alpha composition  */
    {
        // TODO test composition
        pixel_t p1( 10 );
        pixel_t p2 = 20;
        p1.a = 127;
        p2.a = 127;

        // test alpha calculation
        pixel_t p3 = p1 + p2;
        assert( p1 == pixel_t(10, 10, 10, 127) );
        assert( p2 == pixel_t(20, 20, 20, 127) );
        assert( p3 == pixel_t(8, 8, 8, 190) );

    }

    assert(pixel_t(-1) == UINT8_MAX);

}