# This Makefile automatically generates and runs a C++ file that runs 
# all tests. 

COMPILE = g++ --std=c++17 -O2
MAIN_FILE = tests.cpp
EXE = tests
SHELL := /bin/bash
HEADER_FILE = all_headers.cpp
TEST_FILE = all_tests.cpp

START_BRACE := {
END_BRACE := }

${EXE}: ${MAIN_FILE}
	${COMPILE} ${MAIN_FILE} -o ${EXE} 
	./${EXE}
	rm -rf ${EXE} ${MAIN_FILE}

${MAIN_FILE}: ${HEADER_FILE} ${TEST_FILE}
	$(shell \
	cat ${HEADER_FILE} > ${MAIN_FILE}; \
	printf "int main() ${START_BRACE}\n" >> ${MAIN_FILE}; \
	printf "\tbool ans = true;\n" >> ${MAIN_FILE}; \
	cat ${TEST_FILE} >> ${MAIN_FILE}; \
	printf "\tif (!ans) exit(-10);" >> ${MAIN_FILE}; \
	printf "\treturn 0;\n${END_BRACE}" >> ${MAIN_FILE}; \
	rm -f ${HEADER_FILE} ${TEST_FILE}; \
	)

${HEADER_FILE}:
    $(shell \
	printf "#include <bits/stdc++.h>\n" > ${HEADER_FILE}; \
	printf "using namespace std;\n" >> ${HEADER_FILE}; \
	printf "#define ll long long\n" >> ${HEADER_FILE}; \
	printf "#define ld long double\n" >> ${HEADER_FILE}; \
	printf "#define FAIL \"\\\033[1;31mfailed\\\033[0m\"\n" >> ${HEADER_FILE}; \
	printf "#define PASS \"\\\033[1;32mpassed\\\033[0m\"\n" >> ${HEADER_FILE}; \
	printf "#define cpassert(X) if (!(X)) return false;\n" >> ${HEADER_FILE}; \
	for i in `find ../lib/ -type f -iwholename "*lib/*.hpp"`; do \
		printf "#include \"../lib/$${i:7:-4}.hpp\"\n" >> ${HEADER_FILE}; \
	done; \
	for i in `find . -type f -iwholename "*.hpp"`; do \
		printf "#include \"./$${i:2:-4}.hpp\"\n" >> ${HEADER_FILE}; \
	done; \
	)

${TEST_FILE}:
	$(shell \
	for i in `find . -type f -iwholename "*.hpp"`; do \
		printf "\tans = $${i:2:-4}::runTests() && ans;\n" >> ${TEST_FILE}; \
	done \
	)

clean: 
	rm -rf ${HEADER_FILE} ${TEST_FILE} ${MAIN_FILE} ${EXE}
