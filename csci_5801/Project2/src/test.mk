CXX=g++
CXXFLAGS = -std=c++11 -g

SOURCES = $(wildcard *.cc)
OBJFILES = $(notdir $(SOURCES:.cpp=.o))

MAINFILES = candidate.cpp party.cpp ballot.cpp coin.cpp ballotQueue.cpp oplDriver.cpp irvDriver.cpp poDriver.cpp textResult.cpp multipleFiles.cpp

LABTESTEXE = all_test
LABEXE = candidate party ballot coin ballotQueue oplDriver irvDriver poDriver textResult multipleFiles

all: ${LABEXE} 

${LABTESTEXE}: 
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib all_test.cpp $(MAINFILES) -lgtest_main -lgtest -pthread -o $@

${LABEXE}: ${LABTESTEXE}
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib main.cpp $(MAINFILES) -lgtest_main -lgtest -pthread -o $@

test: ${LABTESTEXE}

clean:
	rm -f ${LABEXE}
	rm -f ${LABTESTEXE}
	rm -rf *.o
