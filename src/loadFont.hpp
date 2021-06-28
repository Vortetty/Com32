#ifndef LOADFONT
#define LOADFONT
#include <iostream>
#include <bitset>
#include <string>

#define LODEPNG_NO_COMPILE_ZLIB
//#define LODEPNG_NO_COMPILE_DECODER
#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_COMPILE_CPP
#include <lodepng.h>

std::vector<bool> loadFont(std::string filename, unsigned &width, unsigned &height){
    std::vector<unsigned char> image; //the raw pixels

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    std::vector<bool> data;

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            data.push_back(
                (image[(y*width+x)*4] == 0 && image[(y*width+x)*4+1] == 0 && image[(y*width+x)*4+2] == 0) ? 1 : 0
            );
        }
    }

    return data;
}
#endif