OBJS = RiskyWeather.o
CC = g++
CFLAGS = -std=c++11 -Wall -c
LFLAGS = -std=c++11 -Wall
LIBFLAGS = -ltins

all: riskyweather

riskyweather: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o riskyweather $(LIBFLAGS)

RiskyWeather.o: RiskyWeather.cpp
	$(CC) $(CFLAGS) RiskyWeather.cpp

clean:
	rm *.o riskyweather

