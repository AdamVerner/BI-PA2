#include "progtest.cpp"
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;

class my_bad_cast: public std::bad_cast {
public:
    my_bad_cast(char const* s, char const* d): _source(s), _destination(d) {
        try {
            std::ostringstream oss;
            oss << "Could not cast '" << _source
                << "' into '" << _destination << "'";
            _what = oss.str();
        } catch (...) {
            _what.clear();
        }
    }

    char const* source() const { return _source; }
    char const* destination() const { return _destination; }

    virtual char const* what() const noexcept {
        return not _what.empty() ? _what.c_str() : std::bad_cast::what();
    }

private:
    char const* _source;
    char const* _destination;
    std::string _what;
    // you can even add a stack trace
};

template <typename D, typename S>
D my_dynamic_cast(S&& s) {
    try {
        return dynamic_cast<D>(std::forward<S>(s));
    } catch(std::bad_cast const&) {
        throw my_bad_cast(typeid(S).name(), typeid(D).name());
    }
}

int Vmain ( void );

int main(){

    CTable table (1, 1);
    table.SetCell(0, 0, CText("SomeText", CText::ALIGN_LEFT));
    table.SetCell(0, 0, CText("TestText", CText::ALIGN_LEFT));

    CTable table2(1, 1);
    table2.SetCell(0, 0, CText("Intitial Text", CText::ALIGN_LEFT));

    table2 = table;

    table.SetCell(0, 0, CText("tabl1", CText::ALIGN_LEFT));
    table2.SetCell(0, 0, CText("tbl2Text", CText::ALIGN_LEFT));

    cout << table;
    cout << table2;



    Vmain();

}


