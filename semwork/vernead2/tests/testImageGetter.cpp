//
// Created by vernead2 on 02.05.20.
//

#include <iostream>
#include <sstream>
#include <cassert>

#include "../src/dataTypes.h"
#include "../src/Image/Image.h"
#include "../src/Image/Loaders/Loader.h"

void testConstructionAndMerge( ) {
    Image img2( 3, 3, " # ### # " );
    Image img3( 3, 3, "## ##    " );

    std::stringstream oss;
    oss << img2;
    assert( oss.str( ) == "Image <3 x 3>\n  #  \n# # #\n  #  \n" );

    oss.str( "" );
    oss.clear( );
    oss << img3;
    assert( oss.str( ) == "Image <3 x 3>\n"
                          "# #  \n"
                          "# #  \n"
                          "     \n" );

    img2.merge( img3 );

    oss.str( "" );
    oss.clear( );
    oss << img2;
    assert( oss.str( ) == "Image <3 x 3>\n"
                          "i #  \n"
                          "# # i\n"
                          "  i  \n" );
}

void testAsciiParser( ) {

    ImagePtr img = LoadImage( "tests/img.ascii" );


    std::stringstream oss;
    oss << *img;
    assert( oss.str( ) == "Image <15 x 22>\n"
                          "# # #                                      \n"
                          "#     #                                    \n"
                          "#     #   #   # #       # # #         # # #\n"
                          "# # #     # #         #       #     #     #\n"
                          "#         #           #       #     #     #\n"
                          "#         #           #       #     #     #\n"
                          "#         #             # # #         # # #\n"
                          "                                          #\n"
                          "                                      # #  \n"
                          "                                           \n"
                          "  #         # # #       # # #       #      \n"
                          "# # #     #       #   #           # # #    \n"
                          "  #       # # # # #     # # #       #      \n"
                          "  #       #                   #     #      \n"
                          "    # #     # # #       # # #         # #  \n" );


}

void testPNGParser(){

    std::stringstream oss1, oss2;

    ImagePtr img = LoadImage( "tests/images/progtest.png" );
    oss1 << *img;

    img.get()->save();

    // test that the saved file will be loaded as same.
    ImagePtr new_img = LoadImage( "tests/images/progtest.png" );
    oss2 << *new_img;

    assert(oss1.str() == oss2.str());

    assert(oss1.str() == "Image <16 x 16>\n"
                         "# # # # # # # # # # # # # # # #\n"
                         "W W W W W # # # W W W W W # # #\n"
                         "W W W W W # # # W W W W W # # #\n"
                         "W W W W W # # # W W W W W # # #\n"
                         "W W W W W W # W W W W W W # # #\n"
                         "W W W W W W W W W W W W W W W #\n"
                         "# # W W W W W W W W W W W W W W\n"
                         "# # # W W W W W W W W W W W W W\n"
                         "# # W W W W W W W W W W W W W W\n"
                         "W W W W W W W W W W W W W W W #\n"
                         "W W W W W W W W W W W W W # # #\n"
                         "W W W W W W W W W W W W W # # #\n"
                         "W W W W W W W W W W W W W # # #\n"
                         "# # # # W W W W W # # # # # # #\n"
                         "# # # # W W W W W # # # # # # #\n"
                         "# # # # # W W W # # # # # # # #\n");

    assert(img->difference(*new_img) < 0.000001);

    remove("tests/new.png");

}

void testJPGParser(){

    ImagePtr img = LoadImage( "tests/progtest.jpeg" );

    std::cout << *img;
    Image img_ref( 16, 16, "################"
                           "WLWWW###WWWWW###"
                           "WWWWW###WWWWW###"
                           "WWWWW###WWWWW###"
                           "WWWWWW#WWWWLW###"
                           "WWWWWWWWWWWWWWW#"
                           "##WWWWWWWWWWWWLW"
                           "###WWWWWWWWWWWWW"
                           "##WWWWWWWWWWWWWW"
                           "WWWWWWWLWWWWLWW#"
                           "WWWWWWWWWWWWW###"
                           "WWWWWWWWWWWWL###"
                           "WWWWWWWWWWWWW###"
                           "####WWWWW#######"
                           "####WWWWW#######"
                           "#####WWW########");

    // difference is less than 2% (error in JPG encoding)
    assert(img->difference(img_ref) < 0.02);

}

int main( ) {
    testConstructionAndMerge( );
    testAsciiParser( );
    testPNGParser( );
    testJPGParser( );

    Image_JPG img("examples/kitty.jpg");
    Image_PNG i3( (Image(img)) );

    i3.saveAs("tests/new.png");

    std::cout << i3;

    ImagePtr img2 = LoadImage( "tests/progtest.jpeg" );
    ImagePtr img3 = img.copy();
    assert(img2.get() != img3.get());


}