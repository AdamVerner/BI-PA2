//
// Created by vernead2 on 20.06.20.
//

#include <getopt.h>
#include <algorithm>

#include "../Exceptions.h"
#include "../Constants.h"
#include "../Plugins/Plugin_Resize.h"
#include "../Plugins/Plugin_Rotate.h"
#include "../Filter/Filter_Edge.h"
#include "../Filter/Filter_Grayscale.h"
#include "../Filter/Filter_HighPass.h"
#include "../Filter/Filter_Inverse.h"
#include "../Filter/Filter_LowPass.h"
#include "../Filter/Filter_Sharpen.h"
#include "../Image/Image_JPG.h"
#include "../Image/Image_PNG.h"
#include "../Image/LoadImage.h"
#include "CMDInterface.h"
#include "InteractiveImageInterface.h"
#include "InteractiveSequenceInterface.h"

int CMDInterface::ParseArguments( int argc, char ** argv ) {

    if(argc == 1){
        interactive = true;
        return 0;
    }


    int option_index = 0;
    static struct option long_options[] = {
            {"interactive", no_argument, nullptr,  'I' },
            {"filter", required_argument, nullptr,  'f' },
            {"rotate", required_argument, nullptr,  'r' },
            {"resize", required_argument, nullptr,  's' },
            {"ascii", required_argument, nullptr,  'a' },
            {"info", no_argument, nullptr,  'i' },
            {"help", no_argument, nullptr,  'h' },
    };

    try {
        while( !print_image_info || !interactive || !print_help ) {
            int c = getopt_long( argc, argv, "If:r:s:ih", long_options, &option_index );
            if( c == -1 )
                break;

            switch( c ) {
                case 'I':
                    interactive = true;
                    return 0;
                case 'f':
                    parseFilter( optarg );
                    break;
                case 'r':
                    parseRotation( optarg );
                    break;
                case 'a':
                    use_nonDefaultLut = true;
                    nonDefaultLut = LoadLut(optarg);
                    break;
                case 's':
                    parseResize( optarg );
                    break;
                case 'i':
                    print_image_info = true;
                    break;
                case 'h':
                    print_help = true;
                    return 0;
                default:
                    print_help = true;
            }
        }
    }
    catch( const BaseException & e ){
        out << e;
        return 1;

    }
    catch (std::exception & e){
        out << "Invalid parameter." << std::endl;
        return 1;
    }


    if((argc - optind != 2 && !print_image_info) || (print_image_info && argc - optind != 1) ){
        out << "Invalid number of arguments" << std::endl;
        return 1;
    }

    filenameIn = argv[optind++];
    filenameOut = argv[optind++];

    return 0;

}

int CMDInterface::run( ) {

    if(print_help) {
        printHelp( );
        return 0;
    }

    if(interactive) {

        out << "Welcome to '" << program_invocation_short_name << "'\n";
        out << "This is free software: you are free to change and redistribute it.\n";
        out << "There is NO WARRANTY, to the extent permitted by law.\n\n\n";

        out << "You've choose an interactive mode, you will be assisted in Editing images or creating sequences of images\n" << std::endl;

        Selector s;
        s.Add(1, "Edit Image", [&]{ InteractiveImageInterface().run(); });
        s.Add(3, "Create Image sequence", []{ InteractiveSequenceInterface().run(); });
        s.Add(10, "Exit", []{});
        s.prompt();
        return 0;
    }

    try {
        img = LoadImage( filenameIn );

        if(use_nonDefaultLut)
            img->mLUT = nonDefaultLut;

        if( print_image_info ) {
            printImageInfo( );
            return 0;
        }

        // apply filters and plugins parsed from argv
        for( const auto & f: filters )
            img->applyFilter( *f );

        for( const auto & p: plugins )
            img->applyPlugin( *p );

        if( filenameOut == "-" ) {
            out << *img;
            return 0;
        }

        switch(ImageTypeFromFilename(filenameOut)){
            case (JPG): std::make_shared<Image_JPG>( *img )->saveAs(filenameOut); break;
            case (PNG): std::make_shared<Image_PNG>( *img )->saveAs(filenameOut); break;
            case (ASCII): std::make_shared<Image_ASCII>( *img )->saveAs(filenameOut); break;
            default:
            throw BaseException("Can't deduce ImageType from filename");
        }

        out << "Image successfully saved" << std::endl;

    }
    catch( const BaseException & e ){
        out << e;
        return 5;
    }
    catch (std::exception & e){
        out << "Internal error: " << e.what() << std::endl;
        return 6;
    }

    return 0;
}

