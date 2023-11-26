#include "DataCom_test.h"

TEST_F(DataCom_test, IndexOfCharTests) {
    EXPECT_EQ(dc.indexOfChar(";hello;world", ';', 0), 0);
    EXPECT_EQ(dc.indexOfChar("hello;world", ';', 0), 5);
    EXPECT_EQ(dc.indexOfChar("helloworld;", ';', 0), 10);
    EXPECT_EQ(dc.indexOfChar("hello;world;", ';', 5), 5);
    EXPECT_EQ(dc.indexOfChar("hello;world", ';', -999), 5);
    EXPECT_EQ(dc.indexOfChar("hello;world", ';', -1), 5);

    EXPECT_EQ(dc.indexOfChar(";hello;world", ';', 1), 6);
    EXPECT_EQ(dc.indexOfChar("hello;world;", ';', 6), 11);

    EXPECT_EQ(dc.indexOfChar("aaAaa", 'A', 0), 2);

    EXPECT_EQ(dc.indexOfChar("hello;world", 'a', 0), -1);
    EXPECT_EQ(dc.indexOfChar("hello;world", ';', 6), -1);

    EXPECT_EQ(dc.indexOfChar("hello;world", ';', 999), -1);
    EXPECT_EQ(dc.indexOfChar("", ';', 0), -1);
    EXPECT_EQ(dc.indexOfChar("", ';', 999), -1);

    EXPECT_EQ(dc.indexOfChar("hello;w\x00orld;", 0x00, 0), 7);
    EXPECT_EQ(dc.indexOfChar("hello;w\xFForld;", 0xFF, 0), 7);
}

