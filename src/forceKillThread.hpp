#include <centurion.hpp>
#include "windowManager.hpp"
#include "C32colors.hpp"
#include "externs.hpp"
#include "shared.hpp"
#include "globals.hpp"
#include <unistd.h>

void createSegfault(){
    std::cout.flush();
    int segfault[1];
    segfault[0] = segfault[99999999999999999999999];
}

void forceKillThreadFunc(){
    int segfault[1];
    sleepms(5000);
    createSegfault();
}