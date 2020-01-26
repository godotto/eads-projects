#ifndef TREE_HPP
#define TREE_HPP

template <typename Key, typename Info>
class Tree
{
public:
    Tree();
    ~Tree();
    Tree(const Tree<Key, Info> &other);

    Tree<Key, Info> &operator=(const Tree<Key, Info> &other);
    bool operator operator==(const Tree<Key, Info> &other) const;
    bool operator operator!=(const Tree<Key, Info> &other) const;

    void Insert(const Key &key, const Info &info);
    bool Remove(const Key &key);
    bool Clear();

    bool IsEmpty() const;
    int Size() const;
    bool Search(const Key &key, const Info &info) const;

    void PrintInorder() const;
    void PrintPreorder() const;
    void PrintPostorder() const;

private:
    struct Node
    {
        Key key;
        Info info;

        Node *left;
        Node *right;

        int height;

        Node(const Key &key, const Info &info);
    };

    Node *root;
    int size;

    Node *RotateLeft(Node *node);
    Node *RotateRight(Node *node);
    int GetBalance(Node *node) const;

    void PrintInorder(Node *node) const;
    void PrintPreorder(Node *node) const;
    void PrintPostorder(Node *node) const;
};

#endif