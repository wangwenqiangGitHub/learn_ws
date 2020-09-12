src =$(wildcard ./*.c)
obj = $(patsubst %.c, %.o,$(src))

target = hello
CC = gcc
$(target):$(obj)
	$(CC) $(obj) -o $(target)

%.o: %.c
	$(CC)  -c $< -o $@

.PHNY:clean
clean:
	rm -rf $(obj) $(target)
