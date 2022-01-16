// Copyright Davydov Nikolay 2021
#include <gtest/gtest.h>
#include <string>

#include "optional.hpp"

using namespace my_optional;


TEST(Optional, Constructors) {
    int int_obj = 10;

    optional<int> optional_int0;
    optional<int> optional_int1(std::nullopt);
    optional<int> optional_int2(10);
    optional<int> optional_int3(optional_int2);
    optional<int> optional_int4(std::move(optional_int2));
    optional<int> optional_int5(int_obj);

    EXPECT_TRUE(optional_int3.operator bool());
    EXPECT_TRUE(optional_int4.operator bool());
    EXPECT_TRUE(optional_int5.operator bool());

    EXPECT_FALSE(optional_int0.operator bool());
    EXPECT_FALSE(optional_int1.operator bool());
}

TEST(Optional, Equal) {
    std::string str = "qwerty";

    optional<std::string> optional_str6("Hello");
    optional<std::string> optional_str7;
    optional<std::string> optional_str8;
    optional<std::string> optional_str9;
    optional<std::string> optional_str10;

    EXPECT_TRUE(optional_str6.operator bool());
    EXPECT_FALSE(optional_str7.operator bool());
    EXPECT_FALSE(optional_str8.operator bool());
    EXPECT_FALSE(optional_str9.operator bool());
    EXPECT_FALSE(optional_str10.operator bool());

    optional_str7 = optional_str6;
    EXPECT_TRUE(optional_str7.operator bool());

    optional_str8 = std::move(optional_str7);
    EXPECT_TRUE(optional_str8.operator bool());

    optional_str9 = "World";
    EXPECT_TRUE(optional_str9.operator bool());

    optional_str10 = str;
    EXPECT_TRUE(optional_str10.operator bool());
}

TEST(Optional, Access) {
    optional<std::string> optional_str1("Hello");
    EXPECT_EQ(*optional_str1, "Hello");

    optional<std::string> optional_str2;
    optional_str2 = optional_str1;
    EXPECT_EQ(*optional_str2, "Hello");

    optional_str1 = "World";
    EXPECT_EQ(*optional_str1, "World");
    EXPECT_EQ(optional_str1->size(), 5);

    optional<std::string> optional_str3(optional_str1);
    EXPECT_EQ(*optional_str3, "World");
    EXPECT_EQ(optional_str3->size(), 5);

    optional<int> optional_int1 (100);
    EXPECT_EQ(*optional_int1, 100);

    optional<int> optional_int2 (optional_int1);
    EXPECT_EQ(*optional_int2, 100);

    optional<int> optional_int3;
    optional_int3 = 20;
    EXPECT_EQ(*optional_int3, 20);
}

TEST(Optional, Value) {
    optional<std::string> optional_str1("Hello");
    EXPECT_EQ(optional_str1.value(), "Hello");
    EXPECT_NO_THROW(optional_str1.value());

    optional<std::string> optional_str2;
    EXPECT_THROW(optional_str2.value(), std::runtime_error);

    optional_str2 = optional_str1;
    EXPECT_EQ(optional_str2.value(), "Hello");
    EXPECT_NO_THROW(optional_str2.value());

    optional_str1 = "World";
    EXPECT_EQ(optional_str1.value(), "World");
    EXPECT_NO_THROW(optional_str1.value());

    optional<std::string> optional_str3(optional_str1);
    EXPECT_EQ(optional_str3.value(), "World");
    EXPECT_NO_THROW(optional_str3.value());

    optional<int> optional_int1 (100);
    EXPECT_EQ(optional_int1.value(), 100);

    optional<int> optional_int2 (optional_int1);
    EXPECT_EQ(optional_int2.value(), 100);

    optional<int> optional_int3;
    EXPECT_THROW(optional_int3.value(), std::runtime_error);

    optional_int3 = 20;
    EXPECT_EQ(optional_int3.value(), 20);
}

TEST(Optional, Value_or) {
    optional<std::string> optional_str1("Hello");
    EXPECT_EQ(optional_str1.value_or("qwerty"), "Hello");

    optional<std::string> optional_str2;
    EXPECT_EQ(optional_str2.value_or("qwerty"), "qwerty");

    optional_str2 = "World";
    EXPECT_EQ(optional_str2.value_or("qwerty"), "World");
}

