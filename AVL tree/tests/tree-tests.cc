#include "../include/tree.hpp"
#include "../lib/catch.hpp"

TEST_CASE("Empty tree")
{
    Tree<int, int> tree1;

    SECTION("printing tree")
    {
        std::cout << "----1----\n";
        tree1.PrintInorder();
        std::cout << "----2----\n";
        tree1.PrintPreorder();
        std::cout << "----3----\n";
        tree1.PrintPostorder();
        std::cout << "----4----\n";
        tree1.PrintVisually();
    }

    SECTION("checking if tree is empty")
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
    std::cout << "----5----\n";
    tree1.PrintInorder();
    std::cout << std::endl;
    std::cout << "----6----\n";
    tree1.PrintPreorder();
    std::cout << std::endl;
    std::cout << "----7----\n";
    tree1.PrintPostorder();
    std::cout << std::endl;
    std::cout << "----8----\n";
    tree1.PrintVisually();
    std::cout << std::endl;
}

TEST_CASE("Removing from tree")
{
    Tree<int, int> tree1;

    tree1.Insert(3, 1);
    tree1.Insert(-1, 1);
    tree1.Insert(7, 1);
    tree1.Insert(10, 1);
    tree1.Insert(-12, 1);
    tree1.Insert(9, 1);
    tree1.Insert(11, 1);

    SECTION("removing chosen elements")
    {
        std::cout << std::endl;
        std::cout << "----9----\n";
        tree1.PrintInorder();
        tree1.Remove(10);
        std::cout << std::endl;
        std::cout << "----10----\n";
        tree1.PrintInorder();
        tree1.Remove(3);
        std::cout << std::endl;
        std::cout << "----11----\n";
        tree1.PrintInorder();
        tree1.Remove(100);
        std::cout << std::endl;
        std::cout << "----12----\n";
        tree1.PrintInorder();
    }

    SECTION("removing all elements")
    {
        REQUIRE(tree1.Clear());
        std::cout << "----13----\n";
        tree1.PrintInorder();
    }
}

TEST_CASE("Comparison operators")
{
    Tree<int, int> tree1;

    tree1.Insert(3, 1);
    tree1.Insert(-1, 1);
    tree1.Insert(7, 1);
    tree1.Insert(10, 1);
    tree1.Insert(-12, 1);
    tree1.Insert(9, 1);
    tree1.Insert(11, 1);

    Tree<int, int> tree2;

    tree2.Insert(3, 1);
    tree2.Insert(-1, 1);
    tree2.Insert(7, 1);
    tree2.Insert(10, 1);
    tree2.Insert(-12, 1);
    tree2.Insert(9, 1);
    tree2.Insert(11, 1);

    REQUIRE((tree1 == tree2));
    REQUIRE_FALSE((tree1 != tree2));

    tree2.Insert(3, 2);
    REQUIRE((tree1 != tree2));
    REQUIRE_FALSE((tree1 == tree2));
}

TEST_CASE("Copying tree")
{
    SECTION("copy constructor")
    {
        Tree<int, int> *tree1 = new Tree<int, int>;
        tree1->Insert(3, 1);
        tree1->Insert(-1, 1);
        tree1->Insert(7, 1);
        tree1->Insert(10, 1);
        tree1->Insert(-12, 1);
        tree1->Insert(9, 1);
        tree1->Insert(11, 1);

        Tree<int, int> *tree2 = new Tree<int, int>(*tree1);
        REQUIRE((*tree1 == *tree2) == true);

        delete tree1;
        std::cout << std::endl;
        std::cout << "----14----\n";
        tree2->PrintInorder();
        delete tree2;
    }

    SECTION("assigment operator")
    {
        Tree<int, int> *tree1 = new Tree<int, int>;
        tree1->Insert(3, 1);
        tree1->Insert(-1, 1);
        tree1->Insert(7, 1);
        tree1->Insert(10, 1);
        tree1->Insert(-12, 1);
        tree1->Insert(9, 1);
        tree1->Insert(11, 1);

        Tree<int, int> *tree2 = new Tree<int, int>;
        *tree2 = *tree1;
        REQUIRE((*tree1 == *tree2) == true);

        delete tree1;
        std::cout << std::endl;
        std::cout << "----15----\n";
        tree2->PrintInorder();
        delete tree2;
    }
}

TEST_CASE("Other methods")
{
    Tree<int, int> tree1;

    tree1.Insert(3, 1);
    tree1.Insert(-1, 1);
    tree1.Insert(7, 1);
    tree1.Insert(10, 1);
    tree1.Insert(-12, 1);
    tree1.Insert(9, 1);
    tree1.Insert(11, 1);

    SECTION("size method")
    {
        REQUIRE(tree1.Size() == 7);
    }

    SECTION("checking if tree is empty")
    {
        REQUIRE_FALSE(tree1.IsEmpty());
        tree1.Clear();
        REQUIRE(tree1.IsEmpty());
    }

    SECTION("searching")
    {
        REQUIRE(tree1.Search(3));
        REQUIRE(tree1.Search(10));
        REQUIRE_FALSE(tree1.Search(-3));
        REQUIRE_FALSE(tree1.Search(21));

        tree1.Remove(3);
        REQUIRE_FALSE(tree1.Search(3));
    }
}