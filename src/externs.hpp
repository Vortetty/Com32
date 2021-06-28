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
