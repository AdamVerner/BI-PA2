//
// Created by home-6 on 21.06.20.
//

#include <thread>

#include "InteractiveSequenceInterface.h"

int InteractiveSequenceInterface::run( ) {

    bool stop = false;
    while(!stop){


        if(sequence.empty())
            out << "There are no frames in your sequence.\nStart by inserting new frame" << std::endl;
        else if(sequence.size() == 1)
            out << "There is 1 frame in your sequence" << std::endl;
        else
            out << "There are currently " << sequence.size() << " frames in your sequence" << std::endl;


        Selector s;
        s.Add(1, "Insert frame", [&]{ InsertFrame(); });

        if(sequence.size() > 1)
            s.Add(2, "Move frame", [&]{ MoveFrame(); });

        if(!sequence.empty()) {
            s.Add( 3, "Remove frame", [&]( ) { RemoveFrame(); } );
            s.Add( 4, "Edit frame", [&]{ EditFrame(); } );
            s.Add( 5, "Play sequence", [&]{ PlaySequence(); } );
        }
        s.Add(10, "Return", [&](){stop = true; });

        try{
            s.prompt();
        }
        catch( const BaseException & e ) {
            out << e;
        }
    }

    return 0;
}

void InteractiveSequenceInterface::InsertFrame( ) {

    InteractiveImageInterface ImageIface;
    if(!ImageIface.run() && ImageIface.img.get()){

        out << "Index to insert at (0-"<< sequence.size() << "): " << std::endl;
        int idx = PromptIntegerValue(0, (int)sequence.size());
        sequence.insert(sequence.begin() + idx, ImageIface.img);

    }
    else
        std::cout << "Failure" << std::endl;

}

void InteractiveSequenceInterface::MoveFrame( ) {

    out << "Select index of frame to pop <0-"<< sequence.size()-1 << ">: " << std::endl;
    int idx = PromptIntegerValue(0, (int)sequence.size()-1);

    ImagePtr img = sequence[idx];
    sequence.erase(sequence.begin() + idx);

    idx = PromptIntegerValue(0, (int)sequence.size());
    sequence.insert(sequence.begin() + idx, img);

}

void InteractiveSequenceInterface::RemoveFrame( ) {

    out << "Select index of frame to delete <0-"<< sequence.size()-1 << ">: " << std::endl;
    int idx = PromptIntegerValue(0, (int)sequence.size()-1);

    sequence.erase(sequence.begin() + idx);
}

void InteractiveSequenceInterface::EditFrame( ) {
    out << "Select index of frame to Edit <(>0-"<< sequence.size()-1 << ">: " << std::endl;
    int idx = PromptIntegerValue(0, (int)sequence.size()-1);
    InteractiveImageInterface ImageIface(sequence[idx]);
    ImageIface.run();

}

void InteractiveSequenceInterface::PlaySequence( ) {

    out << "Select time between each frame [ms]" << std::endl;
    int delay = PromptIntegerValue(0);

    for(const auto & a:sequence){
        system("clear");
        out<< *a;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }



}
