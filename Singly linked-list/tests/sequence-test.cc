#include "../include/sequence.hpp"
#include "../lib/catch.hpp"

#include <sstream>

TEST_CASE("Empty list")
{
    Sequence<int, int> s;

    SECTION("printing list")
    {
        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("empty list") == 1);
    }

    SECTION("checking if list is empty")
    {
        REQUIRE(s.Size() == 0);
        REQUIRE(s.IsEmpty());
    }

    SECTION("removing methods")
    {
        REQUIRE_FALSE(s.PopBack());
        REQUIRE_FALSE(s.PopFront());
        REQUIRE_FALSE(s.Remove(1, 2));
        REQUIRE_FALSE(s.Clear());
        REQUIRE_FALSE(s.RemoveAllOccurances(1));
    }

    SECTION("finding")
    {
        REQUIRE(s.NumberOfOccurances(1) == 0);
        REQUIRE_FALSE(s.Find(1, 2));
    }
}

TEST_CASE("Filling list")
{
    Sequence<int, int> s;

    SECTION("adding on the beginning")
    {
        s.PushFront(1, 2);
        s.PushFront(3, 1);
        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("adding on the end")
    {
        s.PushBack(21, 7);
        s.PushBack(1, 9);
        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("adding inside")
    {
        s.PushFront(31, 2);
        s.PushFront(31, 22);
        s.PushBack(-3, 9);
        s.PushBack(100, 765);

        REQUIRE(s.Insert(68, 419, 31, 2));
        REQUIRE_FALSE(s.Insert(20, 36, 31, 3));
        REQUIRE_FALSE(s.Insert(17, 52, 2, 1));

        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }
}

TEST_CASE("Removing from list")
{
    Sequence<int, int> s;
    s.PushFront(31, 2);
    s.PushFront(31, 22);
    s.PushBack(-3, 9);
    s.PushBack(100, 765);

    SECTION("removing from the beginning")
    {
        REQUIRE(s.PopFront());
        REQUIRE(s.PopFront());

        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("removing from the end")
    {
        REQUIRE(s.PopBack());
        REQUIRE(s.PopBack());

        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);

        REQUIRE(s.PopBack());
        REQUIRE(s.PopBack());
    }

    SECTION("removing selected element")
    {
        REQUIRE(s.Remove(31, 2));
        REQUIRE_FALSE(s.Remove(31, 3));
        REQUIRE_FALSE(s.Remove(2, 1));

        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("removing all elements")
    {
        REQUIRE(s.Clear());
        REQUIRE(s.IsEmpty());
    }

    SECTION("removing all elements with the chosen key")
    {
        REQUIRE(s.RemoveAllOccurances(31));
        REQUIRE_FALSE(s.RemoveAllOccurances(60));

        std::ostringstream output;
        s.Print(output);
        REQUIRE(output.str().compare("successful") == 1);
    }
}

TEST_CASE("Comparison operators")
{
    Sequence<int, int> s1;
    s1.PushFront(31, 2);
    s1.PushFront(31, 22);
    s1.PushBack(-3, 9);
    s1.PushBack(100, 765);

    Sequence<int, int> s2;
    s2.PushFront(31, 2);
    s2.PushFront(31, 22);
    s2.PushBack(-3, 9);
    s2.PushBack(100, 765);

    SECTION("equality operator")
    {
        REQUIRE((s1 == s2) == true);
        s2.PopFront();
        REQUIRE((s1 == s2) == false);
    }

    SECTION("inequality operator")
    {
        REQUIRE((s1 != s2) == false);
        s2.PopFront();
        REQUIRE((s1 != s2) == true);
    }
}

TEST_CASE("Copying list")
{
    SECTION("copy constructor")
    {
        Sequence<int, int> *s1 = new Sequence<int, int>;
        s1->PushFront(31, 2);
        s1->PushFront(31, 22);
        s1->PushBack(-3, 9);
        s1->PushBack(100, 765);

        Sequence<int, int> *s2 = new Sequence<int, int>(*s1);
        REQUIRE((*s1 == *s2) == true);

        delete s1;

        std::ostringstream output;
        (*s2).Print(output);
        REQUIRE(output.str().compare("successful") == 1);

        delete s2;
    }

    SECTION("assigment operator")
    {
        Sequence<int, int> *s1 = new Sequence<int, int>;
        s1->PushFront(31, 2);
        s1->PushFront(31, 22);
        s1->PushBack(-3, 9);
        s1->PushBack(100, 765);

        Sequence<int, int> *s2 = new Sequence<int, int>;
        *s2 = *s1;
        REQUIRE((*s1 == *s2) == true);

        delete s1;

        std::ostringstream output;
        (*s2).Print(output);
        REQUIRE(output.str().compare("successful") == 1);

        delete s2;
    }
}

TEST_CASE("Other methods")
{
    Sequence<int, int> s;
    s.PushFront(31, 2);
    s.PushFront(31, 22);
    s.PushBack(-3, 9);
    s.PushBack(100, 765);

    SECTION("size method")
    {
        REQUIRE(s.Size() == 4);
    }

    SECTION("find method")
    {
        REQUIRE(s.Find(31, 2));
        REQUIRE(s.Find(100));
        REQUIRE_FALSE(s.Find(31, 3));
        REQUIRE_FALSE(s.Find(1));
    }

    SECTION("checking number of key occurances")
    {
        REQUIRE(s.NumberOfOccurances(31) == 2);
        REQUIRE(s.NumberOfOccurances(1) == 0);
    }
}