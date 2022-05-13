/**
 * @file all_test.cpp
 * @brief Google testing file
 * @author Amy Nguyen
 * @author Kaley Schiffler
 * @author Hoin Jang
 */

#include "ballot.h"
#include "ballotQueue.h"
#include "candidate.h"
#include "coin.h"
#include "gtest/gtest.h"
#include "party.h"

/**
 * @brief Google testing, unit and integration tests
 */
class AllTest : public ::testing::Test {
 public:
  void SetUp() {}
  void TearDown() {}

 protected:
};

/**************Ballot Test****************/

/**
 * @brief Ballot class tests push() and isEmpty()
 */
TEST_F(AllTest, BallotEmptyTest) {
  Ballot ballot;

  EXPECT_EQ(ballot.isEmpty(), true) << "Ballot is not empty when it should be";
  ballot.push(3);
  EXPECT_EQ(ballot.isEmpty(), false) << "Ballot is empty when it shouldn't be";
}

/**
 * @brief Ballot class tests push() and pop()
 */
TEST_F(AllTest, BallotPopTest) {
  Ballot ballot;

  ASSERT_EXIT(ballot.pop(), testing::KilledBySignal(SIGSEGV), "");  // seg fault

  ballot.push(1);
  EXPECT_EQ(ballot.pop(), 1) << "Incorrect ballot vote";
  EXPECT_EQ(ballot.isEmpty(), true) << "Ballot not popped off";
}

/**************Candidate Test****************/

/**
 * @brief Candidate class tests setName() and getName()
 */
TEST_F(AllTest, CandidateNameTest) {
  Candidate c1;
  Candidate c2;

  c1.setName("John");

  EXPECT_EQ(c1.getName(), "John") << "Incorrect candidate name";
  EXPECT_EQ(c2.getName(), "None") << "Incorrect candidate name";
}

/**
 * @brief Candidate class tests getNumVotes() and addVotes()
 */
TEST_F(AllTest, CandidateAddVoteTest) {
  Candidate c1;
  EXPECT_EQ(c1.getNumVotes(), 0) << "Votes should be 0";

  c1.addVote();  // adds a vote to the candidate
  EXPECT_EQ(c1.getNumVotes(), 1) << "Incorrect number of votes";

  c1.addVote();
  EXPECT_EQ(c1.getNumVotes(), 2) << "Incorrect number of votes";
}

/**
 * @brief Candidate and party class integration tests adding a candidate to a
 * party
 */
TEST_F(AllTest, AddCandidateToPartyTest) {
  Party p;
  EXPECT_EQ(p.getNumCandidates(), 0) << "Incorrect number of candidates";

  // Integration Test
  Candidate* c = new Candidate();
  c->setName("Ben");
  c->addVote();

  p.addCandidate(c);
  EXPECT_EQ(p.getNumCandidates(), 1) << "Incorrect number of candidates";

  EXPECT_EQ(p.getPopularCandidate()->getName(), "Ben")
      << "Candidate not in party";
}
/**************Party Test****************/

/**
 * @brief Party class tests getName() and setName()
 */
TEST_F(AllTest, PartyNameTest) {
  Party p1;
  Party p2;

  p1.setName("R");

  EXPECT_EQ(p1.getName(), "R") << "Incorrect party name";
  EXPECT_EQ(p2.getName(), "None") << "Incorrect party name";
}

/**
 * @brief
 * Party and Candidate class integration tests total votes of
 * a party by totaling all the party candidates' votes
 */
TEST_F(AllTest, PartyTotalVotesTest) {
  Party p;
  Candidate* c1 = new Candidate();
  Candidate* c2 = new Candidate();

  EXPECT_EQ(p.getTotalVotes(), 0) << "Incorrect number of votes";

  p.addCandidate(c1);
  p.addCandidate(c2);

  c1->addVote();
  c1->addVote();
  c2->addVote();

  p.calculateTotalVotes();

  EXPECT_EQ(p.getNumCandidates(), 2) << "Incorrect number of candidates";
  EXPECT_EQ(c1->getNumVotes(), 2) << "Incorrect number of votes";
  EXPECT_EQ(c2->getNumVotes(), 1) << "Incorrect number of votes";
  EXPECT_EQ(p.getTotalVotes(), 3) << "Incorrect total number of votes";
}

