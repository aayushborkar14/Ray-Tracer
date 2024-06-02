all: out.ppm

main.exe: vec3.o color.o
	g++ main.cpp vec3.o color.o -o main.exe

out.ppm: main.exe
	.\main.exe > out.ppm

vec3.o:
	g++ -c vec3.cpp -o vec3.o

color.o:
	g++ -c color.cpp -o color.o

clean:
	rm vec3.o color.o main.exe out.ppm
