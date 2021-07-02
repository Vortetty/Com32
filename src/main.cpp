/*
 * Copyright 2021 Vortetty
 * Licenced under Apache 2.0
 */
#include <centurion.hpp>
#include "windowManager.hpp"
#include "C32colors.hpp"
#include <thread>
#include "renderer.hpp"
#include "inputHandler.hpp"
#include <iostream>
#include "eventHandler.hpp"

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
    std::thread inputHandlerThread(inputThreadFunc, std::ref(window), std::ref(renderer), std::ref(event), WINDOW_SCALE);
    std::thread eventThread(eventThreadFunc, std::ref(window), std::ref(renderer), std::ref(event), WINDOW_SCALE);
    //renderThreadFunc(window, renderer, event, WINDOW_SCALE);
    std::cout << "Made Threads\n";
    
    renderThread.join();
    renderCursorThread.join();
    inputHandlerThread.join();
    eventThread.join();
    std::cout << "Threads Finished\n";

    killWindow(window);
    std::cout << "Killed Window\n";

    return 0;
}