TEST_F(DataCom_test, IndexOfCharArrayTests) {
    EXPECT_EQ(dc.indexOfCharArray("EINO::hello;world", "EINO::", 0), 0);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO::world", "EINO::", 0), 5);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO::", "EINO::", 0), 5);
    EXPECT_EQ(dc.indexOfCharArray("EINO::", "EINO::", 0), 0);
    EXPECT_EQ(dc.indexOfCharArray("EINO::EINO::world", "EINO::", 1), 6);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO::world", "EINO::", -999), 5);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO::world", "EINO::", -1), 5);

    EXPECT_EQ(dc.indexOfCharArray("EINO:hello;world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO:world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("helloEINO:w:orld", "EINO::", 0), -1);

    EXPECT_EQ(dc.indexOfCharArray("eino::EINO::hello;world", "EINO::", 0), 6);
    EXPECT_EQ(dc.indexOfCharArray("helloeino::;world", "EINO::", 0), -1);

    EXPECT_EQ(dc.indexOfCharArray("hello;world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("INO::hello;world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray(".INO::hello;world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("E.INO::hello;world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("helloE.INO::world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("helloIENO::world", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("EINO::hello;world", "EINO::", 1), -1);
    EXPECT_EQ(dc.indexOfCharArray("helloE.INO::EINO::", "EINO::", 0), 12);

    EXPECT_EQ(dc.indexOfCharArray("EINO::hello;world", "EINO::", 999), -1);
    EXPECT_EQ(dc.indexOfCharArray("", "EINO::", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("", "EINO::", 999), -1);
    EXPECT_EQ(dc.indexOfCharArray("EINO::hello;world", "", 0), -1);
    EXPECT_EQ(dc.indexOfCharArray("EINO::hello;world", "", 999), -1);
}

TEST_F(DataCom_test, SubStrTests) {
    TestSubString("hello;world", 0, 5, "hello");
    TestSubString("hello;world", 1, 5, "ello;");
    TestSubString("hello;world", 6, 3, "wor");
    TestSubString("hello;world", 0, 11, "hello;world");
    TestSubString("hello;world", 0, 999, "hello;world");

    TestSubString(
        "hello;world;this;is;a;long;example;of;an;str;constructor;that;is;longer;than;the;max;size;"
        "allowed;hello;world;this;is;a;long;example;of;an;str;constructor;that;is;longer;than;the;"
        "max;size;allowed;",
        0, 999,
        "hello;world;this;is;a;long;example;of;an;str;constructor;that;is;longer;than;the;max;size;"
        "allowed;hello;world;this;");

    TestSubString("hello;world", -1, 5, "hello");
    TestSubString("hello;world", -999, 5, "hello");
    TestSubString("hello;world", 0, -1, "");
    TestSubString("hello;world", 0, -999, "");
    TestSubString("hello;world", -1, -1, "");
    TestSubString("hello;world", -999, -999, "");

    TestSubString("hello;world", 0, 0, "");
    TestSubString("hello;world", 2, 0, "");
    TestSubString("", 0, 3, "");
    TestSubString("", 0, 0, "");
    TestSubString("", 0, 999, "");

    char str[FULL_LENGTH];
    dc.subStr("hello;world", 999, 3, &str[0]);
    EXPECT_EQ(str[0], '\0');
    dc.subStr("hello;world", 999, 0, &str[0]);
    EXPECT_EQ(str[0], '\0');
}

TEST_F(DataCom_test, SplitStringTests) {
    TestSplitStr(dc.splitString("hello;world", ';', 10), {"hello", "world"}, 10);
    TestSplitStr(dc.splitString("hello;world", ';', 2), {"hello", "world"}, 2);
    TestSplitStr(dc.splitString("hello;verylongargumentthatsurpasses;", ';', 10),
                 {"hello", "verylongargumenttha"}, 10);
    TestSplitStr(dc.splitString("hello;verylongargumentthatsurpasses;", ';', 2),
                 {"hello", "verylongargumenttha"}, 2);
    TestSplitStr(dc.splitString("hello;world", ';', 1), {"hello"}, 1);
    TestSplitStr(dc.splitString("hello;world", ';', 0), {""}, 0);
    TestSplitStr(dc.splitString("hello;world;", ';', 10), {"hello", "world"}, 10);
    TestSplitStr(dc.splitString("hello;world;hi", ';', 10), {"hello", "world", "hi"}, 10);
    TestSplitStr(dc.splitString("hello;world", ';', -1), {""}, 0);
    TestSplitStr(dc.splitString("hello;world", ';', -999), {""}, 0);

    TestSplitStr(dc.splitString("a;b;c", ';', 10), {"a", "b", "c"}, 10);
    TestSplitStr(dc.splitString("a;b;c", ';', 3), {"a", "b", "c"}, 3);
    TestSplitStr(dc.splitString("a;b;c;", ';', 10), {"a", "b", "c"}, 10);
    TestSplitStr(dc.splitString("a;b;c;", ';', 3), {"a", "b", "c"}, 3);

    TestSplitStr(dc.splitString("hello;;world", ';', 10), {"hello", "", "world"}, 10);
    TestSplitStr(dc.splitString("hello;;;;world", ';', 10), {"hello", "", "", "", "world"}, 10);
    TestSplitStr(dc.splitString(";world;", ';', 10), {"", "world"}, 10);

    TestSplitStr(dc.splitString("hello;world;verylongargument", '!', 10), {"hello;world;verylon"},
                 10);
    TestSplitStr(dc.splitString("hello;world;verylongargument", '!', 1), {"hello;world;verylon"},
                 1);

    TestSplitStr(dc.splitString("", ';', 10), {""}, 10);
    TestSplitStr(dc.splitString("", ';', 0), {""}, 0);

    TestSplitStr(dc.splitString("hello;world", ';', 0), {""}, 0);
}

TEST_F(DataCom_test, EmptyConstructorTests) {
    DataCom dc1;

    EXPECT_NE(dc1.operation, nullptr);
    EXPECT_NE(dc1.args, nullptr);
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        EXPECT_NE(dc1.args[i], nullptr);
    }
}

TEST_F(DataCom_test, StringConstructorTests) {
    TestStrConstructor("EINO::hello;world;::END", {"hello", "world"});
    TestStrConstructor("EINO::hello;::END", {"hello"});
    TestStrConstructor("EINO::hello;;world;::END", {"hello", "", "world"});
    TestStrConstructor("EINO::::END", {});
    TestStrConstructor("EINO::hello::END", {"hello"});
    TestStrConstructor("EINO::hello;verylongargumentthatsurpasses;::END",
                       {"hello", "verylongargumenttha"});

    TestStrConstructor("EINO::hello;world;this;is;a;long;example;of;an;str;constructor;::END",
                       {"hello", "world", "this", "is", "a", "long", "example"});

    TestStrConstructor("EINO::hello;world;::EN", {});
    TestStrConstructor("INO::hello;world;::END", {});
    TestStrConstructor("EINO:hello;world;::END", {});
    TestStrConstructor("EINO::hello;world;:END", {});
    TestStrConstructor("hello;world;", {});

    TestStrConstructor("beginEINO::hello;world;::ENDend", {"hello", "world"});
    TestStrConstructor("beginEINO::hello;world;::END", {"hello", "world"});
    TestStrConstructor("EINO::hello;world;::ENDend", {"hello", "world"});
    TestStrConstructor(";EINO::hello;world;::END;", {"hello", "world"});
    TestStrConstructor(";EINO::hello;world;::END", {"hello", "world"});
    TestStrConstructor("EINO::hello;world;::END;", {"hello", "world"});
    TestStrConstructor("EINO:: hello ; world ;::END", {" hello ", " world "});

    TestStrConstructor("", {});
    TestStrConstructor("", {});
}

TEST_F(DataCom_test, CopyConstructorTests) {
    DataCom dc1("EINO::hello;world;this;is;a;long;example;of;an;str;constructor;::END");

    size_t length = dc1.array_length;

    DataCom dc2(dc1);

    EXPECT_EQ(strcmp(dc2.operation, "hello"), 0);
    std::vector<std::string> results = {"world", "this", "is", "a", "long", "example"};
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(strcmp(dc2.args[i], results[i].c_str()), 0);
    }

    memcpy(dc1.operation, "goodbye", strlen("goodbye") + 1);
    EXPECT_EQ(strcmp(dc2.operation, "hello"), 0);

    memcpy(dc1.args[1], "that", strlen("that") + 1);
    EXPECT_EQ(strcmp(dc2.args[1], "this"), 0);
}

TEST_F(DataCom_test, AssignTests) {
    DataCom dc1("EINO::hello;world;this;is;a;long;example;of;an;str;constructor;::END");

    size_t length = dc1.array_length;

    DataCom dc2;
    dc2 = dc1;

    EXPECT_EQ(strcmp(dc2.operation, "hello"), 0);
    std::vector<std::string> results = {"world", "this", "is", "a", "long", "example"};
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(strcmp(dc2.args[i], results[i].c_str()), 0);
    }

    memcpy(dc1.operation, "goodbye", strlen("goodbye") + 1);
    EXPECT_EQ(strcmp(dc2.operation, "hello"), 0);

    memcpy(dc1.args[1], "that", strlen("that") + 1);
    EXPECT_EQ(strcmp(dc2.args[1], "this"), 0);
}

TEST_F(DataCom_test, ToStringTests) {
    TestToString("EINO::hello;world;::END", "EINO::hello;world;;;;;::END");
    TestToString("EINO::hello;world;this;is;a;long;example;of;an;str;constructor;::END",
                 "EINO::hello;world;this;is;a;long;::END");
    TestToString("EINO::hello;;::END", "EINO::hello;;;;;;::END");
    TestToString("EINO::hello;;;;;;;;;;;;;;;;;;;;;;;::END", "EINO::hello;;;;;;::END");

    TestToString("", "EINO::;;;;;;::END");
    TestToString("INO::hello;world;::END", "EINO::;;;;;;::END");
}

TEST_F(DataCom_test, BuilderTests) {
    TestSeparatorBuilder("hello;world;", ';', {"hello", "world"});
    TestSeparatorBuilder("hello|world|", '|', {"hello", "world"});
    TestSeparatorBuilder("hello;", ';', {"hello"});
    TestSeparatorBuilder("hello|", '|', {"hello"});
    TestSeparatorBuilder("hello;;world;", ';', {"hello", "", "world"});
    TestSeparatorBuilder("hello||world|", '|', {"hello", "", "world"});
    TestSeparatorBuilder("", ';', {});
    TestSeparatorBuilder("", '|', {});
    TestSeparatorBuilder("hello", ';', {"hello"});
    TestSeparatorBuilder("hello", '|', {"hello"});
    TestSeparatorBuilder("hello;verylongargumentthatsurpasses;", ';',
                         {"hello", "verylongargumenttha"});
    TestSeparatorBuilder("hello|verylongargumentthatsurpasses|", '|',
                         {"hello", "verylongargumenttha"});

    TestSeparatorBuilder("hello;world;this;is;a;long;example;of;an;str;Builder;", ';',
                         {"hello", "world", "this", "is", "a", "long", "example"});
    TestSeparatorBuilder("hello|world|this|is|a|long|example|of|an|str|Builder|", '|',
                         {"hello", "world", "this", "is", "a", "long", "example"});

    TestSeparatorBuilder(" hello ; world ;", ';', {" hello ", " world "});
    TestSeparatorBuilder(" hello | world |", '|', {" hello ", " world "});

    TestSeparatorBuilder("", ';', {});
    TestSeparatorBuilder("", '|', {});
}

TEST_F(DataCom_test, SetOpArgIntTests) {
    TestSetOp<int>(0, "0");
    TestSetOp<int>(0.3, "0");
    TestSetOp<int>(1, "1");
    TestSetOp<int>(32767, "32767");
    TestSetOp<int>(-32768, "-32768");
    TestSetOp<int>(-1, "-1");
    TestSetOp<int>(-0, "0");

    TestSetArg<int>(0, 123456, 0, "123456");
    TestSetArg<int>(1, 654321, 1, "654321");
    TestSetArg<int>(4, 123456, 4, "123456");
    TestSetArg<int>(5, 654321, 4, "654321");
    TestSetArg<int>(-1, 123456, 0, "123456");

    TestSetArg<int>(0, 0, 0, "0");
    TestSetArg<int>(0, 0.3, 0, "0");
    TestSetArg<int>(0, 1, 0, "1");
    TestSetArg<int>(0, 32767, 0, "32767");
    TestSetArg<int>(0, -32768, 0, "-32768");
    TestSetArg<int>(0, -1, 0, "-1");
    TestSetArg<int>(0, -0, 0, "0");
}

TEST_F(DataCom_test, SetOpArgUnsignedIntTests) {
    TestSetOp<unsigned int>(0, "0");
    TestSetOp<unsigned int>(0.3, "0");
    TestSetOp<unsigned int>(1, "1");
    TestSetOp<unsigned int>(65535, "65535");
    TestSetOp<unsigned int>(-999, "4294966297");
    TestSetOp<unsigned int>(-1, "4294967295");
    TestSetOp<unsigned int>(-0, "0");

    TestSetArg<unsigned int>(0, 123456, 0, "123456");
    TestSetArg<unsigned int>(1, 654321, 1, "654321");
    TestSetArg<unsigned int>(4, 123456, 4, "123456");
    TestSetArg<unsigned int>(5, 654321, 4, "654321");
    TestSetArg<unsigned int>(-1, 123456, 0, "123456");

    TestSetArg<unsigned int>(0, 0, 0, "0");
    TestSetArg<unsigned int>(0, 0.3, 0, "0");
    TestSetArg<unsigned int>(0, 1, 0, "1");
    TestSetArg<unsigned int>(0, 65535, 0, "65535");
    TestSetArg<unsigned int>(0, -999, 0, "4294966297");
    TestSetArg<unsigned int>(0, -1, 0, "4294967295");
    TestSetArg<unsigned int>(0, -0, 0, "0");
}

TEST_F(DataCom_test, SetOpArgLongTests) {
    TestSetOp<long>(0, "0");
    TestSetOp<long>(0.3, "0");
    TestSetOp<long>(1, "1");
    TestSetOp<long>(2147483647, "2147483647");
    TestSetOp<long>(-2147483648, "-2147483648");
    TestSetOp<long>(-1, "-1");
    TestSetOp<long>(-0, "0");

    TestSetArg<long>(0, 123456, 0, "123456");
    TestSetArg<long>(1, 654321, 1, "654321");
    TestSetArg<long>(4, 123456, 4, "123456");
    TestSetArg<long>(5, 654321, 4, "654321");
    TestSetArg<long>(-1, 123456, 0, "123456");

    TestSetArg<long>(0, 0, 0, "0");
    TestSetArg<long>(0, 0.3, 0, "0");
    TestSetArg<long>(0, 1, 0, "1");
    TestSetArg<long>(0, 2147483647, 0, "2147483647");
    TestSetArg<long>(0, -2147483648, 0, "-2147483648");
    TestSetArg<long>(0, -1, 0, "-1");
    TestSetArg<long>(0, -0, 0, "0");
}

TEST_F(DataCom_test, SetOpArgUnsignedLongTests) {
    TestSetOp<unsigned long>(0, "0");
    TestSetOp<unsigned long>(0.3, "0");
    TestSetOp<unsigned long>(1, "1");
    TestSetOp<unsigned long>(4294967295, "4294967295");
    TestSetOp<unsigned long>(-0, "0");

    TestSetArg<unsigned long>(0, 123456, 0, "123456");
    TestSetArg<unsigned long>(1, 654321, 1, "654321");
    TestSetArg<unsigned long>(4, 123456, 4, "123456");
    TestSetArg<unsigned long>(5, 654321, 4, "654321");
    TestSetArg<unsigned long>(-1, 123456, 0, "123456");

    TestSetArg<unsigned long>(0, 0, 0, "0");
    TestSetArg<unsigned long>(0, 0.3, 0, "0");
    TestSetArg<unsigned long>(0, 1, 0, "1");
    TestSetArg<unsigned long>(0, 4294967295, 0, "4294967295");
    TestSetArg<unsigned long>(0, -0, 0, "0");
}

TEST_F(DataCom_test, SetOpArgBoolTests) {
    TestSetOp<bool>(true, "1");
    TestSetOp<bool>(false, "0");
    TestSetOp<bool>(1, "1");
    TestSetOp<bool>(2, "1");
    TestSetOp<bool>(0, "0");
    TestSetOp<bool>(-1, "1");

    TestSetArg<bool>(0, true, 0, "1");
    TestSetArg<bool>(1, false, 1, "0");
    TestSetArg<bool>(4, true, 4, "1");
    TestSetArg<bool>(5, false, 4, "0");
    TestSetArg<bool>(-1, true, 0, "1");

    TestSetArg<bool>(0, true, 0, "1");
    TestSetArg<bool>(0, false, 0, "0");
    TestSetArg<bool>(0, 1, 0, "1");
    TestSetArg<bool>(0, 2, 0, "1");
    TestSetArg<bool>(0, 0, 0, "0");
    TestSetArg<bool>(0, -1, 0, "1");
}

/*
 * No testing since using an Arduino implemented function
 *
TEST_F(DataCom_test, SetOpArgDoubleTests)
{
    TestSetOp<double>(0, 0, "0");
    TestSetOp<double>(0, 2, "0.00");
    TestSetOp<double>(99, 0, "99");
    TestSetOp<double>(99, 3, "99.000");
    TestSetOp<double>(0.1, 2, "0.10");
    TestSetOp<double>(0.125, 2, "0.12");
    TestSetOp<double>(0.125, 3, "0.125");
    TestSetOp<double>(99, 30, "99.0000000000000000");
    TestSetOp<double>(9999, 30, "9999.00000000000000");
    TestSetOp<double>(0, -1, "0.00000000000000000");
    TestSetOp<double>(99, -1, "99.0000000000000000");
    TestSetOp<double>(99, -999, "99.0000000000000000");

    TestSetArg<double>(0, 0.1, 2, 0, "0.10");
    TestSetArg<double>(1, 0.1, 2, 1, "0.10");
    TestSetArg<double>(4, 0.1, 2, 4, "0.10");
    TestSetArg<double>(5, 0.1, 2, 4, "0.10");
    TestSetArg<double>(-1, 0.1, 2, 0, "0.10");

    TestSetArg<double>(0, 0, 0, 0, "0");
    TestSetArg<double>(0, 0, 2, 0, "0.00");
    TestSetArg<double>(0, 99, 0, 0, "99");
    TestSetArg<double>(0, 99, 3, 0, "99.000");
    TestSetArg<double>(0, 0.1, 2, 0, "0.10");
    TestSetArg<double>(0, 0.125, 2, 0, "0.12");
    TestSetArg<double>(0, 0.125, 3, 0, "0.125");
    TestSetArg<double>(0, 99, 30, 0, "99.0000000000000000");
    TestSetArg<double>(0, 9999, 30, 0, "9999.00000000000000");
    TestSetArg<double>(0, 0, -1, 0, "0.00000000000000000");
    TestSetArg<double>(0, 99, -1, 0, "99.0000000000000000");
    TestSetArg<double>(0, 99, -999, 0, "99.0000000000000000");
}

TEST_F(DataCom_test, SetOpArgFloatTests)
{
    TestSetOp<float>(0, 0, "0");
    TestSetOp<float>(0, 2, "0.00");
    TestSetOp<float>(99, 0, "99");
    TestSetOp<float>(99, 3, "99.000");
    TestSetOp<float>(0.1, 2, "0.10");
    TestSetOp<float>(0.125, 2, "0.12");
    TestSetOp<float>(0.125, 3, "0.125");
    TestSetOp<float>(99, 30, "99.0000000000000000");
    TestSetOp<float>(9999, 30, "9999.00000000000000");
    TestSetOp<float>(0, -1, "0.00000000000000000");
    TestSetOp<float>(99, -1, "99.0000000000000000");
    TestSetOp<float>(99, -999, "99.0000000000000000");

    TestSetArg<float>(0, 0.1, 2, 0, "0.10");
    TestSetArg<float>(1, 0.1, 2, 1, "0.10");
    TestSetArg<float>(4, 0.1, 2, 4, "0.10");
    TestSetArg<float>(5, 0.1, 2, 4, "0.10");
    TestSetArg<float>(-1, 0.1, 2, 0, "0.10");

    TestSetArg<float>(0, 0, 0, 0, "0");
    TestSetArg<float>(0, 0, 2, 0, "0.00");
    TestSetArg<float>(0, 99, 0, 0, "99");
    TestSetArg<float>(0, 99, 3, 0, "99.000");
    TestSetArg<float>(0, 0.1, 2, 0, "0.10");
    TestSetArg<float>(0, 0.125, 2, 0, "0.12");
    TestSetArg<float>(0, 0.125, 3, 0, "0.125");
    TestSetArg<float>(0, 99, 30, 0, "99");
    TestSetArg<float>(0, 99.0, 30, 0, "99.0000000000000000");
    TestSetArg<float>(0, 9999.0, 30, 0, "9999.00000000000000");
    TestSetArg<float>(0, 0, -1, 0, "0.00000000000000000");
    TestSetArg<float>(0, 99.0, -1, 0, "99.0000000000000000");
    TestSetArg<float>(0, 99.0, -999, 0, "99.0000000000000000");
}
 */

TEST_F(DataCom_test, SetOpArgCharTests) {
    TestSetOp<char>('a', "a");
    TestSetOp<char>('9', "9");
    TestSetOp<char>(',', ",");
    TestSetOp<char>('*', "*");
    TestSetOp<char>(' ', " ");
    TestSetOp<char>('~', "~");
    TestSetOp<char>(0, "\x00");
    TestSetOp<char>(10, "\xA");
    TestSetOp<char>(255, "\xFF");

    TestSetArg<char>(0, 'a', 0, "a");
    TestSetArg<char>(1, 'a', 1, "a");
    TestSetArg<char>(4, 'a', 4, "a");
    TestSetArg<char>(5, 'a', 4, "a");
    TestSetArg<char>(-1, 'a', 0, "a");

    TestSetArg<char>(0, 'a', 0, "a");
    TestSetArg<char>(0, '9', 0, "9");
    TestSetArg<char>(0, ',', 0, ",");
    TestSetArg<char>(0, '*', 0, "*");
    TestSetArg<char>(0, ' ', 0, " ");
    TestSetArg<char>(0, '~', 0, "~");
    TestSetArg<char>(0, 0, 0, "\x00");
    TestSetArg<char>(0, 10, 0, "\xA");
    TestSetArg<char>(0, 255, 0, "\xFF");
}

TEST_F(DataCom_test, SetOpArgCharArrayTests) {
    TestSetOp<const char *>("hello", "hello");
    TestSetOp<const char *>("h3ll0+,", "h3ll0+,");
    TestSetOp<const char *>("verylongargumentthatsurpasses", "verylongargumenttha");
    TestSetOp<const char *>(" hello ", " hello ");
    TestSetOp<const char *>("", "");

    TestSetArg<const char *>(0, "hello", 0, "hello");
    TestSetArg<const char *>(1, "hello", 1, "hello");
    TestSetArg<const char *>(4, "hello", 4, "hello");
    TestSetArg<const char *>(5, "hello", 4, "hello");
    TestSetArg<const char *>(-1, "hello", 0, "hello");

    TestSetArg<const char *>(0, "hello", 0, "hello");
    TestSetArg<const char *>(0, "h3ll0+,", 0, "h3ll0+,");
    TestSetArg<const char *>(0, "verylongargumentthatsurpasses", 0, "verylongargumenttha");
    TestSetArg<const char *>(0, " hello ", 0, " hello ");
    TestSetArg<const char *>(0, "", 0, "");
}
