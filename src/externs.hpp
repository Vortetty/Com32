#include "threadsafe/deque"
#include "threadsafe/vector"
#include <globals.hpp>

#ifndef EXTERNS
#define EXTERNS

extern std::threadsafe::safe_vector<std::threadsafe::safe_vector<character>> charBuf;
extern std::threadsafe::safe_deque<modifiedChar> charChanges;
extern std::threadsafe::safe_vector<bool> fontBitmap;
extern bool windowKilled;
extern bool windowNeedsKilled;
extern Vec2 cursorPosition;
extern bool shouldUpdateText;

#endif
