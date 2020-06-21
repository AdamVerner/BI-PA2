//
// Created by vernead2 on 20.06.20.
//

#pragma once
//
// Created by vernead2 on 20.06.20.
//

#pragma once

#include <memory>

#include "../Filter/Filter.h"
#include "../Plugins/Plugin.h"
#include "../Image/Image.h"
#include "../Exceptions.h"
#include "../Image/Image_JPG.h"
#include "../Image/Image_PNG.h"
#include "../Image/Image_ASCII.h"
#include "Selector.h"

/**
 * Interactive interface. Prompt the user for every step that's needed.
 *
 * */
class InteractiveImageInterface{
public:

    InteractiveImageInterface(): out( std::cout){ };
    explicit InteractiveImageInterface(ImagePtr & img): img(img), out( std::cout){ };

    /** Run the interface*/
    int run();

    ImagePtr img /**< pointer on the currently edited image*/;
protected:
    std::ostream & out; /**<stream to write output to */

private:

    /** Prompts the user about required image type */
    void PromptImageSaveAs( );
    /** Prompts for selection of a filter and applies it if applicable */
    void FilteringImage();
    /** Prompt selection of a plugin and directly apply it */
    void PluginImage( );
    /** Display options about image editing (plugin, save, filters....) */
    void EditImage( );
    /** Prompts user to select a pixel and write new value to it */
    void SetPixelPrompt( );
    /** Prompt user to select image for editing */
    void GetImageFromUser( );
    /** Prompt the user to input existing image location, which is then loaded into mem. */
    void GetExistingImage( );
    /** Prompt user about new image size and background  */
    void CreateNewImage( );
    /** Prompt the user for Image location. */
    std::string promptImageLocation( );

    /** Prompt user for integer and range verify it. */
    int PromptIntegerValue( const std::string & name, int min = INT_MIN, int max = INT_MAX);

    void LoadLookupTable( );
};