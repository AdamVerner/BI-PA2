//
// Created by vernead2 on 01.05.20.
//

#pragma once

#include <cstddef>

#include "dataTypes.h"

/**
 * Best effort filter.
 * This filter does not resize to precise size, it can only increase/decrease by powers of 2
 *
 * When upscaling each pixel is stretched into 4 pixels. So each dimension is doubled.
 * This process is repeated unless both width and height are greater or equal to their requested size.
 *
 * When downscaling each 4 pixels are shrunk into 1, halving each dimension
 * Similarly to upscaling, this process is repeated unless dimensions are less or equal to the request
 *
 * TODO implement percentage scaler
 * */
class CScaler {
public:
    CScaler( size_t width, size_t height ) : mReqWidth( width ), mReqHeight( height ) { }

    CScaler() = delete;

    virtual void processData( imgData_t & data, size_t & width, size_t & height ) const;

    inline size_t getReqWidth( ) const { return mReqWidth; }
    inline size_t getReqHeight( ) const { return mReqHeight; }

protected:
    size_t mReqWidth;
    size_t mReqHeight;

private:
    void scaleDown( imgData_t & data, size_t & width, size_t & height ) const;
    void scaleUp( imgData_t & data, size_t & width, size_t & height ) const;

};


