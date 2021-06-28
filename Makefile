COMPILER    = g++
CPP_OPTIONS = -O3 $(shell sdl2-config --cflags --libs) -s --std=c++17 -pthread

#
#INCLUDES  = -Iinclude -I/usr/local/include/terminalpp-2.0.2
#LINKS     = -L/usr/local/lib/terminalpp-2.0.2 -lterminalpp
#CPP_FILES = $(shell find ./link -name '*.cpp') $(shell find ./link -name '*.c')
#

INCLUDES  = -Iinclude -I/usr/local/include/SDL2 -Isrc
LINKS     = -L/usr/local/lib/libSDL2 -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image
CPP_FILES =	$(shell find ./link -name '*.cpp') $(shell find ./link -name '*.c')


test: clean build heady
	chmod +x ./build/c64_term_emulator
	./build/c64_term_emulator

build: clean
	${COMPILER} ${CPP_OPTIONS} ${INCLUDES} ${LINKS} ${CPP_FILES} ./src/main.cpp -o ./build/c64_term_emulator
	cp -r ./assets ./build/assets

heady: 
	rm -f ./build/singleFile.cpp
	heady --source "src" --output "build/singleFile.cpp"

clean:
	-rm -rf build
	mkdir build