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
    bool operator==(const Tree<Key, Info> &other) const;
    bool operator!=(const Tree<Key, Info> &other) const;

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

    Node *Insert(Node *parent, const Key &key, const Info &info);

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
    height = 0;
    left = nullptr;
    right = nullptr;
}

// insertion

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::Insert(Node *parent, const Key &key, const Info &info)
{
    if (parent == nullptr)
    {
        parent = new Node(key, info);
        size++;
    }
    else if (key < parent->key)
    {
        parent->left = Insert(parent->left, key, info);

        if (GetBalance(parent) > 1)
        {
            if (key < parent->left->key)
                parent = SingleRotateRight(parent);
            else
                parent = DoubleRotateRight(parent);
        }
    }
    else if (key > parent->key)
    {
        parent->right = Insert(parent->right, key, info);

        if (GetBalance(parent) < -1)
        {
            if (key > parent->right->key)
                parent = SingleRotateLeft(parent);
            else
                parent = DoubleRotateLeft(parent);
        }
    }
    else
    {
        parent->info = info;
        return parent;
    }

    parent->height = UpdateHeight(Height(parent->left), Height(parent->right));
    return parent;
}

template <typename Key, typename Info>
void Tree<Key, Info>::Insert(const Key &key, const Info &info)
{
    Insert(root, key, info);
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

    newParent->height = UpdateHeight(Height(newParent->left), Height(newParent->right));
    node->height = UpdateHeight(Height(node->left), Height(node->right));

    return newParent;
}

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::SingleRotateRight(Node *node)
{
    Node *newParent;

    newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    newParent->height = UpdateHeight(Height(newParent->left), Height(newParent->right));
    node->height = UpdateHeight(Height(node->left), Height(node->right));

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