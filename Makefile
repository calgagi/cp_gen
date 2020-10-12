COMPILE = g++ --std=c++17 -O2
EXE = gen 

${EXE}: main.cpp 
	${COMPILE} main.cpp -o ${EXE}

.PHONY: tests
tests:
	cd ./tests && $(MAKE)

clean:
	rm -rf *.o *.out gen test; cd ./tests && $(MAKE) clean