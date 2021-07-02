#include <centurion.hpp>
#include "threadsafe/vector"

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