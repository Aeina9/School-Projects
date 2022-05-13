CXX=g++
CXXFLAGS = -std=c++11 -g
GTEST_DIR=googletest/googletest

all: all_test candidate party ballot coin ballotQueue oplDriver irvDriver

candidate: candidate.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib candidate.o main.cpp -o $@

party: party.o candidate.o coin.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib party.o candidate.o coin.o main.cpp -o $@

ballot: ballot.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib ballot.o main.cpp -o $@

coin: coin.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib coin.o main.cpp -o $@

ballotQueue: ballotQueue.o ballot.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib ballotQueue.o ballot.o main.cpp -o $@

oplDriver: oplDriver.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib oplDriver.o main.cpp -o $@

irvDriver: irvDriver.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib irvDriver.o main.cpp -o $@

all_test: candidate.o party.o ballot.o coin.o ballotQueue.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib all_test.cpp candidate.o party.o ballot.o coin.o ballotQueue.o -lgtest_main -lgtest -pthread -o $@

clean:
	rm -f all_test candidate candidate.o party party.o ballot ballot.o coin coin.o ballotQueue ballotQueue.o oplDriver oplDriver.o irvDriver irvDriver.o
