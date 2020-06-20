//
// Created by vernead2 on 06.06.20.
//

#pragma once

#include "Image/Image.h"

namespace interactive {

    std::string promptLocation( );

    int PromptIntegerValue( const std::string & name, int min = INT_MIN, int max = INT_MAX );

    ImagePtr CreateNewImage( );

    ImagePtr GetExistingImage( );

    ImagePtr GetImageFromUser( );

    void SetPixelPrompt( const ImagePtr & img );

    void EditImage( ImagePtr img );

    void PluginImage( ImagePtr img );

    void FilteringImage( ImagePtr img );

    void SaveImagePrompt( ImagePtr & img );

}