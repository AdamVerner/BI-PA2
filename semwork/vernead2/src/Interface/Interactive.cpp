
#include <iostream>
#include <climits>
#include <functional>
#include <memory>
#include <Plugins/Plugin_Rotate.h>
#include <Plugins/Plugin_Scaler.h>

#include "Image/Loaders/Loader.h"
#include "Filter/Filter_Edge.h"
#include "Filter/Filter_Grayscale.h"
#include "Filter/Filter_LowPass.h"
#include "Filter/Filter_HighPass.h"
#include "Filter/Filter_Inverse.h"
#include "Filter/Filter_Sharpen.h"
#include "Interface/Interactive.h"
#include "Image/Image.h"

#include "Selector.h"

namespace interactive {

/** Prompt the user for Image location. */
    std::string promptLocation( ) {
        std::string location;
        std::cout << "Location: " << std::endl;
        std::cin >> location;
        return location;
    }

/** Prompt user for integer and range verify it. */
    int PromptIntegerValue( const std::string & name, int min, int max ) {
        std::cout << name << ": ";
        int value;
        while( !promptInteger( value ) || value < min || value > max )
            std::cout << "Invalid value." << std::endl;
        return value;
    }

/** Prompt user about new image size and background  */
    ImagePtr CreateNewImage( ) {
        int width = PromptIntegerValue( "Image Width", 0 );
        int height = PromptIntegerValue( "Image Height", 0 );
        return std::make_shared<Image>( width, height );
    }


/** Prompt the user to input existing image location, which is then loaded into mem. */
    ImagePtr GetExistingImage( ) {
        while( true ) {
            std::string location = promptLocation( );
            try { return std::make_shared<Image_PNG>( location ); }
            catch( BaseException & e ) {
                try { return std::make_shared<Image_JPG>( location ); }
                catch( BaseException & e ) {
                    try {
                        return std::make_shared<Image_ASCII>( location );
                    }
                    catch( BaseException & e ) {
                        std::cout << "Failed Loading Image" << std::endl;
                    }
                }
            }
        }
    }

    ImagePtr GetImageFromUser( ) {

        Selector s;
        ImagePtr img;
        s.Add( 1, "NEW", [&]( ) { img = CreateNewImage( ); } );
        s.Add( 4, "Existing", [&]( ) { img = GetExistingImage( ); } );
        s.prompt( "Do you want to create new Image or open an existing one?" );

        return img;

    }

    void SetPixelPrompt( const ImagePtr & img ) {

        int x, y, value;

        std::cout << "X: ";
        while( !promptInteger( x ) || x > (int) img->getWidth( ))
            std::cout << "Invalid coordinate." << std::endl;

        std::cout << "y: ";
        while( !promptInteger( y ) || y > (int) img->getHeight( ))
            std::cout << "Invalid coordinate." << std::endl;

        std::cout << "Grayscale value(0-255): ";
        while( !promptInteger( value ) || x > 255 || x < 0 )
            std::cout << "Invalid value." << std::endl;

        img->Pixel( x, y ) = value;

    }


    void EditImage( ImagePtr img ) {
        bool stop = false;
        Selector s2;
        s2.Add( 1, "Display", [&]( ) { std::cout << *img; } );
        s2.Add( 2, "Filters", [&]( ) { FilteringImage( img ); } );
        s2.Add( 3, "Plugins", [&]( ) { PluginImage( img ); } );
        s2.Add( 4, "Set Pixel", [&]( ) { SetPixelPrompt( img ); } );

        s2.Add( 5, "Save", [&]( ) { img->save( ); } );
        s2.Add( 6, "Save As", [&]( ) { SaveImagePrompt( img ); } );

        s2.Add( 10, "Return", [&]( ) { stop = true; } );


        while( !stop ) {
            s2.prompt( "What do you want to do?" );
        }


    }

    void PluginImage( ImagePtr img ) {

        Selector s;
        s.Add( 1, "Rotate", [&]( ) {
            img->applyPlugin( Plugin_Rotate((int) img->getWidth( ) / 2, (int) img->getHeight( ) / 2,
                                            PromptIntegerValue( "Angle", 0, 360 )));
        } );
        s.Add( 2, "Scale", [&]( ) {
            img->applyPlugin(
                    Plugin_Scaler( PromptIntegerValue( "New Width", 0 ), PromptIntegerValue( "New Height", 0 )));
        } );
        s.prompt( false );

    }

/** Prompts for selection of a filter and applies it if applicable */
    void FilteringImage( ImagePtr img ) {
// TODO prompt for filter values if available

        std::cout << "Which Filter do you want to use? " << std::endl;

        Selector s;
        s.Add( 1, "Edge", [&]( ) { img->applyFilter( Filter_Edge( )); } );
        s.Add( 2, "Grayscale", [&]( ) { img->applyFilter( Filter_Grayscale( )); } );
        s.Add( 3, "LowPass", [&]( ) { img->applyFilter( Filter_LowPass( )); } );
        s.Add( 4, "HighPass", [&]( ) { img->applyFilter( Filter_HighPass( )); } );
        s.Add( 5, "Inverse", [&]( ) { img->applyFilter( Filter_Inverse( )); } );
        s.Add( 6, "Sharpen", [&]( ) { img->applyFilter( Filter_Sharpen( )); } );
        s.prompt( false );

    }

    void SaveImagePrompt( ImagePtr & img ) {
        std::string location;
        std::cout << "Entry location to save the image: ";
        std::cin >> location;

        std::cout << "In order to be able to save the image as different format, you must change it first."
                  << std::endl;
        Selector s;
        s.Add( 1, "JPG", [&]( ) { img = std::make_shared<Image_JPG>( *img ); } );
        s.Add( 2, "PNG", [&]( ) { img = std::make_shared<Image_PNG>( *img ); } );
        s.Add( 3, "ASCII", [&]( ) { img = std::make_shared<Image_ASCII>( *img ); } );
        s.prompt( "Select new format: " );

        try {
            img->saveAs( location );
        }
        catch( const FileException & e ) {
            std::cout << "Couldn't save the file to specified location," << std::endl;
        }

        std::cout << "Image successfully saved to '" << location << "'" << std::endl;

    }


}