void CMDInterface::printImageInfo( ) {
    out << "Width: " << img->getWidth() << std::endl;
    out << "Height: " << img->getHeight() << std::endl;
    out << "Depth: 8bit" << std::endl;
    out << "Colorspace: RGBA" << std::endl;

    out << "Histogram:" << std::endl;
    for(const auto & a: img->getHistogram(10)) {
        auto starts = (size_t)std::log2(a + 1);
        out << "> " << std::string(starts, '-') << std::endl;
    }
}

void CMDInterface::parseResize( std::string specification ) {

    size_t x = std::stoi(specification.substr(0, specification.find(FILTER_DELIM)));
    specification.erase(0, specification.find(FILTER_DELIM) + 1);
    size_t y = std::stoi(specification);

    plugins.push_back(std::make_unique<Plugin_Resize>(x, y));

}

/**Parse Image rotation string.
 * @throws exception when unable to parse.
 * */
void CMDInterface::parseRotation( std::string specification ) {

    double deg = std::stof(specification.substr(0, specification.find(FILTER_DELIM)));
    specification.erase(0, specification.find(FILTER_DELIM) + 1);

    int x = std::stoi(specification.substr(0, specification.find(FILTER_DELIM)));
    specification.erase(0, specification.find(FILTER_DELIM) + 1);
    int y = std::stoi(specification);

    plugins.push_back(std::make_unique<Plugin_Rotate>(deg, x, y));

}

void CMDInterface::parseFilter( std::string specification ) {

    std::transform(specification.begin(), specification.end(), specification.begin(), [](unsigned char c){ return std::tolower(c); });

    if(specification == "edge") filters.push_back(std::make_unique<Filter_Edge>());
    else if(specification == "grayscale") filters.push_back(std::make_unique<Filter_Grayscale>());
    else if(specification == "highpass") filters.push_back(std::make_unique<Filter_HighPass>());
    else if(specification == "inverse") filters.push_back(std::make_unique<Filter_Inverse>());
    else if(specification == "lowpass") filters.push_back(std::make_unique<Filter_LowPass>());
    else if(specification == "sharpen") filters.push_back(std::make_unique<Filter_Sharpen>());
    else throw InvalidParam("Invalid Filter name " + specification);
}

void CMDInterface::printHelp( ) {
    out << "Usage: " << program_invocation_short_name<< " [OPTIONS] INPUT OUTPUT\n";
    out << "Example: -filter=grayscale -scale=150:100 -rotate=75:50:90 examples/kitty.jpg tmp/newImage.png\n";
    out << "\n";
    out << "OPTIONS:\n";
    out << "  -I, --Interactive      Launch interactive mode. All other switches are ignored\n";
    out << "  -f, --filter=NAME     Specify filter for image. see \"Format\" chapter for more\n";
    out << "  -r, --rotate=DEG:x:y  Rotate Image by specified angle in degrees around origin X:Y\n";
    out << "  -s, --resize=x:y      Resize the image to specified size\n";
    out << "  -a, --ascii=FILE      Load ascii Lookup table from specified file\n";
    out << "  -i, --info            Prints all known info about image\n";
    out << "  -h, --help            Prints this help and exit\n";
    out << "\n";
    out << "\n";
    out << "Filters do not have any parameters, they are specified by their name\n";
    out << "Some of the available filters are: \n";
    out << "  - inverse\n";
    out << "  - sharpen\n";
    out << "  - grayscale\n";
    out << "  - lowpass\n";
    out << "  - highpass\n";
    out << "\n";
    out << "When OUTPUT is '-', image is printed to stdout.\n";
    out << "\n";
    out << "Report bugs to: bugs@averner.cz\n";
    out << "averner2 home page: <https://github.com/AdamVerner/CVUT-PA2/tree/master/semwork/vernead2/>" << std::endl;
}

ImageType CMDInterface::ImageTypeFromFilename( const std::string & filename ) {
    if (ends_with(filename, ".ascii"))
        return ASCII;
    else if (ends_with(filename, ".png"))
        return PNG;
    else if (ends_with(filename, ".jpg") || ends_with(filename, ".jpeg"))
        return JPG;
    throw BaseException("Invalid Image name");
}

bool CMDInterface::ends_with( std::string const & value, std::string const & ending ) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), [](char c1, char c2) -> bool{ return std::toupper(c1) == std::toupper(c2);});
}
