#include <stdint.h>
#include <centurion.hpp>
#include "C32colors.hpp"

#ifndef GLOBALS
#define GLOBALS

typedef uint8_t byte;

struct Vec2 {
    int x, y;
};
struct Vec2f {
    float x, y;
};
struct Vec4 {
    int top, bottom, left, right;
};

class character {
    public:
        char chr;
        cen::color fg=colors::lightBlue, bg=colors::blue;

        character (char _chr){
            chr = _chr;
        }
        character (char _chr, cen::color _fg, cen::color _bg){
            chr = _chr;
            fg = _fg;
            bg = _bg;
        }
        character (){
            chr = ' ';
        }

        character inverted(){
            return character(chr, bg, fg);
        }
};

struct modifiedChar {
    character chr;
    Vec2 pos;
};

struct initLine {
    byte lineNum;
    std::string line;
};

Vec2 ScreenSize = {320, 200};
Vec4 ScreenPadding = {16, 16, 16, 16};
Vec2 CharSize = {8, 8};
Vec2 CharsWH = {ScreenSize.x/CharSize.x, ScreenSize.y/CharSize.y};

#endif