

#compiler / compiler flags
CXX = g++

#SDL2 includes and library linking
SDL2 = -I ../ACPFinalProject/SDL2/include -L ../ACPFinalProject/SDL2/lib/x86 -lSDL2main -lSDL2

main: main.cpp
	$(CXX) main.cpp $(SDL2)  -o main