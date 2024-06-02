objects = vec3.o color.o progress_bar.o

all: out.ppm

main: $(objects)

out.ppm: main
	.\main > $@

clean:
	-rm $(objects) out.ppm
