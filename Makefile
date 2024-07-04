# hex2bin makefile

CC = gcc

hex2bin: hex2bin.c 	## Build app
	$(CC) -Wall -Wextra -Wpedantic -o hex2bin hex2bin.c

debug: hex2bin.c 	## Generate a debug build
	$(CC) -g -DDEBUG -o hex2bin_dbg hex2bin.c

all: hex2bin

lint:			## Check source with splint linter
	splint hex2bin.c

test: hex2bin		## Run a simple test
	./hex2bin A5 > output.txt
	diff output.txt golden.txt

clean:			## Remove object code, binaries and test output
	rm -rf hex2bin hex2bin.o output.txt hex2bin_dbg

# Build a makefile help menu dynamically using, inspired by the pattern from:
# https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help
help:			## Show this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
