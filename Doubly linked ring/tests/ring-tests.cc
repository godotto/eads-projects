#include "../include/ring.hpp"
#include "../lib/catch.hpp"

#include <sstream>

template <typename Key, typename Info>
void Print(std::ostream &os, Ring<Key, Info> ring)
{
    if (ring.IsEmpty())
    {
        std::cout << "List is empty\n\n";
        os << "empty list" << std::endl;
        return;
    }

    typename Ring<Key, Info>::iterator it = ring.begin();

    for (int i = 0; i < ring.Size(); i++)
    {
        std::cout << "Key: " << it->key << " Info: " << it->info << std::endl;
        ++it;
    }

    std::cout << std::endl;
    os << "successful" << std::endl;
}

TEST_CASE("Empty list")
{
    Ring<int, int> ring1;

    SECTION("printing list")
    {
        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("empty list") == 1);
    }

    SECTION("checking if list is empty")
    {
        REQUIRE(ring1.Size() == 0);
        REQUIRE(ring1.IsEmpty());
    }

    SECTION("removing methods")
    {
        REQUIRE_FALSE(ring1.PopBack());
        REQUIRE_FALSE(ring1.Remove(ring1.begin()));
        REQUIRE_FALSE(ring1.Clear());
        REQUIRE_FALSE(ring1.RemoveAllOccurances(1));
    }

    SECTION("finding")
    {
        REQUIRE(ring1.NumberOfOccurances(1) == 0);
        try
        {
            std::cout << ring1.Find(1, 2)->key << std::endl;
        }
        catch (std::string error)
        {
            std::cerr << error << std::endl;
        }
    }
}

TEST_CASE("Filling list")
{
    Ring<int, int> ring1;

    SECTION("adding on the end")
    {
        ring1.PushBack(21, 7);
        ring1.PushBack(1, 9);
        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("adding inside")
    {
        ring1.PushBack(31, 2);
        ring1.PushBack(31, 22);
        ring1.PushBack(-3, 9);
        ring1.PushBack(100, 765);

        typename Ring<int, int>::iterator it = ring1.begin();
        it++;

        REQUIRE(ring1.Insert(68, 419, it));
        REQUIRE_FALSE(ring1.Insert(20, 36, ring1.end()));

        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("successful") == 1);
    }
}

TEST_CASE("Removing from list")
{
    Ring<int, int> ring1;
    ring1.PushBack(31, 2);
    ring1.PushBack(31, 22);
    ring1.PushBack(-3, 9);
    ring1.PushBack(100, 765);

    SECTION("removing from the end")
    {
        REQUIRE(ring1.PopBack());
        REQUIRE(ring1.PopBack());

        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("successful") == 1);

        REQUIRE(ring1.PopBack());
        REQUIRE(ring1.PopBack());
    }

    SECTION("removing selected element")
    {
        typename Ring<int, int>::iterator it = ring1.begin();
        it++;

        REQUIRE(ring1.Remove(it));
        REQUIRE_FALSE(ring1.Remove(ring1.end()));

        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("successful") == 1);
    }

    SECTION("removing all elements")
    {
        REQUIRE(ring1.Clear());
        REQUIRE(ring1.IsEmpty());
    }

    SECTION("removing all elements with the chosen key")
    {
        REQUIRE(ring1.RemoveAllOccurances(31));
        REQUIRE_FALSE(ring1.RemoveAllOccurances(60));

        std::ostringstream output;
        Print<int, int>(output, ring1);
        REQUIRE(output.str().compare("successful") == 1);
    }
}

TEST_CASE("Comparison operators")
{
    Ring<int, int> ring1;
    ring1.PushBack(31, 2);
    ring1.PushBack(31, 22);
    ring1.PushBack(-3, 9);
    ring1.PushBack(100, 765);

    Ring<int, int> ring2;
    ring2.PushBack(31, 2);
    ring2.PushBack(31, 22);
    ring2.PushBack(-3, 9);
    ring2.PushBack(100, 765);

    SECTION("equality operator")
    {
        REQUIRE((ring1 == ring2) == true);
        ring2.PopBack();
        REQUIRE((ring1 == ring2) == false);
    }

    SECTION("inequality operator")
    {
        REQUIRE((ring1 != ring2) == false);
        ring2.PopBack();
        REQUIRE((ring1 != ring2) == true);
    }
}

TEST_CASE("Copying list")
{
    SECTION("copy constructor")
    {
        Ring<int, int> *ring1 = new Ring<int, int>;
        ring1->PushBack(31, 2);
        ring1->PushBack(31, 22);
        ring1->PushBack(-3, 9);
        ring1->PushBack(100, 765);

        Ring<int, int> *ring2 = new Ring<int, int>(*ring1);
        REQUIRE((*ring1 == *ring2) == true);

        delete ring1;

        std::ostringstream output;
        Print<int, int>(output, *ring2);
        REQUIRE(output.str().compare("successful") == 1);

        delete ring2;
    }

    SECTION("assigment operator")
    {
        Ring<int, int> *ring1 = new Ring<int, int>;
        ring1->PushBack(31, 2);
        ring1->PushBack(31, 22);
        ring1->PushBack(-3, 9);
        ring1->PushBack(100, 765);

        Ring<int, int> *ring2 = new Ring<int, int>;
        *ring2 = *ring1;
        REQUIRE((*ring1 == *ring2) == true);

        delete ring1;

        std::ostringstream output;
        Print<int, int>(output, *ring2);
        REQUIRE(output.str().compare("successful") == 1);

        delete ring2;
    }
}

TEST_CASE("Other methods")
{
    Ring<int, int> ring1;
    ring1.PushBack(31, 2);
    ring1.PushBack(31, 22);
    ring1.PushBack(-3, 9);
    ring1.PushBack(100, 765);

    SECTION("size method")
    {
        REQUIRE(ring1.Size() == 4);
    }

    SECTION("find method")
    {
        typename Ring<int, int>::iterator it;
        it = ring1.Find(31, 2);
        REQUIRE(it->info == 22);

        it = ring1.Find(100);
        REQUIRE(it->info == 765);

        it = ring1.Find(31, 3);
        try
        {
            std::cout << it->key << std::endl;
        }
        catch (std::string error)
        {
            std::cerr << error << std::endl;
        }

        it = ring1.Find(1);
        try
        {
            std::cout << it->key << std::endl;
        }
        catch (std::string error)
        {
            std::cerr << error << std::endl;
        }
    }

    SECTION("checking number of key occurances")
    {
        REQUIRE(ring1.NumberOfOccurances(31) == 2);
        REQUIRE(ring1.NumberOfOccurances(1) == 0);
    }
}