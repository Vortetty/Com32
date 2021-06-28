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