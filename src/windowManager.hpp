#include <centurion.hpp>
#include "threadsafe/vector"
#include "externs.hpp"
#include "shared.hpp"

#ifndef WINDOW_MANAGER
#define WINDOW_MANAGER
std::pair<cen::window, cen::renderer> initWindow(cen::library &centurion, bool showOnCreate=false){
    std::pair<cen::window, cen::renderer> wr = cen::make_window_and_renderer();

    if (showOnCreate) wr.first.show();

    return wr;
}

inline bool shouldKillWindow() { return windowNeedsKilled; };

std::threadsafe::safe_vector<cen::event_type> getEvents(cen::event &event){
    std::threadsafe::safe_vector<cen::event_type> events;
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