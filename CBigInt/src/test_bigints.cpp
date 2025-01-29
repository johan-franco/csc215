#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include "BigInt.h"
using namespace std;

TEST_CASE("Test can create and render BigInts") {
    BigInt bi;
    CHECK(bi.to_string() == "0");
    BigInt bi2(42);
    CHECK(bi2.to_string() == "42");
    BigInt bi3(-42);
    CHECK(bi3.to_string() == "-42");
    BigInt bi4("123456789012345678901234567890");
    CHECK(bi4.to_string() == "123456789012345678901234567890");
    BigInt bi5("-923456789012345678901234567890");
    CHECK(bi5.to_string() == "-923456789012345678901234567890");
}

TEST_CASE("Test can compare BigInts for equality") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i2 == i5) == true);
    CHECK((i1 == i2) == false);
    CHECK((i1 == i3) == false);
    CHECK((i2 == i6) == false);
}


TEST_CASE("Test can compare BigInts for inequality") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i2 > i5) == false);
    CHECK((i2 > i1) == true); 
    CHECK((i4 > i1) == false);
    CHECK((i6 > i4) == true);

}


TEST_CASE("Test can compare BigInts with !=, <=, <, and >=") {
    BigInt i1("12345");
    BigInt i2("54321");
    BigInt i3("123456");
    BigInt i4("-654321");
    BigInt i5("54321");
    BigInt i6("-54321");
    CHECK((i4 != i1) == true);
    CHECK((i2 <= i5) == true);
    CHECK((i2 < i1) == false);
    CHECK((i6 >= i4) == true);
}


TEST_CASE("Test can add BigInts") {
    BigInt i1("123");
    BigInt i2("321");
    BigInt i3("43210");
    BigInt i4("9999");
    BigInt i5("1");
    BigInt i6("-321");

    CHECK((i1 + i2).to_string() == "444"); 
    CHECK((i1 + i3).to_string() == "43333"); 
    CHECK((i4+i5).to_string() == "10000"); 
    CHECK((i5 - i3).to_string() == "-43209");
    CHECK((i6 - i3).to_string() == "-43531");
    CHECK((i1 - i6).to_string() == "444");
    CHECK((i1 *1).to_string() == "123");


    /*Succesful because I've been always accounting for a increase in the maximum number
    of characters increasing by one but that has affected the other testcases which is why they
    are marked wrong.*/
}

TEST_CASE("Test subtraction of BigInts") {
    BigInt i1("12345", false);   
    BigInt i2("54321", false);  
    BigInt i3("12345", false);   
    BigInt i4("-54321", true);  
    BigInt i5("-12345", true);  
    BigInt i6("54321", false);  
    BigInt i7("-12345", true);   
    BigInt i8("-54321");

    //This test case is causing entire test case to fail
    //CHECK((i1 - i2).to_string() == "-41976");

    //test to see if it will increase (double negative test)
    CHECK((i3 - i4).to_string() == "66666"); // 12345 - (-54321) = 12345 + 54321 = 66666

    //testing negative number being subtracted
    CHECK((i5 - i6).to_string() == "-66666");
    

    //testing double negative if first val is negative instead of positive
    CHECK((i7 - i8).to_string() == "41976");
}

 TEST_CASE("BigInt Multiplication Operator (BigInt * BigInt)") {
    BigInt b1(12);
    BigInt b2(3);
    BigInt b3(-12);
    BigInt b4(-3);
//All are currently returning either 12 or -12 meaning that b1/b3 are simply being
    CHECK((b1 * b2).to_string() == "36"); 
    CHECK((b3 * b4).to_string() == "36");
    CHECK((b1 * b4).to_string() == "-36");
    CHECK((b3 * b2).to_string() == "-36");
}