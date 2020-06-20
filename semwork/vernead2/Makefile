#Zde bude funkcni Makefile.
SHELL = /bin/bash
CXX = g++ -c
LD = g++  -ljpeg
CXX_FLAGS = -Wall -pedantic -Wno-long-long -O2 -Werror --coverage -std=c++11
LD_FLAGS = -ljpg -lpng

default_target: all


# compile any cpp file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

src/cmd.o:	src/cmd.cpp src/include/cmd.h

src/Image.o: src/Image.cpp src/include/Image.h src/include/Filter.h src/include/Filter.h

all: vernead2 doc

vernead2: src
	$(LD) $(LD_FLAGS) -o $@ $^

compile: vernead2

run: vernead2
	$ ./vernead2

clean:
	rm -f vernead2 src/*.o vernead2.zip
	rm -rf doc/ zip_build/

doc:
	doxygen Doxyfile

zip: clean
	mkdir -p zip_build/vernead2
	cp -r src examples tests zadani.txt Makefile prohlaseni.txt Doxyfile zip_build/vernead2/
	cd zip_build; zip -r ../vernead2 vernead2/


lines:
	 wc src/*.cpp src/include/*.h -l


.PHONY: all run clean doc compile zip



filter.o: filter.cpp filter.h

main.o: main.cpp tga.h filter.h jpeg.h

tga.o: tga.cpp tga.h

jpeg.o: jpeg.cpp jpeg.h
