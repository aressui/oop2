#include <gtest/gtest.h>
#include "../include/solution.h"
#include <sstream>

// === Тесты конструкторов ===

TEST(FiveTest, DefaultConstructor) {
    Five num;
    std::ostringstream out;
    num.print(out);
    EXPECT_EQ(out.str(), "");
}

TEST(FiveTest, FillConstructor) {
    Five num(4, 2);
    std::ostringstream out;
    num.print(out);
    EXPECT_EQ(out.str(), "2222");
}

TEST(FiveTest, InitializerListConstructor) {
    Five num{1, 2, 3, 4};
    std::ostringstream out;
    num.print(out);
    EXPECT_EQ(out.str(), "4321");
}

TEST(FiveTest, StringConstructorValid) {
    Five num("1432");
    std::ostringstream out;
    num.print(out);
    EXPECT_EQ(out.str(), "1432");
}

TEST(FiveTest, StringConstructorInvalid) {
    EXPECT_THROW(Five("195"), std::invalid_argument);
}

// === Арифметика ===

TEST(FiveTest, AddWithoutCarry) {
    Five a("13");
    Five b("11");
    Five c = a.add(b);
    std::ostringstream out;
    c.print(out);
    EXPECT_EQ(out.str(), "24");
}

TEST(FiveTest, AddWithCarry) {
    Five a("44");
    Five b("12");
    Five c = a.add(b);
    std::ostringstream out;
    c.print(out);
    EXPECT_EQ(out.str(), "111");
}

TEST(FiveTest, RemoveWithoutBorrow) {
    Five a("24");
    Five b("13");
    Five c = a.remove(b);
    std::ostringstream out;
    c.print(out);
    EXPECT_EQ(out.str(), "11");
}

TEST(FiveTest, RemoveWithBorrow) {
    Five a("200");
    Five b("11");
    Five c = a.remove(b);
    std::ostringstream out;
    c.print(out);
    EXPECT_EQ(out.str(), "134");
}

TEST(FiveTest, RemoveNegative) {
    Five a("13");
    Five b("24");
    EXPECT_THROW(a.remove(b), std::logic_error);
}
