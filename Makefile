gtc-equilibrium-mapper: main.cpp
	h5c++ -o gtc-equilibrium-mapper main.cpp -lyaml-cpp
	rm main.o

.PHONY: clean

clean:
	rm -f main.o gtc-equilibrium-mapper