int Vmain ( void )
{
    ostringstream oss;
    CTable t0 ( 3, 2 );
    t0 . SetCell ( 0, 0, CText ( "Hello,\n"
                                 "Hello Kitty", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 1, 0, CText ( "Lorem ipsum dolor sit amet", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 2, 0, CText ( "Bye,\n"
                                 "Hello Kitty", CText::ALIGN_RIGHT ) );
    t0.SetCell ( 1, 1, CImage ()
            .AddRow ( "###                   " )
            .AddRow ( "#  #                  " )
            .AddRow ( "#  # # ##   ###    ###" )
            .AddRow ( "###  ##    #   #  #  #" )
            .AddRow ( "#    #     #   #  #  #" )
            .AddRow ( "#    #     #   #  #  #" )
            .AddRow ( "#    #      ###    ###" )
            .AddRow ( "                     #" )
            .AddRow ( "                   ## " )
            .AddRow ( "                      " )
            .AddRow ( " #    ###   ###   #   " )
            .AddRow ( "###  #   # #     ###  " )
            .AddRow ( " #   #####  ###   #   " )
            .AddRow ( " #   #         #  #   " )
            .AddRow ( "  ##  ###   ###    ## " ) );
    t0 . SetCell ( 2, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
             "+--------------------------+----------------------+\n"
             "|Hello,                    |                      |\n"
             "|Hello Kitty               |                      |\n"
             "+--------------------------+----------------------+\n"
             "|Lorem ipsum dolor sit amet|###                   |\n"
             "|                          |#  #                  |\n"
             "|                          |#  # # ##   ###    ###|\n"
             "|                          |###  ##    #   #  #  #|\n"
             "|                          |#    #     #   #  #  #|\n"
             "|                          |#    #     #   #  #  #|\n"
             "|                          |#    #      ###    ###|\n"
             "|                          |                     #|\n"
             "|                          |                   ## |\n"
             "|                          |                      |\n"
             "|                          | #    ###   ###   #   |\n"
             "|                          |###  #   # #     ###  |\n"
             "|                          | #   #####  ###   #   |\n"
             "|                          | #   #         #  #   |\n"
             "|                          |  ##  ###   ###    ## |\n"
             "+--------------------------+----------------------+\n"
             "|                      Bye,|                      |\n"
             "|               Hello Kitty|                      |\n"
             "+--------------------------+----------------------+\n" );
    t0 . SetCell ( 0, 1, t0 . GetCell ( 1, 1 ) );
    t0 . SetCell ( 2, 1, CImage ()
            . AddRow ( "*****   *      *  *      ******* ******  *" )
            . AddRow ( "*    *  *      *  *      *            *  *" )
            . AddRow ( "*    *  *      *  *      *           *   *" )
            . AddRow ( "*    *  *      *  *      *****      *    *" )
            . AddRow ( "****    *      *  *      *         *     *" )
            . AddRow ( "*  *    *      *  *      *        *       " )
            . AddRow ( "*   *   *      *  *      *       *       *" )
            . AddRow ( "*    *    *****   ****** ******* ******  *" ) );
    dynamic_cast<CText &> ( t0 . GetCell ( 1, 0 ) ) . SetText ( "Lorem ipsum dolor sit amet,\n"
                                                                "consectetur adipiscing\n"
                                                                "elit. Curabitur scelerisque\n"
                                                                "lorem vitae lectus cursus,\n"
                                                                "vitae porta ante placerat. Class aptent taciti\n"
                                                                "sociosqu ad litora\n"
                                                                "torquent per\n"
                                                                "conubia nostra,\n"
                                                                "per inceptos himenaeos.\n"
                                                                "\n"
                                                                "Donec tincidunt augue\n"
                                                                "sit amet metus\n"
                                                                "pretium volutpat.\n"
                                                                "Donec faucibus,\n"
                                                                "ante sit amet\n"
                                                                "luctus posuere,\n"
                                                                "mauris tellus" );
    oss . str ("");
    oss . clear ();
    oss << t0;
    // cout << oss.str() << flush;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    CTable t1 ( t0 );
    t1 . SetCell ( 1, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
             "+-----------+------------------------------------------+\n"
             "|Hello,     |          ###                             |\n"
             "|Hello Kitty|          #  #                            |\n"
             "|           |          #  # # ##   ###    ###          |\n"
             "|           |          ###  ##    #   #  #  #          |\n"
             "|           |          #    #     #   #  #  #          |\n"
             "|           |          #    #     #   #  #  #          |\n"
             "|           |          #    #      ###    ###          |\n"
             "|           |                               #          |\n"
             "|           |                             ##           |\n"
             "|           |                                          |\n"
             "|           |           #    ###   ###   #             |\n"
             "|           |          ###  #   # #     ###            |\n"
             "|           |           #   #####  ###   #             |\n"
             "|           |           #   #         #  #             |\n"
             "|           |            ##  ###   ###    ##           |\n"
             "+-----------+------------------------------------------+\n"
             "+-----------+------------------------------------------+\n"
             "|       Bye,|*****   *      *  *      ******* ******  *|\n"
             "|Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|           |*    *  *      *  *      *           *   *|\n"
             "|           |*    *  *      *  *      *****      *    *|\n"
             "|           |****    *      *  *      *         *     *|\n"
             "|           |*  *    *      *  *      *        *       |\n"
             "|           |*   *   *      *  *      *       *       *|\n"
             "|           |*    *    *****   ****** ******* ******  *|\n"
             "+-----------+------------------------------------------+\n" );
    t1 = t0;
    t1 . SetCell ( 0, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CImage ()
            . AddRow ( "  ********                    " )
            . AddRow ( " **********                   " )
            . AddRow ( "**        **                  " )
            . AddRow ( "**             **        **   " )
            . AddRow ( "**             **        **   " )
            . AddRow ( "***         ********  ********" )
            . AddRow ( "****        ********  ********" )
            . AddRow ( "****           **        **   " )
            . AddRow ( "****           **        **   " )
            . AddRow ( "****      **                  " )
            . AddRow ( " **********                   " )
            . AddRow ( "  ********                    " ) );
    oss . str ("");
    oss . clear ();
    oss << t0;
    cout << t0 << flush;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|Hello,                                        |          ###                             |\n"
             "|Hello Kitty                                   |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |          ###                             |\n"
             "|elit. Curabitur scelerisque                   |          #  #                            |\n"
             "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
             "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
             "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
             "|torquent per                                  |          #    #     #   #  #  #          |\n"
             "|conubia nostra,                               |          #    #      ###    ###          |\n"
             "|per inceptos himenaeos.                       |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|Donec tincidunt augue                         |                                          |\n"
             "|sit amet metus                                |           #    ###   ###   #             |\n"
             "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
             "|Donec faucibus,                               |           #   #####  ###   #             |\n"
             "|ante sit amet                                 |           #   #         #  #             |\n"
             "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                              |          ###                             |\n"
             "|                                              |          #  #                            |\n"
             "|                                              |          #  # # ##   ###    ###          |\n"
             "|                                              |          ###  ##    #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #     #   #  #  #          |\n"
             "|                                              |          #    #      ###    ###          |\n"
             "|                                              |                               #          |\n"
             "|                                              |                             ##           |\n"
             "|                                              |                                          |\n"
             "|                                              |           #    ###   ###   #             |\n"
             "|                                              |          ###  #   # #     ###            |\n"
             "|                                              |           #   #####  ###   #             |\n"
             "|                                              |           #   #         #  #             |\n"
             "|                                              |            ##  ###   ###    ##           |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|Lorem ipsum dolor sit amet,                   |                                          |\n"
             "|consectetur adipiscing                        |                                          |\n"
             "|elit. Curabitur scelerisque                   |        ********                          |\n"
             "|lorem vitae lectus cursus,                    |       **********                         |\n"
             "|vitae porta ante placerat. Class aptent taciti|      **        **                        |\n"
             "|sociosqu ad litora                            |      **             **        **         |\n"
             "|torquent per                                  |      **             **        **         |\n"
             "|conubia nostra,                               |      ***         ********  ********      |\n"
             "|per inceptos himenaeos.                       |      ****        ********  ********      |\n"
             "|                                              |      ****           **        **         |\n"
             "|Donec tincidunt augue                         |      ****           **        **         |\n"
             "|sit amet metus                                |      ****      **                        |\n"
             "|pretium volutpat.                             |       **********                         |\n"
             "|Donec faucibus,                               |        ********                          |\n"
             "|ante sit amet                                 |                                          |\n"
             "|luctus posuere,                               |                                          |\n"
             "|mauris tellus                                 |                                          |\n"
             "+----------------------------------------------+------------------------------------------+\n"
             "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
             "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
             "|                                              |*    *  *      *  *      *           *   *|\n"
             "|                                              |*    *  *      *  *      *****      *    *|\n"
             "|                                              |****    *      *  *      *         *     *|\n"
             "|                                              |*  *    *      *  *      *        *       |\n"
             "|                                              |*   *   *      *  *      *       *       *|\n"
             "|                                              |*    *    *****   ****** ******* ******  *|\n"
             "+----------------------------------------------+------------------------------------------+\n" );

    return 0;
}
