//
// Created by home-6 on 21.06.20.
//

#pragma once

#include <list>
#include <queue>

#include "InteractiveImageInterface.h"

/** Prompt the user about image sequence creation and editing */
class InteractiveSequenceInterface{
public:
    InteractiveSequenceInterface(): out(std::cout){};
    int run();

    void InsertFrame();
    void MoveFrame();
    void RemoveFrame();
    void EditFrame();
    /** Play the whole sequence that's stored in memory */
    void PlaySequence();

protected:
    std::ostream & out; /**<stream to write output to */
private:

    std::vector<ImagePtr> sequence;


};