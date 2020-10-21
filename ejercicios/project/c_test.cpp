#define CATCH_CONFIG_MAIN
#include"catch2/catch.hpp"
#include"c_test.hpp"

TEST_CASE(){
    REQUIRE(test1()==1);
    REQUIRE(test2()==1);
    REQUIRE(test3()==1);
    REQUIRE(test4()==1);
}
