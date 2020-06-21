//
// Created by vernead2 on 19.06.20.
//

#pragma once

#include <map>
#include <functional>
#include <climits>

/**
 * Utility to prompt user for multiple selection.
 *
 * Input is sanitized. Upon invalid selection the user is re-prompted until viable option is selected.
 * */
class Selector{
public:

    Selector(std::ostream & out): out(out) { }
    Selector(): Selector(std::cout) {}

    /** Add an option prompt.
     * @param id id the user will be able to select
     * @param name description visible to the user
     * @param callback function called upon option selection
     * */
    void Add(int id, const std::string & name, const std::function<void(void)> & callback );

    /** Prompt the user with previously added options.
     * The selected option is executed. */
    void prompt(bool intro = true);
    void promptCustom( const std::string & prompt);

private:
    std::map<int, std::pair<std::string, const std::function<void(void)>>> options;  /**< Option store */

    /** Print available options to stdout */
    void printPrompt(bool intro);

    std::ostream & out;

};


/**
 * Try to read an integer from CIN, if read fails, delete everything until newline.
 * @param out[out] reference to output integer.
 * @returns false on failure
 * */
bool promptInteger( int & out );


/** Prompt user for integer and range verify it. */
int PromptIntegerValue( int min = INT_MIN, int max = INT_MAX);
