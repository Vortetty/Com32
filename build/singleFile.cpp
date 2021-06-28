

// begin --- main.cpp --- 

/*
 * Copyright 2021 Vortetty
 * Licenced under Apache 2.0
 */
#include <centurion.hpp>

// begin --- windowManager.hpp --- 

#include <centurion.hpp>

#ifndef WINDOW_MANAGER
#define WINDOW_MANAGER
std::pair<cen::window, cen::renderer> initWindow(cen::library &centurion, bool showOnCreate=false){
    std::pair<cen::window, cen::renderer> wr = cen::make_window_and_renderer();

    if (showOnCreate) wr.first.show();

    return wr;
}

volatile bool shouldKillWindow(cen::event &event){
    bool tmp = false;
    while (event.poll()){
        tmp = event.is<cen::quit_event>();
        if (tmp) return true;
    }
    return false;
}

std::vector<cen::event_type> getEvents(cen::event &event){
    std::vector<cen::event_type> events;
    while (event.poll()){
        std::optional<cen::event_type> e = event.type();
        if (e.has_value()) events.push_back(e.value());
    }
    return events;
}

void showWindow(cen::window &window){
    window.show();
}

void killWindow(cen::window &window){
    window.hide();
}
#endif

// end --- windowManager.hpp --- 



// begin --- C32colors.hpp --- 

#include <centurion.hpp>

#ifndef COLORS
#define COLORS
namespace colors {
    cen::color black      (0, 0, 0); // 0
    cen::color white      (255, 255, 255); // 1
    cen::color red        (136, 0, 0); // 2
    cen::color cyan       (170, 255, 238); // 3
    cen::color violet     (204, 68, 204); // 4
    cen::color purple     (204, 68, 204); // 4 but different name
    cen::color green      (0, 204, 85); // 5
    cen::color blue       (0, 0, 170); // 6
    cen::color yellow     (238, 238, 119); // 7
    cen::color orange     (221, 136, 85); // 8
    cen::color brown      (102, 68, 0); // 9
    cen::color lightRed   (255, 119, 119); // 10
    cen::color darkGrey   (51, 51, 51); // 11
    cen::color grey       (119, 119, 119); // 12
    cen::color lightGreen (170, 255, 102); // 13
    cen::color lightBlue  (0, 136, 255); // 14
    cen::color lightGrey  (187, 187, 187); // 15
}
#endif

// end --- C32colors.hpp --- 


#include <thread>

// begin --- renderer.hpp --- 

#include <centurion.hpp>

// begin --- externs.hpp --- 

#include <deque>
#include <vector>
#include <globals.hpp>

#ifndef EXTERNS
#define EXTERNS

extern std::vector<std::vector<character>> charBuf;
extern std::deque<modifiedChar> charChanges;
extern std::vector<bool> fontBitmap;
extern bool windowKilled;
extern Vec2 cursorPosition;

#endif


// end --- externs.hpp --- 



// begin --- shared.hpp --- 

#include <centurion.hpp>
#include <vector>
#include <deque>

// begin --- globals.hpp --- 

#include <stdint.h>
#include <centurion.hpp>

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

// end --- globals.hpp --- 



// begin --- loadFont.hpp --- 

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

// end --- loadFont.hpp --- 



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

// end --- shared.hpp --- 


#include <unistd.h>
#include <time.h>

void drawChar(character chr, int x, int y, cen::renderer &renderer, int windowScale, bool invert=false){
    int offsetx = x*8*windowScale;
    int offsety = y*8*windowScale;

    Vec2 bitmapPos = {(int)chr.chr % (int)std::sqrt(256) * 8, (int)chr.chr / (int)std::sqrt(256) * 8};

    //if (cursorPosition.x == x && cursorPosition.y == y && invert) {
    //    bitmapPos = {219 % (int)std::sqrt(256) * 8, 219 / (int)std::sqrt(256) * 8};
    //}

    //renderer.set_color(invert ? chr.fg : chr.bg);
    //renderer.fill_rect(
    //    cen::rect(
    //        offsetx + ScreenPadding.left*windowScale, offsety + ScreenPadding.top*windowScale,
    //        8*windowScale, 8*windowScale
    //    )
    //);
    
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            renderer.set_color(
                invert ? (fontBitmap[(bitmapPos.x+x)+((bitmapPos.y+y)*fontBitmapWidth)] ? chr.bg : chr.fg) : (fontBitmap[(bitmapPos.x+x)+((bitmapPos.y+y)*fontBitmapWidth)] ? chr.fg : chr.bg)
            );
            renderer.fill_rect(
                cen::rect(
                    x*windowScale + offsetx + ScreenPadding.left*windowScale, y*windowScale + offsety + ScreenPadding.top*windowScale,
                    windowScale, windowScale
                )
            );
        }
        //std::cout << "\n";
    }
}
void drawChar(character chr, Vec2 pos, cen::renderer &renderer, int windowScale, bool invert=false){
    drawChar(
        chr, pos.x, pos.y, renderer, windowScale, invert
    );
}

