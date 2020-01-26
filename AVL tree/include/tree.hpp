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

    int GetBalance(Node *node) const;
    int Height(Node *node) const;
    int UpdateHeight(int leftHeight, int rightHeight);
    Node *SingleRotateLeft(Node *node);
    Node *SingleRotateRight(Node *node);
    Node *DoubleRotateLeft(Node *node);
    Node *DoubleRotateRight(Node *node);

    void PrintInorder(Node *node) const;
    void PrintPreorder(Node *node) const;
    void PrintPostorder(Node *node) const;
};

// ctors and dtor

template <typename Key, typename Info>
Tree<Key, Info>::Tree()
{
    root = nullptr;
    size = 0;
}

template <typename Key, typename Info>
Tree<Key, Info>::~Tree() { Clear(); }

template <typename Key, typename Info>
Tree<Key, Info>::Node::Node(const Key &key, const Info &info)
{
    this->key = key;
    this->info = info;
    height = 1;
    left = nullptr;
    right = nullptr
}

// operations on tree

template <typename Key, typename Info>
int Tree<Key, Info>::Height(Node *node) const
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}

template <typename Key, typename Info>
int Tree<Key, Info>::GetBalance(Node *node) const
{
    if (node == nullptr)
        return 0;
    else
        return Height(node->left) - Height(node->right);
}

template <typename Key, typename Info>
int Tree<Key, Info>::UpdateHeight(int leftHeight, int rightHeight)
{
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::SingleRotateLeft(Node *node)
{
    Node *newParent;

    newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    newParent->height = UpdateHeight(newParent->left, newParent->right);
    node->height = UpdateHeight(node->left, node->right);

    return newParent;
}

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::SingleRotateRight(Node *node)
{
    Node *newParent;

    newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    newParent->height = UpdateHeight(newParent->left, newParent->right);
    node->height = UpdateHeight(node->left, node->right);

    return newParent;
}

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::DoubleRotateLeft(Node *node)
{
    node->right = SingleRotateRight(node->right);
    return SingleRotateLeft(node);
}

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::DoubleRotateRight(Node *node)
{
    node->left = SingleRotateLeft(node->left);
    return SingleRotateRight(node);
}

// other methods

template <typename Key, typename Info>
bool Tree<Key, Info>::IsEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template <typename Key, typename Info>
int Tree<Key, Info>::Size() const { return size; }

#endif