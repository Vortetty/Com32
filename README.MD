# Com32

A Commodore 64-like interface with a custom version of basic. Designed purely out of boredom.

## Requirements

### Included

- [Lodepng](https://github.com/lvandeve/lodepng)
- [Centurion](https://github.com/albin-johansson/centurion)
- [Threadsafe STL](https://github.com/Vortetty/Threadsafe-STL)
- [EasyLoggingPP](https://github.com/amrayn/easyloggingpp)

### Need installed

For these you may need to modify the makefile to point to them

- [SDL2](https://www.libsdl.org)
- [SDL_image](https://www.libsdl.org/projects/SDL_image)
- [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer)
- [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf)
- LibX11
  - For Arch: `sudo pacman libx11`
  - For Ubuntu, etc: `sudo apt-get intall libX11-devel`
  - For Redhat, Fedora, etc: `sudo yum install libX11-devel`
- [Heady](https://github.com/JamesBoer/Heady) (For generating single-file, not needed if you don't want to do this)

## Known bugs

- Kernel may reject frames and the program will crash
- Sometimes segfaults at startup
