

#compiler / compiler flags
CXX = g++

CLASSES := $(wildcard classes/*.cpp)

#SDL2 includes and library linking
SDL2 = -I ../ACPFinalProject/SDL2/include -L ../ACPFinalProject/SDL2/lib/x64 -lSDL2main -lSDL2

main: main.cpp $(CLASSES)
	$(CXX) $(CLASSES) main.cpp $(SDL2)  -o main