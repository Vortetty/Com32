#include <centurion.hpp>
#include "windowManager.hpp"
#include "C32colors.hpp"
#include "externs.hpp"
#include "shared.hpp"
#include "globals.hpp"
#include <unistd.h>

void createSegfault(){ // This was probably stupid lol
    std::cout.flush();
    int segfault[1];
    segfault[0] = segfault[999999999];
}

void forceKillThreadFunc(){
    int segfault[1];
    sleepms(5000);
    //createSegfault();
    exit(15); // Terminated
}