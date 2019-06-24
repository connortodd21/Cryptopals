CC=gcc
CCFLAGS= -g

all: hex_to_base64 hex_xor

hex_to_base64: hex_to_base64.c
		$(CC) -g -o hex_to_base64 hex_to_base64.c 

hex_xor: hex_xor.c
		$(CC) -g -o hex_xor hex_xor.c
clean: 
	rm -rf hex_to_base64 hex_to_base64.dSYM hex_xor hex_xor.dSYM
