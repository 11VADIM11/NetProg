
CXX = g++

CXXFLAGS = -Wall -Wextra -g

TARGET = EchoClient

SRCS = EchoClient.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)  

clean:
	rm -f $(TARGET)
