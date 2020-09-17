/**
* @author Steve Sampson (mail@stephensampson.dev)
* @date 2020-09-17
* @brief This file contains dummy tests
*/

#include "gtest/gtest.h"

class DummyTestFixture : public ::testing::Test {

  protected:
    /// The method called before any tests in the fixture
    virtual void SetUp() {
        // this block may not be used
    }

    /// The method called after all tests in the fixture
    virtual void TearDown() {
        // this block may not be used
    }
};

TEST(DummyTestFixture, NullTestDoesNothing) {
    /* SETUP */

    /* TEST */

    /* Teardown */
    ASSERT_TRUE(true);
}