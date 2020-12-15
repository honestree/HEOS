#include "Polynomial.hpp"
#include <cstdio>
  
//using googletest
#include <gtest/gtest.h>

TEST(Polynomial, Initial) {
    // Init
    Polynomial test( std::vector<double>{ 1 , 1 } );
    ASSERT_EQ( test(1) , 1 );

    // Copy assignment
    Polynomial test2;
    test2 = test;
    EXPECT_TRUE( test2 == test );
}

TEST(Polynomial, Operator ) {
    Polynomial test_a( std::vector<double>{ -1 , 1 } );
    Polynomial test_b( std::vector<double>{ 1 , 1 } );
    Polynomial ans;
    Polynomial expect( std::vector<double>{ 0 , 2 });

    ans = test_a + test_b;

    EXPECT_TRUE( ans == expect );

    ans = test_b * test_a;
    expect = Polynomial( std::vector<double>{ -1 , 0 , 1 });

    EXPECT_TRUE( ans == expect );


}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
