#include "../include/tree.hpp"
#include "../lib/catch.hpp"

TEST_CASE("Empty tree")
{
    Tree<int, int> tree1;

    SECTION("printing tree")
    {
        tree1.PrintInorder();
        tree1.PrintPreorder();
        tree1.PrintPostorder();
        tree1.PrintVisually();
    }

    SECTION("checking if list is empty")
    {
        REQUIRE(tree1.Size() == 0);
        REQUIRE(tree1.IsEmpty());
    }

    SECTION("removing methods")
    {
        REQUIRE_NOTHROW(tree1.Remove(1));
        REQUIRE_FALSE(tree1.Clear());
    }

    SECTION("searching")
    {
        REQUIRE_FALSE(tree1.Search(2));
    }
}

TEST_CASE("Filling tree and printing")
{
    Tree<int, int> tree1;

    tree1.Insert(3, 1);
    tree1.Insert(-1, 1);
    tree1.Insert(7, 1);
    tree1.Insert(10, 1);
    tree1.Insert(-12, 1);
    tree1.Insert(9, 1);
    tree1.Insert(11, 1);

    std::cout << std::endl;
    tree1.PrintInorder();
    std::cout << std::endl;
    tree1.PrintPreorder();
    std::cout << std::endl;
    tree1.PrintPostorder();
    std::cout << std::endl;
    tree1.PrintVisually();
    std::cout << std::endl;
}
