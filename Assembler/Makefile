build-dir = ./bin
src-dir = ./src

compile:
	g++ -Wall -o $(build-dir)/main $(src-dir)/*.cpp

run:
	$(build-dir)/main

compile.run:
	g++ -Wall -o $(build-dir)/main $(src-dir)/*.cpp
	$(build-dir)/main
compile.run.ntf:
	g++ -Wall -o $(build-dir)/main $(src-dir)/*.cpp
	$(build-dir)/main t.asm

clean:
	rm bin/*
