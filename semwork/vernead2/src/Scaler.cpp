
#include <Image.h>
#include "Scaler.h"

/**
 * @param[in,out] data Data to be modified
 * @param[in,out] width Width of data. Returns the actual width the data was scaled to
 * @param[in,out] height Height of data. Returns the actual height the data was scaled to
 * */
void CScaler::processData( imgData_t & data, size_t & width, size_t & height ) const {

    if( height < getReqHeight( ) || width < getReqWidth( )) {
        scaleUp( data, width, height );
    } else {
        scaleDown( data, width, height );
    }
}

void CScaler::scaleDown( imgData_t & data, size_t & width, size_t & height ) const {
    while( height > getReqHeight( ) && width > getReqWidth( )) {

        for( size_t y = 0; y < height / 2; y++ ) {
            for( size_t x = 0; x < width / 2; x++ ) {
                data[y][x] = 0;
                data[y][x] += data[y * 2][x * 2] * 0.25;
                data[y][x] += data[y * 2][x * 2 + 1] * 0.25;
                data[y][x] += data[y * 2 + 1][x * 2] * 0.25;
                data[y][x] += data[y * 2 + 1][x * 2 + 1] * 0.25;
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

void CScaler::scaleUp( imgData_t & data, size_t & width, size_t & height ) const {
    while( height < getReqHeight( ) && width < getReqWidth( )) {

        /* resize the array to for the upscaled image*/
        data.resize( height * 2 );
        for( auto & row: data )
            row.resize( width * 2 );

        /* mx and my represent upper left corner of the 2x2 scaling region */
        for( size_t y = 0; y < height; y++ ) {
            size_t my = height * 2 - y * 2 - 2; // -2 to convert size to last index and to select the second to last
            for( size_t x = 0; x < width; x++ ) {
                size_t mx = width * 2 - x * 2 - 2;

                data[my][mx] = data[y][x];
                data[my][mx + 1] = data[y][x];
                data[my + 1][mx] = data[y][x];
                data[my + 1][mx + 1] = data[y][x];
            }
        }

        height *= 2;
        width *= 2;
    }
}
