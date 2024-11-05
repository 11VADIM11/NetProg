CC = g++
CFLAGS = -Wall -Wextra -g

all: DaytimeClient

udp_client: DaytimeClient.cpp
	$(CC) $(CFLAGS) DaytimeClient.cpp -o DaytimeClient

clean:
	rm -f DaytimeClient
	
	.PHONY: all clean
