#include <centurion.hpp>
#include <vector>
#include <deque>
#include "globals.hpp"
#include "C32colors.hpp"
#include "loadFont.hpp"
#include "externs.hpp"

#ifndef SHARED_VARS
#define SHARED_VARS

std::vector<initLine> initLines = { // Spaces will not modify stuff
    {1, "      **** Com32 Basic Ver1.0 ****      "},
    {2, "           64KB Ram Availible           "}
};

std::vector<std::vector<character>> charBuf;
std::deque<modifiedChar> charChanges;
std::vector<bool> fontBitmap;
bool windowKilled=false;
Vec2 cursorPosition={0, 3};

unsigned fontBitmapWidth, fontBitmapHeight;

void sharedVarsInit(){
    for (int i = 0; i < CharsWH.x; i++){
        std::vector<character> tmp;
        for (int i1 = 0; i1 < CharsWH.y; i1++) tmp.push_back(character());
        charBuf.push_back(tmp);
    }
    std::cout << "Shared init> initialized buffer\n";

    for (auto &e : initLines) {
        int x = 0;
        for (auto &chr : e.line) {
            if (chr != ' '){
                charChanges.push_back(
                    {
                        character(chr),
                        {x, e.lineNum}
                    }
                );
            }
            x += 1;
        }
    }
    std::cout << "Shared init> Generated first display changes\n";

    fontBitmap = loadFont("assets/basicFont.png", fontBitmapWidth, fontBitmapHeight);
    std::cout << "Shared init> Loaded font\n";
}

#endif