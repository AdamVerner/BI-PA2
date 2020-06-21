//
// Created by vernead2 on 20.06.20.
//

#include "../Filter/Filter_Edge.h"
#include "../Filter/Filter_Grayscale.h"
#include "../Filter/Filter_LowPass.h"
#include "../Filter/Filter_HighPass.h"
#include "../Filter/Filter_Inverse.h"
#include "../Filter/Filter_Sharpen.h"
#include "../Plugins/Plugin_Rotate.h"
#include "../Plugins/Plugin_Resize.h"
#include "../Image/LoadImage.h"
#include "InteractiveImageInterface.h"
#include "Selector.h"

int InteractiveImageInterface::run( ) {

    GetImageFromUser();
    EditImage();

    return 0;
}

void InteractiveImageInterface::PromptImageSaveAs( ) {
    std::string location;
    out << "Entry location to save the image: ";
    std::cin >> location;

    Selector s;
    s.Add( 1, "JPG", [&]{ img = std::make_shared<Image_JPG>( *img ); } );
    s.Add( 2, "PNG", [&]{ img = std::make_shared<Image_PNG>( *img ); } );
    s.Add( 3, "ASCII", [&]{ img = std::make_shared<Image_ASCII>( *img ); } );
    s.promptCustom( "Select new Image format: " );

    try {
        img->saveAs( location );
    }
    catch( const FileException & e ) {
        out << "Couldn't save the file to specified location," << std::endl;
    }

    out << "Image successfully saved to '" << location << "'" << std::endl;

}

void InteractiveImageInterface::FilteringImage( ) {
    // TODO prompt for filter values if available

    out << "Which Filter do you want to use? " << std::endl;

    Selector s;
    s.Add( 1, "Edge", [&]{ img->applyFilter( Filter_Edge( )); } );
    s.Add( 2, "Grayscale", [&]{ img->applyFilter( Filter_Grayscale( )); } );
    s.Add( 3, "LowPass", [&]{ img->applyFilter( Filter_LowPass( )); } );
    s.Add( 4, "HighPass", [&]{ img->applyFilter( Filter_HighPass( )); } );
    s.Add( 5, "Inverse", [&]{ img->applyFilter( Filter_Inverse( )); } );
    s.Add( 6, "Sharpen", [&]{ img->applyFilter( Filter_Sharpen( )); } );
    s.prompt( false );
}

void InteractiveImageInterface::PluginImage( ) {

    Selector s;
    s.Add( 1, "Rotate", [&]{
        img->applyPlugin( Plugin_Rotate((int) img->getWidth( ) / 2, (int) img->getHeight( ) / 2,
                                        PromptIntegerValue( "Angle", 0, 360 )));
    } );
    s.Add( 2, "Scale", [&]{
        img->applyPlugin(
                Plugin_Resize( PromptIntegerValue( "New Width", 0 ), PromptIntegerValue( "New Height", 0 ))
        );
    } );
    s.prompt( false );
}

void InteractiveImageInterface::EditImage( ) {
    bool stop = false;
    Selector s2;
    s2.Add( 1, "Display", [&]{ out << *img; } );
    // TODO Image info
    s2.Add( 2, "Filters", [&]{ FilteringImage( ); } );
    s2.Add( 3, "Plugins", [&]{ PluginImage( ); } );
    s2.Add( 4, "Set Pixel", [&]{ SetPixelPrompt( ); } );

    s2.Add( 5, "Save", [&]{ img->save( ); } );
    s2.Add( 6, "Save As", [&]{ PromptImageSaveAs( ); } );

    s2.Add( 10, "Return", [&]{ stop = true; } );


    while( !stop ) {
        s2.promptCustom( "What do you want to do?" );
    }
}

void InteractiveImageInterface::SetPixelPrompt( ) {

    int x, y, value;

    x = PromptIntegerValue("X: ", 0, img->getWidth( ));
    y = PromptIntegerValue("X: ", 0, img->getWidth( ));
    value = PromptIntegerValue("X: ", 0, 255);

    img->Pixel( x, y ) = value;

}

void InteractiveImageInterface::GetImageFromUser( ) {
    Selector s;
    s.Add( 1, "NEW", [&]{ CreateNewImage( ); } );
    s.Add( 4, "Existing", [&]{ GetExistingImage( ); } );
    s.promptCustom( "Do you want to create new Image or open an existing one?" );

}

void InteractiveImageInterface::GetExistingImage( ) {
    while( true ) {
        std::string location = promptImageLocation( );
        try {
            img =  LoadImage( location );
            return;
        }
        catch( BaseException & e ) {
            out << e;
        }
    }
}

void InteractiveImageInterface::CreateNewImage( ) {
    int width = PromptIntegerValue( "Image Width", 0 );
    int height = PromptIntegerValue( "Image Height", 0 );
    img = std::make_shared<Image>( width, height );
}

std::string InteractiveImageInterface::promptImageLocation( ) {
    std::string location;
    out << "Location: " << std::endl;
    std::cin >> location;
    return location;
}

int InteractiveImageInterface::PromptIntegerValue( const std::string & name, int min, int max ) {
    out << name << ": ";
    int value;
    while( !promptInteger( value ) || value < min || value > max )
        std::cout << "Invalid value." << std::endl;
    return value;
}
