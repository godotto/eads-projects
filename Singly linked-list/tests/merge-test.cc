#include "../include/merge.hpp"
#include "../lib/catch.hpp"

#include <sstream>

TEST_CASE("Both of lists are empty")
{
    Sequence<int, int> s1;
    Sequence<int, int> s2;

    std::ostringstream output;
    Merge(s1, 2, 3, s2, 3, 2, 4).Print(output);
    REQUIRE(output.str().compare("empty list") == 1);
}

TEST_CASE("One of the lists is empty")
{
    Sequence<int, int> s1;
    Sequence<int, int> s2;

    s1.PushFront(31, 2);
    s1.PushFront(31, 22);
    s1.PushBack(-3, 9);
    s1.PushBack(100, 765);

    std::ostringstream output1;
    Merge(s1, 2, 3, s2, 3, 2, 4).Print(output1);
    REQUIRE(output1.str().compare("successful") == 1);

    s1.Clear();
    s2.PushFront(31, 2);
    s2.PushFront(31, 22);
    s2.PushBack(-3, 9);
    s2.PushBack(100, 765);

    std::ostringstream output2;
    Merge(s1, 2, 3, s2, 3, 2, 4).Print(output2);
    REQUIRE(output2.str().compare("successful") == 1);
}

TEST_CASE("Normal cases")
{
    Sequence<int, int> s1;
    for (int i = 1; i <= 9; i++)
        s1.PushBack(1, i);

    Sequence<int, int> s2;
    for (int i = 10; i <= 110; i += 10)
        s2.PushBack(2, i);

    std::ostringstream output;
    Merge(s1, 2, 3, s2, 1, 2, 4).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 2, 3, s2, 1, 2, 10).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, 1, 2, 4).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 2, 3, s2, 10, 2, 10).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 2, 3, s2, 0, 2, 10).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 2, 0, s2, 1, 0, 10).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, 11, 2, 10).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, 11, 2, -10).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, 11, 2, 100).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, -10, 3, s2, 11, 2, 10).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, -3, s2, 11, 2, 10).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, -2, 2, 10).Print(output);
    REQUIRE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());

    Merge(s1, 10, 3, s2, 1, -2, 10).Print(output);
    REQUIRE_FALSE(output.str().compare("successful") == 1);
    output.clear();
    output.str(std::string());
}