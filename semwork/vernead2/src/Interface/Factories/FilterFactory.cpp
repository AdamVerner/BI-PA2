//
// Created by home-6 on 19.06.20.
//

#include "FilterFactory.h"

FilterFactory::FilterFactory( ) {
    mFilters.emplace_back( "Edge", new Filter_Edge());
    mFilters.emplace_back( "GrayScale", new Filter_Grayscale());
    mFilters.emplace_back( "HighPass", new Filter_HighPass());
    mFilters.emplace_back( "Inverse", new Filter_Inverse());
    mFilters.emplace_back( "LowPass", new Filter_LowPass());
    mFilters.emplace_back( "Sharpen", new Filter_Sharpen());
}

std::vector<std::string> FilterFactory::getOptionStrings( ) {
    std::vector<std::string> out;
    for(auto & a: mFilters)
        out.push_back(a.first);
    return out;
}

std::shared_ptr<Filter> FilterFactory::GetFilter( size_t idx ) {
    return mFilters.at(idx).second;
}
