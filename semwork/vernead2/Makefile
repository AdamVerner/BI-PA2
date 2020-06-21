#Zde bude funkcni Makefile.
SHELL = /bin/bash
CXX = g++ -c
LD = g++
CXX_FLAGS = -Wall -pedantic -Wno-long-long -O2 -Werror -Wextra -std=c++11
LD_FLAGS = -ljpeg -lpng
NAME = vernead2

default_target: all


$(NAME): build/Plugin_Resize.o build/Plugin_Rotate.o build/CMDInterface.o build/main.o build/InteractiveSequenceInterface.o build/Selector.o build/InteractiveImageInterface.o build/FilterKernel.o build/Filter.o build/FileWrap.o build/LoadImage.o build/Image_PNG.o build/Image_ASCII.o build/Image_JPG.o build/Image.o
	$(LD) $^ $(LD_FLAGS) -o $@

# compile any cpp file
build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

# Weirdly the default rule isnt recursive...
build/%.o: src/Filter/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

build/%.o: src/Image/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

build/%.o: src/Interface/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

build/%.o: src/Plugins/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(NAME) src/*.o $(NAME).zip
	rm -rf doc/ zip_build/ build/


doc: Doxyfile $(wildcard src/*) zadani.txt
	doxygen Doxyfile


zip: clean
	mkdir -p zip_build/$(NAME)
	cp -r src examples tests zadani.txt Makefile prohlaseni.txt Doxyfile zip_build/$(NAME)/
	cp zadani.txt zip_build/$(NAME)/zadani.md
	cd zip_build; zip -r ../$(NAME) $(NAME)/

dependencies:
	find . -name '*.cpp' | xargs g++ -MM  | sed -r 's|^(.*\.o)|build/\1|'

lines:
	 find src/ -name '*.cpp' -o -name '*.h' | xargs wc -l


all: $(NAME) doc

compile: vernead2

run: $(NAME)
	./$(NAME)


# TODO
# tests: all

.PHONY: clean zip dependencies

#Dependency Definitions
build/Plugin_Resize.o: src/Plugins/Plugin_Resize.cpp \
 src/Plugins/Plugin_Resize.h \
 src/Plugins/../dataTypes.h \
 src/Plugins/Plugin.h \
 src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../Filter/Filter.h
build/Plugin_Rotate.o: src/Plugins/Plugin_Rotate.cpp \
 src/Plugins/Plugin_Rotate.h \
 src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../dataTypes.h \
 src/Plugins/../Image/../Filter/Filter.h \
 src/Plugins/../Image/../Plugins/Plugin.h
build/CMDInterface.o: src/Interface/CMDInterface.cpp \
 src/Interface/../Exceptions.h \
 src/Interface/../Constants.h \
 src/Interface/../Plugins/Plugin_Resize.h \
 src/Interface/../Plugins/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h \
 src/Interface/../Plugins/../Image/Image.h \
 src/Interface/../Plugins/../Image/../Filter/Filter.h \
 src/Interface/../Plugins/Plugin_Rotate.h \
 src/Interface/../Filter/Filter_Edge.h \
 src/Interface/../Filter/FilterKernel.h \
 src/Interface/../Filter/Filter_Grayscale.h \
 src/Interface/../Filter/Filter_HighPass.h \
 src/Interface/../Filter/Filter_Inverse.h \
 src/Interface/../Filter/Filter_LowPass.h \
 src/Interface/../Filter/Filter_Sharpen.h \
 src/Interface/../Image/Image_JPG.h \
 src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/LoadImage.h \
 src/Interface/CMDInterface.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Image/Image_ASCII.h \
 src/Interface/Selector.h \
 src/Interface/InteractiveSequenceInterface.h
build/main.o: src/Interface/main.cpp \
 src/Interface/CMDInterface.h \
 src/Interface/../Filter/Filter.h \
 src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h \
 src/Interface/../Image/Image.h
build/InteractiveSequenceInterface.o: \
 src/Interface/InteractiveSequenceInterface.cpp \
 src/Interface/InteractiveSequenceInterface.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Filter/Filter.h \
 src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h \
 src/Interface/../Image/Image.h \
 src/Interface/../Exceptions.h \
 src/Interface/../Image/Image_JPG.h \
 src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/Image_ASCII.h \
 src/Interface/Selector.h
build/Selector.o: src/Interface/Selector.cpp \
 src/Interface/Selector.h
build/InteractiveImageInterface.o: \
 src/Interface/InteractiveImageInterface.cpp \
 src/Interface/../Filter/Filter_Edge.h \
 src/Interface/../Filter/Filter.h \
 src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Filter/FilterKernel.h \
 src/Interface/../Filter/Filter_Grayscale.h \
 src/Interface/../Filter/Filter_LowPass.h \
 src/Interface/../Filter/Filter_HighPass.h \
 src/Interface/../Filter/Filter_Inverse.h \
 src/Interface/../Filter/Filter_Sharpen.h \
 src/Interface/../Plugins/Plugin_Rotate.h \
 src/Interface/../Plugins/../Image/Image.h \
 src/Interface/../Plugins/../Image/../Plugins/Plugin.h \
 src/Interface/../Plugins/Plugin_Resize.h \
 src/Interface/../Image/LoadImage.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Exceptions.h \
 src/Interface/../Image/Image_JPG.h \
 src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/Image_ASCII.h \
 src/Interface/Selector.h
build/FilterKernel.o: src/Filter/FilterKernel.cpp \
 src/Filter/FilterKernel.h \
 src/Filter/Filter.h \
 src/Filter/../dataTypes.h
build/Filter.o: src/Filter/Filter.cpp \
 src/Filter/Filter.h \
 src/Filter/../dataTypes.h \
 src/Filter/../Image/Image.h \
 src/Filter/../Image/../Plugins/Plugin.h
build/FileWrap.o: src/Image/FileWrap.cpp \
 src/Image/../Exceptions.h \
 src/Image/FileWrap.h
build/LoadImage.o: src/Image/LoadImage.cpp \
 src/Image/Image.h \
 src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h \
 src/Image/Image_PNG.h \
 src/Image/../Exceptions.h \
 src/Image/Image_JPG.h \
 src/Image/Image_ASCII.h
build/Image_PNG.o: src/Image/Image_PNG.cpp \
 src/Image/Image_PNG.h \
 src/Image/../Exceptions.h \
 src/Image/Image.h \
 src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h \
 src/Image/FileWrap.h
build/Image_ASCII.o: src/Image/Image_ASCII.cpp \
 src/Image/Image.h \
 src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h \
 src/Image/Image_ASCII.h \
 src/Image/../Exceptions.h
build/Image_JPG.o: src/Image/Image_JPG.cpp \
 src/Image/../Exceptions.h \
 src/Image/../Constants.h \
 src/Image/Image_JPG.h \
 src/Image/Image.h \
 src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h \
 src/Image/FileWrap.h
build/Image.o: src/Image/Image.cpp \
 src/Image/../Exceptions.h \
 src/Image/Image.h \
 src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h
build/testFilters.o: tests/testFilters.cpp tests/../src/Image/LoadImage.h \
 tests/../src/Image/Image.h tests/../src/Image/../Constants.h \
 tests/../src/Image/../dataTypes.h tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h \
 tests/../src/Filter/Filter_LowPass.h tests/../src/Filter/FilterKernel.h \
 tests/../src/Filter/Filter_HighPass.h \
 tests/../src/Filter/Filter_Sharpen.h
build/testScaler.o: tests/testScaler.cpp tests/../src/Image/LoadImage.h \
 tests/../src/Image/Image.h tests/../src/Image/../Constants.h \
 tests/../src/Image/../dataTypes.h tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h \
 tests/../src/Plugins/Plugin_Resize.h
build/testImageGetter.o: tests/testImageGetter.cpp tests/../src/dataTypes.h \
 tests/../src/Image/Image.h tests/../src/Image/../Constants.h \
 tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h tests/../src/Image/LoadImage.h
build/testPixels.o: tests/testPixels.cpp tests/../src/dataTypes.h
build/Plugin_Resize.o: src/Plugins/Plugin_Resize.cpp \
 src/Plugins/Plugin_Resize.h src/Plugins/../dataTypes.h \
 src/Plugins/Plugin.h src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../Constants.h \
 src/Plugins/../Image/../Filter/Filter.h
build/Plugin_Rotate.o: src/Plugins/Plugin_Rotate.cpp \
 src/Plugins/Plugin_Rotate.h src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../Constants.h src/Plugins/../Image/../dataTypes.h \
 src/Plugins/../Image/../Filter/Filter.h \
 src/Plugins/../Image/../Plugins/Plugin.h
build/CMDInterface.o: src/Interface/CMDInterface.cpp \
 src/Interface/../Exceptions.h src/Interface/../Constants.h \
 src/Interface/../Plugins/Plugin_Resize.h \
 src/Interface/../Plugins/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h \
 src/Interface/../Plugins/../Image/Image.h \
 src/Interface/../Plugins/../Image/../Filter/Filter.h \
 src/Interface/../Plugins/Plugin_Rotate.h \
 src/Interface/../Filter/Filter_Edge.h \
 src/Interface/../Filter/FilterKernel.h \
 src/Interface/../Filter/Filter_Grayscale.h \
 src/Interface/../Filter/Filter_HighPass.h \
 src/Interface/../Filter/Filter_Inverse.h \
 src/Interface/../Filter/Filter_LowPass.h \
 src/Interface/../Filter/Filter_Sharpen.h \
 src/Interface/../Image/Image_JPG.h src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/LoadImage.h src/Interface/CMDInterface.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Image/Image_ASCII.h src/Interface/Selector.h \
 src/Interface/InteractiveSequenceInterface.h
build/main.o: src/Interface/main.cpp src/Interface/CMDInterface.h \
 src/Interface/../Filter/Filter.h src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h src/Interface/../Image/Image.h \
 src/Interface/../Image/../Constants.h
build/InteractiveSequenceInterface.o: \
 src/Interface/InteractiveSequenceInterface.cpp \
 src/Interface/InteractiveSequenceInterface.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Filter/Filter.h src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h src/Interface/../Image/Image.h \
 src/Interface/../Image/../Constants.h src/Interface/../Exceptions.h \
 src/Interface/../Image/Image_JPG.h src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/Image_ASCII.h src/Interface/Selector.h
build/Selector.o: src/Interface/Selector.cpp src/Interface/Selector.h
build/InteractiveImageInterface.o: src/Interface/InteractiveImageInterface.cpp \
 src/Interface/../Filter/Filter_Edge.h src/Interface/../Filter/Filter.h \
 src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Filter/FilterKernel.h \
 src/Interface/../Filter/Filter_Grayscale.h \
 src/Interface/../Filter/Filter_LowPass.h \
 src/Interface/../Filter/Filter_HighPass.h \
 src/Interface/../Filter/Filter_Inverse.h \
 src/Interface/../Filter/Filter_Sharpen.h \
 src/Interface/../Plugins/Plugin_Rotate.h \
 src/Interface/../Plugins/../Image/Image.h \
 src/Interface/../Plugins/../Image/../Constants.h \
 src/Interface/../Plugins/../Image/../Plugins/Plugin.h \
 src/Interface/../Plugins/Plugin_Resize.h \
 src/Interface/../Image/LoadImage.h \
 src/Interface/InteractiveImageInterface.h src/Interface/../Exceptions.h \
 src/Interface/../Image/Image_JPG.h src/Interface/../Image/Image_PNG.h \
 src/Interface/../Image/Image_ASCII.h src/Interface/Selector.h
build/FilterKernel.o: src/Filter/FilterKernel.cpp src/Filter/FilterKernel.h \
 src/Filter/Filter.h src/Filter/../dataTypes.h
build/Filter.o: src/Filter/Filter.cpp src/Filter/Filter.h \
 src/Filter/../dataTypes.h src/Filter/../Image/Image.h \
 src/Filter/../Image/../Constants.h \
 src/Filter/../Image/../Plugins/Plugin.h
build/FileWrap.o: src/Image/FileWrap.cpp src/Image/../Exceptions.h \
 src/Image/FileWrap.h
build/LoadImage.o: src/Image/LoadImage.cpp src/Image/Image.h \
 src/Image/../Constants.h src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h src/Image/../Plugins/Plugin.h \
 src/Image/Image_PNG.h src/Image/../Exceptions.h src/Image/Image_JPG.h \
 src/Image/Image_ASCII.h
build/Image_PNG.o: src/Image/Image_PNG.cpp src/Image/Image_PNG.h \
 src/Image/../Exceptions.h src/Image/Image.h src/Image/../Constants.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h src/Image/FileWrap.h
build/Image_ASCII.o: src/Image/Image_ASCII.cpp src/Image/Image.h \
 src/Image/../Constants.h src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h src/Image/../Plugins/Plugin.h \
 src/Image/Image_ASCII.h src/Image/../Exceptions.h
build/Image_JPG.o: src/Image/Image_JPG.cpp src/Image/../Exceptions.h \
 src/Image/../Constants.h src/Image/Image_JPG.h src/Image/Image.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h src/Image/FileWrap.h
build/Image.o: src/Image/Image.cpp src/Image/../Exceptions.h src/Image/Image.h \
 src/Image/../Constants.h src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h src/Image/../Plugins/Plugin.h