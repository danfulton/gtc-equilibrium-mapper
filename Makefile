gtc-equilibrium-mapper: main.cpp
	g++ -o gtc-equilibrium-mapper main.cpp -lyaml-cpp -lboost_program_options -lhdf5 -lhdf5_cpp

.PHONY: clean

clean:
	rm -f gtc-equilibrium-mapper

