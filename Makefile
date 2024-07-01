# hex2bin Makefile
# 

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

hex2bin: hex2bin.c ## Build app
	$(CC) -Wall -Wextra -Wpedantic -o hex2bin hex2bin.c

debug: hex2bin.c ## Generate a debug build
	$(CC) -g -DDEBUG -o hex2bin_dbg hex2bin.c

all: hex2bin

lint:		## Check source with splint linter
	splint -compdef hex2bin.c

test: hex2bin	## Run a simple test
	./hex2bin A5 > output.txt
	diff output.txt golden.txt

clean:		## Remove app binary
	rm -f hex2bin 

distclean:	## Remove all object code
	rm -f hex2bin hex2bin.o

destroy:	## Remove everything
	rm -rf hex2bin hex2bin.o output.txt

.PHONY: help

# From https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help:		## Show this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
