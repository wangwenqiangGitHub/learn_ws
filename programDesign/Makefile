src = $(wildcard ./*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))
target = app
CC = g++
flags = --std=c++11

$(target):$(obj)
	$(CC) $(obj) -o $(target) $(flags) -g

%.o:%.cpp
	$(CC) -c $< -o $@ -g

.PHONY:clean
clean:
	rm -rf $(obj) $(target)
