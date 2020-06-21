TARGET = vernead2

CXX = g++
MKDIR = mkdir -p

CXXFLAGS = -Wall -pedantic -Wextra -std=c++14

SOURCE_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)


.PHONY: all
all: compile doc
	@echo "Finished..."


.PHONY: compile
compile: $(TARGET)
	@echo "Compile..."


.PHONY: run
run: $(TARGET)
	./$(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@


doc: Doxyfile README.md $(HEADERS)
	doxygen Doxyfile

EXAMPLES = $(wildcard examples/*)
$(TARGET).zip: README.md zadani.txt prohlaseni.txt Makefile Doxyfile $(HEADERS) $(SOURCES) $(EXAMPLES)
	mkdir -p .archive/$(TARGET)/
	cp -r README.md zadani.txt prohlaseni.txt Makefile Doxyfile src/ examples/ .archive/$(TARGET)/
	cd .archive/; zip -r ../$(TARGET).zip $(TARGET)/
	rm -r .archive/

.PHONY: clean
clean:
	rm -rf $(TARGET) $(TARGET).zip doc/ .archive/ $(BUILD_DIR)/ 2>/dev/null


# Dependencies

build/testFilters.o: tests/testFilters.cpp tests/../src/Image/LoadImage.h \
 tests/../src/Image/Image.h tests/../src/Image/../dataTypes.h \
 tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h \
 tests/../src/Filter/Filter_LowPass.h tests/../src/Filter/FilterKernel.h \
 tests/../src/Filter/Filter_HighPass.h \
 tests/../src/Filter/Filter_Sharpen.h
build/testScaler.o: tests/testScaler.cpp tests/../src/Image/LoadImage.h \
 tests/../src/Image/Image.h tests/../src/Image/../dataTypes.h \
 tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h \
 tests/../src/Plugins/Plugin_Resize.h
build/testImageGetter.o: tests/testImageGetter.cpp tests/../src/dataTypes.h \
 tests/../src/Image/Image.h tests/../src/Image/../Filter/Filter.h \
 tests/../src/Image/../Plugins/Plugin.h tests/../src/Image/LoadImage.h
build/testPixels.o: tests/testPixels.cpp tests/../src/dataTypes.h
build/Plugin_Resize.o: src/Plugins/Plugin_Resize.cpp \
 src/Plugins/Plugin_Resize.h src/Plugins/../dataTypes.h \
 src/Plugins/Plugin.h src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../Filter/Filter.h
build/Plugin_Rotate.o: src/Plugins/Plugin_Rotate.cpp \
 src/Plugins/Plugin_Rotate.h src/Plugins/../Image/Image.h \
 src/Plugins/../Image/../dataTypes.h \
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
 src/Interface/../Plugins/Plugin.h src/Interface/../Image/Image.h
build/InteractiveSequenceInterface.o: \
 src/Interface/InteractiveSequenceInterface.cpp \
 src/Interface/InteractiveSequenceInterface.h \
 src/Interface/InteractiveImageInterface.h \
 src/Interface/../Filter/Filter.h src/Interface/../Filter/../dataTypes.h \
 src/Interface/../Plugins/Plugin.h src/Interface/../Image/Image.h \
 src/Interface/../Exceptions.h src/Interface/../Image/Image_JPG.h \
 src/Interface/../Image/Image_PNG.h src/Interface/../Image/Image_ASCII.h \
 src/Interface/Selector.h
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
 src/Filter/../Image/../Plugins/Plugin.h
build/FileWrap.o: src/Image/FileWrap.cpp src/Image/../Exceptions.h \
 src/Image/FileWrap.h
build/LoadImage.o: src/Image/LoadImage.cpp src/Image/Image.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h src/Image/Image_PNG.h \
 src/Image/../Exceptions.h src/Image/Image_JPG.h src/Image/Image_ASCII.h
build/Image_PNG.o: src/Image/Image_PNG.cpp src/Image/Image_PNG.h \
 src/Image/../Exceptions.h src/Image/Image.h src/Image/../dataTypes.h \
 src/Image/../Filter/Filter.h src/Image/../Plugins/Plugin.h \
 src/Image/FileWrap.h
build/Image_ASCII.o: src/Image/Image_ASCII.cpp src/Image/Image.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h src/Image/Image_ASCII.h \
 src/Image/../Exceptions.h
build/Image_JPG.o: src/Image/Image_JPG.cpp src/Image/../Exceptions.h \
 src/Image/../Constants.h src/Image/Image_JPG.h src/Image/Image.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h src/Image/FileWrap.h
build/Image.o: src/Image/Image.cpp src/Image/../Exceptions.h src/Image/Image.h \
 src/Image/../dataTypes.h src/Image/../Filter/Filter.h \
 src/Image/../Plugins/Plugin.h
