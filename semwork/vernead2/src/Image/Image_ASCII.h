//
// Created by home-6 on 14.06.20.
//
#include <fstream>
#include <string>
#include <vector>
#include <Exceptions.h>

class Image_ASCII: public Image{
public:

    explicit Image_ASCII(const std::string & file) { LoadFile(file); }
    explicit Image_ASCII(const Image & img): Image(img) { }

    void save() override;
    void saveAs(const std::string &) override{ };

    std::shared_ptr<Image> copy() const{ return std::make_shared<Image_ASCII>(*this); }


private:
    void LoadFile(const std::string & filename);

};