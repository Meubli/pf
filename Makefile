# You can change these variables if you want to use a different compiler or debugger
CC = gcc

# We use .PHONY to tell make to always run these commands even if a file exists
# with the same name in this directory. For more information on .PHONY, see
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: build-main
build-main: build-dir
	$(CC) -Wall -fno-stack-protector -g -o build/pf src/main.c

.PHONY: check
check:
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install clang"

.PHONY: build-dir
build-dir:
	if [ ! -d build ]; then mkdir build; fi

.PHONY: build-test
build-test: build-dir
	$(CC) -Wall -O0 -g -o build/test.o src/test.c

.PHONY: run
run: build-main
	./build/pf /home/nico/git

.PHONY: test
test: build-test
	./build/test.o

.PHONY: clean
clean:
	rm -rf build

.PHONY: install
install: build-main
	cp build/pf /usr/local/bin

.PHONY: uninstall
uninstall:
	rm /usr/local/bin/pf
