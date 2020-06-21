//
// Created by vernead2 on 20.06.20.
//

#pragma once

#include <memory>

#include "../Filter/Filter.h"
#include "../Plugins/Plugin.h"
#include "../Image/Image.h"

/**
 * Terminal Interface. If requested hands off execution to InteractiveImageInterface
 *
 * Firstly call ParseArguments, then run(). If any of these functions return non-zero, exit with failure
 *
 * */
class CMDInterface{
public:

    /** Pre-parse the cmd arguments, but don't execute or print anything */
    CMDInterface(): out(std::cout){ };

    int ParseArguments( int argc, char ** argv );

    /** Executed instructions based on parsed arguments*/
    int run();

private:

    std::ostream & out;
    void printImageInfo();
    void parseResize( std::string specification);
    void parseRotation( std::string specification);
    void parseFilter( std::string specification);
    void printHelp();
    static bool ends_with( std::string const & value, std::string const & ending );
    ImageType ImageTypeFromFilename( const std::string & filename );

    bool print_image_info = false;
    bool interactive = false;
    bool print_help = false;
    bool use_nonDefaultLut = false;

    std::vector<std::unique_ptr<Filter>> filters;
    std::vector<std::unique_ptr<Plugin>> plugins;

    ImagePtr img;
    std::string filenameIn;
    std::string filenameOut;
    std::string nonDefaultLut;

};