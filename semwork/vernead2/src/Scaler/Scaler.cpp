//
// Created by vernead2 on 06.06.20.
//

#include <iostream>
#include "Scaler.h"

/**
 * @param[in,out] data Data to be modified
 * @param[in,out] width Width of data. Returns the actual width the data was scaled to
 * @param[in,out] height Height of data. Returns the actual height the data was scaled to
 * */
void Scaler::processData( imgData_t & data, size_t & width, size_t & height ) const {

    if( height < getReqHeight( ) || width < getReqWidth( )) {
        scaleUp( data, width, height );
    } else {
        scaleDown( data, width, height );
    }
}

void Scaler::scaleDown( imgData_t & data, size_t & width, size_t & height ) const {
    while( height > getReqHeight( ) && width > getReqWidth( )) {

        for( size_t y = 0; y < height / 2; y++ ) {
            for( size_t x = 0; x < width / 2; x++ ) {
                // todo redo
                data[y * width + x] = 0;
                data[y * width + x] += data[y * width * 2 + x * 2];
                data[y * width + x] += data[y * width * 2 + x * 2 + 1];
                data[y * width + x] += data[(y + 1) * width * 2 + x * 2];
                data[y * width + x] += data[(y + 1) * width * 2 + x * 2 + 1];
            }
        }
        width = width / 2;
        height = height / 2;
    }

    // resize the array to discard old data
    data.resize( height );
    for( auto & row: data )
        row.resize( width );
}

void Scaler::scaleUp( imgData_t & data, size_t & width, size_t & height ) const {
    while( height < getReqHeight( ) && width < getReqWidth( )) {

        auto old_data = data; // deep copy

        /* resize the array to for the upscaled image*/
        data.resize( height * 2 );
        for( auto & row: data )
            row.resize( width * 2);

        // TODO wouldn't it be more efficient to create new and use the old one as source?

        /* mx and my represent upper left corner of the 2x2 scaling region */
        for( size_t y = 0; y < height; y++ ) {
            for( size_t x = 0; x < width; x++ ) {
                data[y * 2]    [x * 2]     = old_data[y][x];
                data[y * 2]    [x * 2 + 1] = old_data[y][x];
                data[y * 2 + 1][x * 2]     = old_data[y][x];
                data[y * 2 + 1][x * 2 + 1] = old_data[y][x];
            }
        }

        height *= 2;
        width *= 2;
    }
}