void pushFrame(cen::window &window, cen::renderer &renderer){
    cen::texture pastRender(renderer, renderer.capture(window.get_pixel_format()));
    renderer.present();
    renderer.render(pastRender, cen::rect(0, 0, window.width(), window.height()));
}

Vec2 windowSize = {ScreenSize.x + ScreenPadding.top + ScreenPadding.bottom, ScreenSize.y + ScreenPadding.left + ScreenPadding.right};

void renderThreadFunc(cen::window &window, cen::renderer &renderer, cen::event &event, int windowScale){
    while (!shouldKillWindow(event)){
        auto toPopStart = charChanges.begin();
        auto toPopEnd = charChanges.end();
        for (auto &editedChar : charChanges){
            drawChar(
                editedChar.chr,
                editedChar.pos,
                renderer,
                windowScale
            );
            pushFrame(window, renderer);
            //sleep(1);

            if (shouldKillWindow(event)){
                killWindow(window);
                windowKilled = true;
                return;
            }

            std::cout << "Drew char \"" << editedChar.chr.chr << "\"\n";

            //try {
                charBuf.at(editedChar.pos.x).at(editedChar.pos.y) = editedChar.chr.chr;
            //}
            //catch (...){}
        }
        charChanges.erase(toPopStart, toPopEnd);
    }
    
    killWindow(window);
    windowKilled = true;
}

void renderCursorThreadFunc(cen::window &window, cen::renderer &renderer, cen::event &event, int windowScale){
    bool toggle = false;
    while (!windowKilled){
        drawChar(
            charBuf.at(cursorPosition.x).at(cursorPosition.y),
            cursorPosition,
            renderer,
            windowScale,
            toggle
        );
        pushFrame(window, renderer);
        toggle = !toggle;
        sleep(1);
    }
}

// end --- renderer.hpp --- 


#include <iostream>

#define WINDOW_SCALE 2

int main(){
    cen::library centurion; 

    cen::event event;
    cen::keyboard keyboard;

    auto [window, renderer] = initWindow(centurion, false);
    window.set_resizable(false);
    window.set_size({(ScreenSize.x + ScreenPadding.top + ScreenPadding.bottom)*WINDOW_SCALE, (ScreenSize.y + ScreenPadding.left + ScreenPadding.right)*WINDOW_SCALE});
    window.set_icon(cen::surface("assets/icon.png"));
    window.set_title("Com32");
    showWindow(window);
    std::cout << "Made Window\n";

    renderer.clear_with(colors::lightBlue);
    renderer.set_color(colors::blue);
    renderer.fill_rect(
        cen::rect(ScreenPadding.top*WINDOW_SCALE, ScreenPadding.left*WINDOW_SCALE, ScreenSize.x*WINDOW_SCALE, ScreenSize.y*WINDOW_SCALE)
    );
    pushFrame(window, renderer);
    std::cout << "Colored Window\n";

    sharedVarsInit();
    std::cout << "Initialized Shared Vars\n";

    std::thread renderThread(renderThreadFunc, std::ref(window), std::ref(renderer), std::ref(event), WINDOW_SCALE);
    std::thread renderCursorThread(renderCursorThreadFunc, std::ref(window), std::ref(renderer), std::ref(event), WINDOW_SCALE);
    //renderThreadFunc(window, renderer, event, WINDOW_SCALE);
    std::cout << "Made Threads\n";
    
    renderThread.join();
    renderCursorThread.join();
    std::cout << "Threads Finished\n";

    killWindow(window);
    std::cout << "Killed Window\n";

    return 0;
}

// end --- main.cpp --- 

