CXX = g++

CXXFLAGS = -Wall -Wextra -g

TARGET = DaytimeClient

SRCS = DaytimeClient.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)  

clean:
	rm -f $(TARGET)

