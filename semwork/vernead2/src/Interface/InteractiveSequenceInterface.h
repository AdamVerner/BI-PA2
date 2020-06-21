//
// Created by home-6 on 21.06.20.
//

#pragma once

#include <list>
#include <queue>

#include "Sequence/Sequence.h"
#include "InteractiveImageInterface.h"

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