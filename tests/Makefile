# This Makefile automatically generates and runs a C++ file that runs 
# all tests. 
#   * Tests must be in tests/<ds_name>Tester.hpp for <ds_name>
#   * The class in <ds_name>Tester.hpp must be named <ds_name>Tester
#   * The class must have an entry point called runTests(), which will
#     called by the file that is generated.

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

${MAIN_FILE}: ${HEADER_FILE} ${TEST_FILE}
	$(shell \
	cat ${HEADER_FILE} > ${MAIN_FILE}; \
	printf "int main() ${START_BRACE}\n" >> ${MAIN_FILE}; \
	cat ${TEST_FILE} >> ${MAIN_FILE}; \
	printf "\treturn 0;\n${END_BRACE}" >> ${MAIN_FILE}; \
	rm -f ${HEADER_FILE} ${TEST_FILE}; \
	)

${HEADER_FILE}:
    $(shell \
	printf "#include <bits/stdc++.h>\nusing namespace std;\n" > ${HEADER_FILE}; \
	for i in `find ../lib/ -type f -iwholename "*lib/*.hpp"`; do \
		printf "#include \"$${i:7:-4}Tester.hpp\"\n" >> ${HEADER_FILE}; \
	done \
	)

${TEST_FILE}:
	$(shell \
	for i in `find ../lib/ -type f -iwholename "*lib/*.hpp"`; do \
		printf "\t$${i:7:-4}Tester $${i:7:-4}Test;\n\t$${i:7:-4}Test.runTests();\n" >> ${TEST_FILE}; \
	done \
	)

clean: 
	rm -rf ${HEADER_FILE} ${TEST_FILE} ${MAIN_FILE} ${EXE}