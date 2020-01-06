#include "../include/split.hpp"
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

TEST_CASE("List is empty")
{
    Ring<int, int> ring1;
    Ring<int, int> ring2;
    Ring<int, int> ring3;

    Split(ring1, true, ring2, 3, 2, ring3, 2, 4);

    std::ostringstream output;
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("empty list") == 1);

    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("empty list") == 1);
}

TEST_CASE("Normal cases")
{
    Ring<int, int> ring1;
    Ring<int, int> ring2;
    Ring<int, int> ring3;

    for (int i = 1; i <= 12; i++)
        ring1.PushBack(1, i);

    Split(ring1, false, ring2, 3, 2, ring3, 2, 4);

    std::cout << "--------------------------------\n";
    std::cout << "Result 1:\n";
    std::ostringstream output;
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("successful") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("successful") == 1);
    std::cout << "--------------------------------\n";

    Split(ring1, true, ring2, 4, 2, ring3, 1, 5);

    std::cout << "\n--------------------------------\n";
    std::cout << "Result 1:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("successful") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("successful") == 1);
    std::cout << "--------------------------------\n";
}

TEST_CASE("Invalid parameters")
{
    Ring<int, int> ring1;
    Ring<int, int> ring2;
    Ring<int, int> ring3;

    for (int i = 1; i <= 12; i++)
        ring1.PushBack(1, i);

    Split(ring1, true, ring2, 4, 0, ring3, 1, 0);

    std::cout << "--------------------------------\n";
    std::cout << "Result 1:\n";
    std::ostringstream output;
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("empty list") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("empty list") == 1);
    std::cout << "--------------------------------\n";

    Split(ring1, true, ring2, 0, 2, ring3, 0, 5);

    std::cout << "\n--------------------------------\n";
    std::cout << "Result 1:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("empty list") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("empty list") == 1);
    std::cout << "--------------------------------\n";

    Split(ring1, true, ring2, -1, 2, ring3, 2, 5);

    std::cout << "\n--------------------------------\n";
    std::cout << "Result 1:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("empty list") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("successful") == 1);
    std::cout << "--------------------------------\n";

    Split(ring1, true, ring2, 3, 2, ring3, 2, -5);

    std::cout << "\n--------------------------------\n";
    std::cout << "Result 1:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring2);
    REQUIRE(output.str().compare("successful") == 1);

    std::cout << "Result 2:\n";
    output.clear();
    output.str(std::string());
    Print<int, int>(output, ring3);
    REQUIRE(output.str().compare("empty list") == 1);
    std::cout << "--------------------------------\n";
}