#include <centurion.hpp>
#include "threadsafe/vector"
#include "threadsafe/deque"
#include "globals.hpp"
#include "C32colors.hpp"
#include "loadFont.hpp"
#include "externs.hpp"
#include <chrono>
#include <thread>


#ifndef SHARED_VARS
#define SHARED_VARS

std::threadsafe::safe_vector<initLine> initLines = { // Spaces will not modify stuff
    {1, "      **** Com32 Basic Ver1.0 ****      "},
    {2, "           64KB Ram Availible           "}
};

std::threadsafe::safe_vector<std::threadsafe::safe_vector<character>> charBuf;
std::threadsafe::safe_deque<modifiedChar> charChanges;
std::threadsafe::safe_vector<bool> fontBitmap;
bool windowKilled=false;
Vec2 cursorPosition={0, 3};

unsigned fontBitmapWidth, fontBitmapHeight;

void sharedVarsInit(){
    for (int i = 0; i < CharsWH.x; i++){
        std::threadsafe::safe_vector<character> tmp;
        for (int i1 = 0; i1 < CharsWH.y; i1++) tmp.push_back(character());
        charBuf.push_back(tmp);
    }
    std::cout << "Shared init> initialized buffer\n";

    for (auto &e : initLines) {
        int x = 0;
        for (auto &chr : e.line) {
            if (chr != ' '){
                std::cout << "Shared init> Pushing " << chr << "\n";
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

inline void sleepms(long long ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif