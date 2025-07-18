##
# life: a simple C cli implementation of Conway's game of life
#
# @file
# @version 0.1

life: life.c
	$(CC) life.c -o life

clean:
	rm life
# end
