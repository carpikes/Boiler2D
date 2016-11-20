all: build project

build:
	@mkdir -p build
	cd build && cmake ..

project:
	cd build && make -j8

demo1: build project
	build/bin/demo1

demo: build project
	build/bin/demo

clean:
	rm -rf build/

again: clean build project

.PHONY: project run clean again
