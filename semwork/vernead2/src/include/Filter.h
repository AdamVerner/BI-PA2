/**
 * Most of filtering was sourced from
 *   https://northstar-www.dartmouth.edu/doc/idl/html_6.2/Filtering_an_Imagehvr.html
 *   https://northstar-www.dartmouth.edu/doc/idl/html_6.2/Sharpening_an_Image.html
 * */

#pragma once

#include "Image.h"
#include "dataTypes.h"



class CFilter{

    void processData(imgData_t * data){}

};


class CFilter_Inverse{


};


class CFilter_Rotate{


};

class CFilter_LowPass{ };
class CFilter_HighPass{ };
class CFilter_Sharpen{ };
