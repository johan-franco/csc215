#include "BIGINT.H"
#include "BDSCTEST.H"

main() {
    START_TESTING("BIGINTTD.C");

    TEST_CASE("Read and write bigint 1234567") {
        struct bigint bint1;
        char buffer[3 * MAX_DIGITS]; 

        set_bigint("999999", &bint1);

        set_bigint("1234567", &bi);
        ASSERT_STR(get_bigint(&bint1, buffer));
    }

    END_TESTING();
}