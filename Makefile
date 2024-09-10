
CC = g++
CPPFLAGS = -g -I./ -INoiseGenerators/ -std=c++20
LINKER_FLAGS = -lSDL2 -lGL -lX11 -ldl -lpthread -lrt
SRCS=$(subst main.cpp,,$(wildcard *.cpp)) $(wildcard NoiseGenerators/*.cpp)
OBJS=$(SRCS:.cpp=.o )

all : main.cpp $(OBJS)
	$(CC) main.cpp -o main $(CPPFLAGS) $(LINKER_FLAGS) $(BGFX_HEADERS) $(OBJS)

run : all
	./main

clean :
	rm main -f
	find . -name "*.o" -type f -delete

main.o : main.cpp
	@:

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@