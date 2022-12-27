CC = g++ -std=c++14

CFLAGS = -g -Wall -Wextra -Werror
CPATH = -I include/
DLIB = -fPIC -shared -Wl,-rpath,libs/

all: bin/game.out

bin/game.out: src/main.cpp libs/game.so  libs/model.so libs/fox.so libs/hare.so  
	$(CC) $(CFLAGS) $(CPATH) -fPIC -Wl,-rpath,libs/ -o $@ $^

libs/fox.so: src/fox.cpp
	$(CC) $(DLIB) $(CFLAGS) $(CPATH) -o $@ $^

libs/hare.so: src/hare.cpp
	$(CC) $(DLIB) $(CFLAGS) $(CPATH) -o $@ $^

libs/game.so: src/game.cpp
	$(CC) $(DLIB) $(CFLAGS) $(CPATH) -o $@ $^

libs/model.so: src/model.cpp
	$(CC) $(DLIB) $(CFLAGS) $(CPATH) -o $@ $^

.SILENT: clean 

clean:
	find . -type f -name "*.so" -exec rm -f {} \;
	find . -type f -name "*.a" -exec rm -f {} \;
	find . -type f -name "*.out" -exec rm -f {} \;
	find . -type f -name "*.tmp" -exec rm -f {} \;

run:
	bin/game.out data/input.txt data/outut.txt

rebuild: clean all