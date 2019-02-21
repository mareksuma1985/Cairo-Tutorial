CFLAGS=`pkg-config --libs --cflags gtkmm-3.0 cairomm-1.0`

all: attitude-indicator

attitude-indicator: main.cpp
	clang $(CFLAGS) -g -std=c++2a -lstdc++ -lm *.cpp -o attitude-indicator

clean:
	rm -f *.o attitude-indicator