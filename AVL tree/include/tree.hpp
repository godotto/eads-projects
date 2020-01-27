#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

template <typename Key, typename Info>
class Tree
{
public:
    Tree();
    ~Tree();
    Tree(const Tree<Key, Info> &other);

    Tree<Key, Info> &operator=(const Tree<Key, Info> &other);
    bool operator==(const Tree<Key, Info> &other);
    bool operator!=(const Tree<Key, Info> &other);

    void Insert(const Key &key, const Info &info);
    void Remove(const Key &key);
    bool Clear();

    bool IsEmpty() const;
    int Size() const;
    bool Search(const Key &key) const;

    void PrintInorder() const;
    void PrintPreorder() const;
    void PrintPostorder() const;
    void PrintVisually() const;

private:
    struct Node
    {
        Key key;
        Info info;

        Node *left;
        Node *right;

        int height;

        Node(const Key &key, const Info &info);
        ~Node();
    };

    Node *root;
    int size;

    int GetBalance(Node *node) const;
    int Height(Node *node) const;
    int UpdateHeight(int leftHeight, int rightHeight) const;
    Node *SingleRotateLeft(Node *node);
    Node *SingleRotateRight(Node *node);
    Node *DoubleRotateLeft(Node *node);
    Node *DoubleRotateRight(Node *node);
    Node *GetMinimalKey(Node *node) const;

    Node *Insert(Node *parent, const Key &key, const Info &info);
    Node *Remove(Node *node, const Key &key);
    void Clear(Node *node);

    void PrintInorder(Node *node) const;
    void PrintPreorder(Node *node) const;
    void PrintPostorder(Node *node) const;
    void PrintVisually(Node *node, int indent) const;

