CXX=g++
CXXFLAGS=-std=c++11 -g -Wall -O3 -lncurses -Wno-unused-command-line-argument


default: build/bin/snake

build: 
	mkdir -p build/bin

clean: 
	rm -r build

run: snake
	./build/bin/snake

build/main.o: main.h main.cpp build
	echo "Compiling main.o"
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

build/game.o: game.h game.cpp build
	echo "Compiling game.o"
	$(CXX) $(CXXFLAGS) -c game.cpp -o build/game.o

build/Food.o: Food.h Food.cpp build
	echo "Compiling Food.o"
	$(CXX) $(CXXFLAGS) -c Food.cpp -o build/Food.o

build/log.o: log.h log.cpp build
	echo "Compiling log.o"
	$(CXX) $(CXXFLAGS) -c log.cpp -o build/log.o

build/Panel.o: Panel.h Panel.cpp build
	echo "Compiling Panel.o"
	$(CXX) $(CXXFLAGS) -c Panel.cpp -o build/Panel.o

build/Snake.o: Snake.h Snake.cpp build
	echo "Compiling Snake.o"
	$(CXX) $(CXXFLAGS) -c Snake.cpp -o build/Snake.o

snake: build/main.o  build/game.o  build/Food.o  build/log.o  build/Panel.o  build/Snake.o
	echo 'Linking all'
	$(CXX) $(CXXFLAGS) build/main.o build/game.o build/Food.o build/log.o build/Panel.o build/Snake.o -o build/bin/snake

