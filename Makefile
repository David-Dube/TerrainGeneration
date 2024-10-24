SHELL := /bin/bash

CC = g++
CPPFLAGS = -g -I./ -INoiseGenerators/ -INoiseGenerators/Biomes/ -std=c++20 -pthread
LINKER_FLAGS = -lSDL2 -lGL -lX11 -ldl -lrt -lSDL2_ttf -lSDL2_image -lpthread
SRCS=$(subst main.cpp,,$(wildcard *.cpp)) $(wildcard NoiseGenerators/*.cpp) $(wildcard NoiseGenerators/Biomes/*.cpp)
OBJS=$(SRCS:.cpp=.o )

all : main.cpp $(OBJS)
	$(CC) main.cpp -o main $(CPPFLAGS) $(LINKER_FLAGS) $(OBJS)

run : all
	./main

benchmark : all
	time ./main benchmark

clean :
	rm main -f
	find . -name "*.o" -type f -delete

main.o : main.cpp
	@:

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(LINKER_FLAGS)