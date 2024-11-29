all:
	clang -std=c2x -g -I/usr/local/include/SDL3/ -rpath /usr/local/lib -lSDL3 src/main.c src/display.c src/device.c -o target/emulator
cleanup:
	rm -fr target/emulator
	rm -fr target/test
