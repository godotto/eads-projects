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
