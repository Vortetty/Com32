#include <centurion.hpp>
#include "windowManager.hpp"
#include "C32colors.hpp"
#include "externs.hpp"
#include "shared.hpp"
#include "globals.hpp"
#include <mutex>

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

std::mutex mutex;
void pushFrame(cen::window &window, cen::renderer &renderer){
    std::lock_guard<std::mutex> lock(mutex);
    cen::texture pastRender(renderer, renderer.capture(window.get_pixel_format()));
    renderer.present();
    renderer.render(pastRender, cen::rect(0, 0, window.width(), window.height()));
}

Vec2 windowSize = {ScreenSize.x + ScreenPadding.top + ScreenPadding.bottom, ScreenSize.y + ScreenPadding.left + ScreenPadding.right};

void renderThreadFunc(cen::window &window, cen::renderer &renderer, cen::event &event, int windowScale){
    while (!shouldKillWindow()){
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
            //sleepms(1000);

            if (shouldKillWindow()){
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
        sleepms(500);
    }
}