#Zde bude funkcni Makefile.
SHELL = /bin/bash
CXX = g++ -c
LD = g++  -ljpeg
CXX_FLAGS = -Wall -pedantic -Wno-long-long -O2 -Werror --coverage
# LD_FLAGS = -ljpg -lpng


all: vernead2


vernead2: src/cmd.o
	$(LD) $(LD_FLAGS) -o $@ $^


clean:
	rm -f vernead2 src/*.o
	rm -rf doc/*

doc:
	doxygen Doxyfile

# compile any file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<



# linked: src.cpp src.h dep.h

src/cmd.o:	src/cmd.cpp src/include/cmd.h

src/Image.o: src/Image.cpp src/include/Image.h src/include/Filter.h src/include/Filter.h



run:
ifeq (,$(wildcard ./vernead2))
	$(error Project has not been build, run 'make all')
else
	$(SHELL) vernead2
endif


.PHONY: all run clean doc



filter.o: filter.cpp filter.h

main.o: main.cpp tga.h filter.h jpeg.h

tga.o: tga.cpp tga.h

jpeg.o: jpeg.cpp jpeg.h
