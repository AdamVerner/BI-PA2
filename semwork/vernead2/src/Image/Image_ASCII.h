//
// Created by vernead2 on 14.06.20.
//
#include <fstream>
#include <string>
#include <vector>
#include <Exceptions.h>

#include "Image.h"

class Image_ASCII: public Image{
public:

    explicit Image_ASCII(const std::string & file): mFilename(file) { LoadFile(file); }
    explicit Image_ASCII(const Image & img): Image(img) { }

    void save() override;
    void saveAs(const std::string & filename) override {
        this->mFilename = filename;
        save();
    };

    std::shared_ptr<Image> copy() const override{ return std::make_shared<Image_ASCII>(*this); }


private:
    std::string mFilename;
    void LoadFile(const std::string & filename);

};