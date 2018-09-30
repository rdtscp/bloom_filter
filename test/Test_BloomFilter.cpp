#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"

#include "../include/bloom_filter.h"

using namespace ads;

TEST(BloomFilterTest, NormalConstruction) {
	bloom_filter bf(100, 0.01);

	ASSERT_TRUE(true);
}

TEST(BloomFilterTest, FilterLength) {
	bloom_filter bf(125000, 0.01);
	ASSERT_EQ(bf.dump().length(), 1198133);
}

TEST(BloomFilterTest, InitialisedToZeros) {
	bloom_filter bf(2, 0.091848839);
	ASSERT_EQ("0000000000", bf.dump());
}

TEST(BloomFilterTest, TestInsert) {
	bloom_filter bf(125000, 0.01);
	std::string bitsBefore = bf.dump();
	bf.insert("test");
	std::string bitsAfter  = bf.dump();

	ASSERT_NE(bitsBefore, bitsAfter);
}

TEST(BloomFilterTest, NumberHashes) {
	bloom_filter bf(125000, 0.01);

	std::string bits = bf.dump();
	ASSERT_EQ(std::count(bits.begin(), bits.end(), '1'), 0);

	bf.insert("test");

	bits = bf.dump();
	ASSERT_EQ(std::count(bits.begin(), bits.end(), '1'), 7);
}

// The fixture for testing class Project1. From google test primer.
class Test_BloomFilter : public ::testing::Test {
	protected:

		Test_BloomFilter() {
			// You can do set-up work for each test here.
		}

		// If the constructor and destructor are not enough for setting up
		// and cleaning up each test, you can define the following methods:
		virtual void SetUp() {
			// Code here will be called immediately after the constructor (right
			// before each test).
		}

		virtual void TearDown() {
			// Code here will be called immediately after each test (right
			// before the destructor).
		}

};