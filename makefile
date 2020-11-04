EX_NAME=main.cpp
EX=boxing_timer

SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(patsubst ./src/%.cpp,./obj/%.o,$(SOURCES))

CC=g++
CFLAGS= -w -Wall -std=c++11 

LINKWX_IMG=`wx-config --libs --cxxflags`

LIBS=-L /usr/local/lib -I /usr/local/include/POCO -lPocoFoundation -lPocoUtil -lSDL2 -lSDL2_mixer

all : $(EX)

$(OBJECTS): ./obj/%.o : ./src/%.cpp
	$(CC) $(CFLAGS) $(LIBS) $(LINKWX_IMG) -c $< -o $@

$(EX): $(OBJECTS)
	$(CC) -o $@ $(EX_NAME) $^ $(CFLAGS) $(LINKWX_IMG) $(LIBS)

.PHONY: clean_full
clean_full:
	rm -f boxing_timer
	rm -f ./obj/*.o 

.PHONY: clean
clean:
	rm -f boxing_timer
