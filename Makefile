objects = vec3.o color.o progress_bar.o
CXX = g++

all: out.ppm

main.exe: $(objects) main.cpp
	g++ $^ -o $@

out.ppm: main.exe
	.\main.exe > $@

clean:
	-rm $(objects) out.ppm
