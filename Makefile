

#compiler / compiler flags
CXX = g++

#SDL2 includes and library linking
SDL2 = -I ../ACPFinalProject/SDL2/include -L ../ACPFinalProject/SDL2/lib/x86 -l SDL2main.lib -l SDL2.lib

main: main.cpp
	$(CXX) $(SDL2) main.cpp -o main