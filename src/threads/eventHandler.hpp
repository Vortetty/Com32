#include <centurion.hpp>
#include "windowManager.hpp"
#include "C32colors.hpp"
#include "externs.hpp"
#include "shared.hpp"
#include "globals.hpp"
#include <unistd.h>
#include "threads/forceKillThread.hpp"

void startKillThread(){
    std::thread forceKill(forceKillThreadFunc);
    return;
}

void eventThreadFunc(cen::window &window, cen::renderer &renderer, cen::event &event, int windowScale){
    while (!shouldKillWindow()){
        while( event.poll() ){
            if (event.type().has_value()){
                switch( event.type().value() ){
                    case cen::event_type::quit:
                        windowNeedsKilled = true;
                        startKillThread();
                        return;
                        break;

                    case cen::event_type::key_down:
                        std::cout << "Key pressed: " << SDL_GetKeyName(event.get<cen::keyboard_event>().get().keysym.sym) << "\n";
                        break;

                    default:
                        break;
                }
            }
        }
    }
}