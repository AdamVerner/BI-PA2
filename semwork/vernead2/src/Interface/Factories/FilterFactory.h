//
// Created by vernead2 on 19.06.20.
//

#pragma once

#include <vector>
#include <string>
#include <map>
#include <Filter/Filter.h>
#include <Filter/Filter_Inverse.h>
#include <Filter/Filter_Sharpen.h>
#include <Filter/Filter_LowPass.h>
#include <Filter/Filter_Grayscale.h>
#include <Filter/Filter_HighPass.h>
#include <Filter/Filter_Edge.h>
#include <algorithm>

class FilterFactory{
public:

    FilterFactory();

    /** Get Available filters
     * @returns vector of strings containg names of filters
     * */
    std::vector<std::string> getOptionStrings();

    /** Get filter from index.
     * @throws range_error
     * */
    inline std::shared_ptr<Filter> GetFilter(size_t idx);

protected:
private:

    std::vector<std::pair<std::string, std::shared_ptr<Filter>>> mFilters;

};