    Node *Search(Node *node, const Key &key) const;
    void CopyTree(Node *&newTree, Node *copiedTree);
    void CompareTrees(Node *left, Node *right, bool &isEqual);
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
Tree<Key, Info>::Tree(const Tree<Key, Info> &other)
{
    root = nullptr;
    CopyTree(root, other.root);
    size = other.size;
}

template <typename Key, typename Info>
Tree<Key, Info>::Node::Node(const Key &key, const Info &info)
{
    this->key = key;
    this->info = info;
    height = 0;
    left = nullptr;
    right = nullptr;
}

template <typename Key, typename Info>
Tree<Key, Info>::Node::~Node()
{
    if (left != nullptr)
        delete left;
    if (right != nullptr)
        delete right;
}

// operators

template <typename Key, typename Info>
Tree<Key, Info> &Tree<Key, Info>::operator=(const Tree<Key, Info> &other)
{
    if (this == &other)
        return *this;

    Clear();
    CopyTree(root, other.root);

    return *this;
}

template <typename Key, typename Info>
bool Tree<Key, Info>::operator==(const Tree<Key, Info> &other)
{
    if (size != other.size)
        return false;
    else
    {
        bool isEqual = true;
        CompareTrees(root, other.root, isEqual);
        if (isEqual)
            return true;
        else
            return false;
    }
}

template <typename Key, typename Info>
bool Tree<Key, Info>::operator!=(const Tree<Key, Info> &other)
{
    return !operator==(other);
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
    root = Insert(root, key, info);
}

// removal

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::Remove(Node *node, const Key &key)
{
    if (node == nullptr)
        return nullptr;

    if (key < node->key)
        node->left = Remove(node->left, key);
    else if (key > node->key)
        node->right = Remove(node->right, key);

    else if (node->left != nullptr && node->right != nullptr)
    {
        Node *temp = GetMinimalKey(node->right);
        node->key = temp->key;
        node->info = temp->info;
        node->right = Remove(node->right, node->key);
    }
    else
    {
        Node *temp = node;
        if (node->right == nullptr)
            node = node->left;
        else
            node = node->right;

        size--;

        temp->left = nullptr;
        temp->right = nullptr;

        delete temp;
    }

    if (node == nullptr)
        return node;

    node->height = UpdateHeight(Height(node->left), Height(node->right));

    if (GetBalance(node) > 1)
    {
        if (GetBalance(node->left) >= 0)
            return SingleRotateRight(node);
        else if(GetBalance(node->left) < 0)
            return DoubleRotateRight(node);
    }
    else if (GetBalance(node) < -1)
    {
        if (GetBalance(node->right) <= 0)
            return SingleRotateLeft(node);
        else if (GetBalance(node->right) > 0)
            return DoubleRotateLeft(node);
    }

    return node;
}

template <typename Key, typename Info>
void Tree<Key, Info>::Remove(const Key &key)
{
    root = Remove(root, key);
}

template <typename Key, typename Info>
bool Tree<Key, Info>::Clear()
{
    if (IsEmpty())
        return false;
    else
    {
        delete root;
        root = nullptr;
        size = 0;
        return true;
    }
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
int Tree<Key, Info>::UpdateHeight(int leftHeight, int rightHeight) const
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

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::GetMinimalKey(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    else
    {
        if (node->left == nullptr)
            return node;
        else
            return GetMinimalKey(node->left);
    }
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

template <typename Key, typename Info>
typename Tree<Key, Info>::Node *Tree<Key, Info>::Search(Node *node, const Key &key) const
{
    if (node == nullptr || node->key == key)
        return node;
    else if (node->key < key)
        return Search(node->right, key);
    else
        return Search(node->left, key);
}

template <typename Key, typename Info>
bool Tree<Key, Info>::Search(const Key &key) const
{
    if (Search(root, key) == nullptr)
        return false;
    else
        return true;
}

template <typename Key, typename Info>
void Tree<Key, Info>::CopyTree(Node *&newTree, Node *copiedTree)
{
    if (copiedTree == nullptr)
        return;
    else
    {
        newTree = Insert(newTree, copiedTree->key, copiedTree->info);
        CopyTree(newTree, copiedTree->right);
        CopyTree(newTree, copiedTree->left);
    }
}

template <typename Key, typename Info>
void Tree<Key, Info>::CompareTrees(Node *left, Node *right, bool &isEqual)
{
    if (left == nullptr || right == nullptr || !isEqual)
        return;
    else
    {
        CompareTrees(left->left, right->left, isEqual);
        if ((left->key != right->key) || (left->info != right->info))
            isEqual = false;
        CompareTrees(left->right, right->right, isEqual);
    }
}

// printing methods

template <typename Key, typename Info>
void Tree<Key, Info>::PrintInorder(Node *node) const
{
    if (node == nullptr)
        return;
    else
    {
        PrintInorder(node->left);
        std::cout << "(" << node->key << ", " << node->info << ")\n";
        PrintInorder(node->right);
    }
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintInorder() const
{
    if (IsEmpty())
    {
        std::cout << "Tree is empty\n";
        return;
    }

    PrintInorder(root);
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintPreorder(Node *node) const
{
    if (node == nullptr)
        return;
    else
    {
        std::cout << "(" << node->key << ", " << node->info << ")\n";
        PrintPreorder(node->left);
        PrintPreorder(node->right);
    }
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintPreorder() const
{
    if (IsEmpty())
    {
        std::cout << "Tree is empty\n";
        return;
    }

    PrintPreorder(root);
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintPostorder(Node *node) const
{
    if (node == nullptr)
        return;
    else
    {
        PrintPostorder(node->left);
        PrintPostorder(node->right);
        std::cout << "(" << node->key << ", " << node->info << ")\n";
    }
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintPostorder() const
{
    if (IsEmpty())
    {
        std::cout << "Tree is empty\n";
        return;
    }
    PrintPostorder(root);
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintVisually(Node *node, int indent) const
{
    if (node == nullptr)
        return;
    else
    {
        indent += 15;

        PrintVisually(node->right, indent);

        std::cout << std::endl;
        for (int i = 15; i < indent; i++)
            std::cout << " ";
        std::cout << "(" << node->key << ", " << node->info << ")\n";
        
        PrintVisually(node->left, indent);
    }
}

template <typename Key, typename Info>
void Tree<Key, Info>::PrintVisually() const
{
    if (IsEmpty())
    {
        std::cout << "Tree is empty\n";
        return;
    }

    PrintVisually(root, 0);
}

#endif