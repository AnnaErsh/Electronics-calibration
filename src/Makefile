ex:= $(addprefix ../bin/, Calibration Display)

all: $(ex)

%.o: %.cpp
	g++ -O2 -std=c++11 -Wall -I$(shell root-config --incdir) -c -ggdb $< -o $@

../bin/Calibration: Calibration.o
	g++ -O2 -std=c++11 -Wall $(shell root-config --nonew --libs) $^ -o $@ -ggdb $(shell root-config --nonew --libs) 

../bin/Display: Display.o
	g++ -O2 -std=c++11 -Wall $(shell root-config --nonew --libs) $^ -o $@ -ggdb $(shell root-config --nonew --libs) 

clean:
	rm *.o $(ex)
tar: 
	tar -czf $(ex) *.c Make life