/************** coin flip test****************/

/**
 * @brief Coin class tests constructor and fairness of flip()
 */
TEST_F(AllTest, CoinFlipTest) {
  Coin c;
  int NUM_FLIPS = 300;
  int headCount = 0;
  int tailCount = 0;

  // 20% more or less than expected
  double maxMargin = (NUM_FLIPS / 2) * 1.20;
  double minMargin = (NUM_FLIPS / 2) * 0.80;

  // coin is fair until proven otherwise
  bool fair = true;

  // record results of 300 flips
  for (int j = 0; j < NUM_FLIPS; ++j) {
    if (c.flip() == 0) {
      ++headCount;
    } else {
      ++tailCount;
    }
  }

  // check for any unusual bias
  if (((headCount > maxMargin) && (tailCount < minMargin)) ||
      ((headCount < minMargin) && (tailCount > maxMargin))) {
    std::cout << "H " << headCount << "T " << tailCount << std::endl;
    fair = false;
  }

  EXPECT_EQ(fair, true) << "Coin flip may be unfair/incorrect";
}

/************** ballotQueue test****************/

/**
 * @brief BallotQueue class tests isEmpty()
 */
TEST_F(AllTest, BallotQueueEmptyTest) {
  BallotQueue ballotQueue;
  Ballot* b1 = new Ballot();

  EXPECT_EQ(ballotQueue.isEmpty(), true) << "Incorrect number of ballots";
  ballotQueue.push(b1);
  EXPECT_EQ(ballotQueue.isEmpty(), false) << "Incorrect number of ballots";
}

/**
 * @brief BallotQueue class tests getCount() and push()
 */
TEST_F(AllTest, GetCountTest) {
  BallotQueue ballotQueue;

  Ballot* b1 = new Ballot();
  Ballot* b2 = new Ballot();
  Ballot* b3 = new Ballot();

  ballotQueue.push(b1);
  ballotQueue.push(b2);
  ballotQueue.push(b3);

  EXPECT_EQ(ballotQueue.getCount(), 3)
      << "Incorrect number of ballots in queue";
}

/**
 * @brief BallotQueue class tests pop()
 */
TEST_F(AllTest, BallotQueuePopTest) {
  BallotQueue ballotQueue;

  EXPECT_EQ(ballotQueue.getCount(), 0) << "Empty ballot";
  ASSERT_EXIT(ballotQueue.pop(), testing::KilledBySignal(SIGSEGV),
              "");  // seg fault, pop empty queue

  Ballot* b1 = new Ballot();
  Ballot* b2 = new Ballot();
  Ballot* b3 = new Ballot();

  ballotQueue.push(b1);
  ballotQueue.push(b2);
  ballotQueue.push(b3);

  EXPECT_EQ(ballotQueue.getCount(), 3) << "Incorrect number of ballots";

  EXPECT_EQ(ballotQueue.pop(), b3) << "Incorrect ballot popped";
  EXPECT_EQ(ballotQueue.pop(), b2) << "Incorrect ballot popped";
  EXPECT_EQ(ballotQueue.pop(), b1) << "Incorrect ballot popped";
}

/**
 * @brief
 * BallotQueue class tests shuffle()
 * May sometimes "fail". Means huffled executed,
 * but order remained the same. Not completely unavoidable.
 */
TEST_F(AllTest, BallotQueueShuffle) {
  BallotQueue queue;
  bool correctOrder = true;

  Ballot* b1 = new Ballot();
  Ballot* b2 = new Ballot();
  Ballot* b3 = new Ballot();

  queue.push(b1);
  queue.push(b2);
  queue.push(b3);

  if (!(queue.pop() == b3)) {
    correctOrder = false;
  }

  if (!(queue.pop() == b2)) {
    correctOrder = false;
  }

  if (!(queue.pop() == b1)) {
    correctOrder = false;
  }
  // normal order is correct

  queue.push(b1);
  queue.push(b2);
  queue.push(b3);

  queue.shuffle();

  // if all statements are true then the order is the same as normal
  // else, the order has changed (shuffled).
  if (queue.pop() == b3) {
    if (queue.pop() == b2) {
      if (queue.pop() == b1) {
        correctOrder = false;
      }
    }
  }

  EXPECT_EQ(correctOrder, true) << "Incorrect order, not shuffled";
}
