//
// Created by vernead2 on 30.04.20.
//

#include <iostream>
#include <cstdlib>    /* for exit */
#include <getopt.h>  /* for getopt_long*/


#include "cmd.h"

void help(const std::string & prgName){
    std::cout << "Usage: " << prgName<< " [OPTIONS] ... IMAGES ... OUTPUTS" << std::endl;

    std::cout << "Example: img1.png img2.png -fsharpen:1 -frotate:90 -o new_img1.jpg new_img2.jpg" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  -a, --ascii=FILE       ASCII File encoding specification (.ascii image can be used)" << std::endl;
    std::cout << "  -f, --filter=FILTER    Specify filter for image. see \"Format\" chapter for more" << std::endl;
    std::cout << "  -i, --image=IMAGE      Specify Image source file" << std::endl;
    std::cout << "  -I, --Interactive      Launch interactive mode. All other switches are ignored" << std::endl;
    std::cout << "  -n, --inplace          Don't save to new file, modify the old one" << std::endl;
    std::cout << "  -o, --output           Placeholder option" << std::endl;
    std::cout << "  -p, --print            Ignore outputs and print to STDOUT" << std::endl;
    std::cout << "  -s, --scale=SCALE      Scale images to certain size." << std::endl;
    std::cout << "  -v, --verbose          Increase verbosity level" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Filter specification" << std::endl;
    std::cout << "  Filters are specified by single string split by colon." << std::endl;
    std::cout << "    FILTER_NAME[:PARAM1[:PARAM2[:PARAM3... ]]]" << std::endl;
    std::cout << "  More examples can be found in documentation. here are somme examples." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  -f lowpass:average:5:2" << std::endl;
    std::cout << "  -f higpass:average:3:1" << std::endl;
    std::cout << "  -f sharpen:1" << std::endl;
    std::cout << "  -f rotate:90" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "When OTPUT is '-', output is printed to stdout. In combination with --ansi" << std::endl;
    std::cout << "output is displayed in terminal using ANSI control sequences." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Report bugs to: bugs@averner.cz" << std::endl;
    std::cout << "averner2 home page: <https://github.com/AdamVerner/CVUT-PA2/tree/master/semwork/vernead2/>" << std::endl;
}

int main(int argc, char **argv) {

    help(argv[0]);
    exit(0);

    int c;
    int digit_optind = 0;

    while (true) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
                {"add",     required_argument, 0,  0 },
                {"append",  no_argument,       0,  0 },
                {"delete",  required_argument, 0,  0 },
                {"verbose", no_argument,       0,  0 },
                {"create",  required_argument, 0, 'c'},
                {"file",    required_argument, 0,  0 }
                // ,{0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "abc:d:012",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 0:
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;

            case '0':
            case '1':
            case '2':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf("digits occur in two different argv-elements.\n");
                digit_optind = this_option_optind;
                printf("option %c\n", c);
                break;

            case 'a':
                printf("option a\n");
                break;

            case 'b':
                printf("option b\n");
                break;

            case 'c':
                printf("option c with value '%s'\n", optarg);
                break;

            case 'd':
                printf("option d with value '%s'\n", optarg);
                break;

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    exit(EXIT_SUCCESS); }

