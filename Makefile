COMPILER    = g++
CPP_OPTIONS = -O3 $(shell sdl2-config --cflags --libs) -s --std=c++17 -pthread

#
#INCLUDES  = -Iinclude -I/usr/local/include/terminalpp-2.0.2
#LINKS     = -L/usr/local/lib/terminalpp-2.0.2 -lterminalpp
#CPP_FILES = $(shell find ./link -name '*.cpp') $(shell find ./link -name '*.c')
#

INCLUDES  = -Iinclude -I/usr/local/include/SDL2 -Isrc
LINKS     = -L/usr/local/lib/libSDL2 -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lX11
CPP_FILES =	$(shell find ./link -name '*.cpp') $(shell find ./link -name '*.c') 


test: clean build
	-./bin/com32 > test.log 2>&1

build: clean
	${COMPILER} ${CPP_OPTIONS} ${INCLUDES} ${LINKS} ${CPP_FILES} ./src/main.cpp -o ./bin/com32
	cp -r ./assets ./bin/assets
	chmod +x ./bin/com32

heady: 
	rm -f ./bin/singleFile.cpp
	heady --source "src" --output "bin/singleFile.cpp"

git: clean bin
	git add *
	git commit
	git pull
	git push

clean:
	-rm -rf bin
	mkdir bin