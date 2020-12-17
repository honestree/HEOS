#include <cstdio>
#include <cmath>

// Include homehade hpp
#include "Polynomial.hpp"
#include "WaveFunc.hpp"

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

    ans = ans - test_a * 9;
    expect = Polynomial( std::vector<double>{ 9, -7 } );
    EXPECT_TRUE( ans == expect );

    ans = ans / 2;
    expect = Polynomial( std::vector<double>{ 4.5, -3.5 } );
    EXPECT_TRUE( ans == expect );


    ans = test_b * test_a;
    expect = Polynomial( std::vector<double>{ -1 , 0 , 1 });
    EXPECT_TRUE( ans == expect );

}

TEST(Polynomial, value ) {

    Polynomial test( std::vector<double>{ -1 , 1 } );

    test = test * test;
    EXPECT_EQ(test.value( 10 ), 81);

    test = test * Polynomial( std::vector<double>{ 1 , 1 , 1 } );
    EXPECT_EQ(test.value( 10 ), 8991 );

}

TEST( Polynomial, differential ){

    Polynomial test( std::vector<double>{ -1 , 1 } );

    test = test * test;

    EXPECT_EQ( test.value( 3 ), 4 );

    test.differential();

    EXPECT_EQ( test.value( 8 ), 14 );

}

TEST( WaveFunc, Laguerre ){

    WaveFunc calcul( 1, 0, 0 );
    Polynomial ans;
    Polynomial expect;

    expect = Polynomial( std::vector<double>{ 1, -1 } );
    ans = calcul.Laguerre( 1 );
    EXPECT_TRUE( ans == expect );

    expect = Polynomial( std::vector<double>{ 720, -4320, 5400, -2400, 450, -36, 1 } );
    expect = expect / 720;
    ans = calcul.Laguerre( 6 );
    EXPECT_TRUE( ans == expect );

}

TEST( WaveFunc, RBF ){

    WaveFunc WF1( 1, 0, 0 );
    WaveFunc WF2( 2 ,1, 0 );
    WaveFunc WF3( 3 ,2, 0 );
    double ans;
    double expect;
    double t_rad = 1e-9;

    ans = WF1.RBF( t_rad );
    expect = 2 * exp( -1 * t_rad / BohrRad ) / pow(BohrRad,(1.5));
    EXPECT_TRUE( abs( ans - expect ) < 1e-10  );

    ans = WF2.RBF( t_rad );
    expect = pow( 24, -0.5 ) * pow(BohrRad,-1.5 ) * ( t_rad/BohrRad ) * exp( -0.5 * t_rad / BohrRad );
    EXPECT_TRUE( abs( ans - expect ) < 1e-10  );

    ans = WF3.RBF( t_rad );
    expect = 4/(81 * pow(30,0.5)) * pow(BohrRad,-1.5) * pow( t_rad/BohrRad , 2 )*exp( -1 * t_rad/3/BohrRad ) ;
    EXPECT_TRUE( abs( ans - expect ) < 1e-10  );

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
