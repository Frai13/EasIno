
#ifndef DATACOM_TEST_H
#define DATACOM_TEST_H

#include <iostream>
#include <vector>

#include "../src/DataCom.h"
#include "gtest/gtest.h"

class DataCom_test : public testing::Test {
   protected:
    DataCom dc;

    void SetUp() override {}

    void TestSubString(std::string line, int start, int length, std::string expected_result) {
        char cstr[FULL_LENGTH];

        dc.subStr(line.c_str(), start, length, &cstr[0]);
        EXPECT_EQ(strcmp(cstr, expected_result.c_str()), 0)
            << "ERROR in:" << line << std::endl
            << "With FULL_LENGTH:" << FULL_LENGTH << " start:" << start << " length:" << length
            << std::endl
            << "Expect:" << expected_result << std::endl
            << "Result:" << cstr;
    }

    void TestSplitStr(char **array, std::vector<std::string> results, int length) {
        for (int i = results.size(); i < length; i++) {
            results.push_back("");
        }

        for (int i = 0; i < length; i++) {
            EXPECT_EQ(strcmp(array[i], results[i].c_str()), 0)
                << "ERROR in iteration:" << i << std::endl
                << "With length:" << length << std::endl
                << "Expect:" << results[i] << std::endl
                << "Result:" << array[i];
        }

        for (int i = 0; i < length; i++) {
            free(array[i]);
        }
        free(array);
    }

    void TestStrConstructor(std::string line, std::vector<std::string> results) {
        static int i = 0;
        i++;
        DataCom dc1(line.c_str());

        size_t length = dc1.array_length;

        for (int i = results.size(); i < length + 1; i++) {
            results.push_back("");
        }

        EXPECT_EQ(strcmp(dc1.operation, results[0].c_str()), 0)
            << "ERROR in:" << line << std::endl
            << "Expect:" << results[0] << std::endl
            << "Result:" << dc1.operation;
        for (int i = 1; i < length + 1; i++) {
            EXPECT_EQ(strcmp(dc1.args[i - 1], results[i].c_str()), 0)
                << "ERROR in:" << line << std::endl
                << "With iteration:" << i << std::endl
                << "Expect:" << results[i] << std::endl
                << "Result:" << dc1.args[i - 1];
        }
    }

    void TestToString(std::string line, std::string result) {
        DataCom dc1(line.c_str());

        char cstr[FULL_LENGTH];
        dc1.toString(&cstr[0]);
        EXPECT_EQ(strcmp(cstr, result.c_str()), 0) << "ERROR in:" << line << std::endl
                                                   << "Expect:" << result << std::endl
                                                   << "Result:" << cstr;
    }

    void TestSeparatorBuilder(std::string line, char separator, std::vector<std::string> results) {
        DataCom dc1;

        dc1.builder(line.c_str(), separator);

        size_t length = dc1.array_length;

        for (int i = results.size(); i < length + 1; i++) {
            results.push_back("");
        }

        EXPECT_EQ(strcmp(dc1.operation, results[0].c_str()), 0)
            << "ERROR in:" << line << std::endl
            << "With separator:" << separator << std::endl
            << "Expect:" << results[0] << std::endl
            << "Result:" << dc1.operation;
        for (int i = 1; i < length + 1; i++) {
            EXPECT_EQ(strcmp(dc1.args[i - 1], results[i].c_str()), 0)
                << "ERROR in:" << line << std::endl
                << "With separator:" << separator << " iteration:" << i << std::endl
                << "Expect:" << results[i] << std::endl
                << "Result:" << dc1.args[i - 1];
        }
    }

    template <typename T>
    void TestSetOp(T value, std::string result) {
        DataCom dc1;
        dc1.setOperation(value);
        EXPECT_EQ(strcmp(dc1.operation, result.c_str()), 0)
            << "ERROR in value:" << value << std::endl
            << "Expect:" << result << std::endl
            << "Result:" << dc1.operation;
    }

    template <typename T>
    void TestSetOp(T value, int n_decimals, std::string result) {
        DataCom dc1;
        dc1.setOperation(value, n_decimals);
        EXPECT_EQ(strcmp(dc1.operation, result.c_str()), 0)
            << "ERROR in value:" << value << std::endl
            << "With n_decimals:" << n_decimals << std::endl
            << "Expect:" << result << std::endl
            << "Result:" << dc1.operation;
    }

    template <typename T>
    void TestSetArg(int pos, T value, int expected_pos, std::string result) {
        DataCom dc1;
        dc1.setArgument(pos, value);
        EXPECT_EQ(strcmp(dc1.args[expected_pos], result.c_str()), 0)
            << "ERROR in value:" << value << std::endl
            << "With pos:" << pos << " expected_pos:" << expected_pos << std::endl
            << "Expect:" << result << std::endl
            << "Result:" << dc1.args[expected_pos];
    }

    template <typename T>
    void TestSetArg(int pos, T value, int n_decimals, int expected_pos, std::string result) {
        DataCom dc1;
        dc1.setArgument(pos, value, n_decimals);
        EXPECT_EQ(strcmp(dc1.args[expected_pos], result.c_str()), 0)
            << "ERROR in value:" << value << std::endl
            << "With pos:" << pos << " expected_pos:" << expected_pos
            << " n_decimals:" << n_decimals << std::endl
            << "Expect:" << result << std::endl
            << "Result:" << dc1.args[expected_pos];
    }
};

#endif  // DATACOM_TEST_H