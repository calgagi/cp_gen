COMPILE = g++ --std=c++17 -O2
EXE = gen 
LINKERFLAG = -lm

SRCS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=%)

${EXE}: ${SRCS}
	${COMPILE} ${SRCS} -o ${EXE}
