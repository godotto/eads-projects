#ifndef RING_HPP
#define RING_HPP

#include <string>
#include <iostream>

template <typename Key, typename Info>
class Ring
{
public:
    struct Data
    {
        Key key;
        Info info;

        Data(const Key &key, const Info &info);
    };

    class iterator;
    class const_iterator;

    Ring();
    ~Ring();
    Ring(const Ring<Key, Info> &other);

    Ring<Key, Info> &operator=(const Ring<Key, Info> &other);
    bool operator==(const Ring<Key, Info> &other);
    bool operator!=(const Ring<Key, Info> &other);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    void PushBack(const Key &key, const Info &info);
    bool Insert(const Key &key, const Info &info, const iterator &position);

    bool PopBack();
    bool Remove(const iterator &position);
    bool Clear();
    bool RemoveAllOccurances(const Key &key);

    iterator Find(const Key &key, int whichOccurance = 1);
    const_iterator Find(const Key &key, int whichOccurance = 1) const;
    bool IsEmpty() const;
    int Size() const;
    int NumberOfOccurances(const Key &key) const;
    void Print() const;
    //void Print(std::ostream &os) const;

private:
    struct Node
    {
        Data data;
        Node *next;
        Node *previous;

        Node(const Key &key, const Info &info, Node *next, Node *previous);
    };

    Node *first;
    int size;
};

// ctors and dtor

template <typename Key, typename Info>
Ring<Key, Info>::Ring()
{
    first = nullptr;
    size = 0;
}

template <typename Key, typename Info>
Ring<Key, Info>::~Ring() { Clear(); }

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info> &other)
{
    first = nullptr;
    size = 0;

    const_iterator it = other.begin();
    for (int i = 0; i < other.size; i++)
    {
        PushBack(it->key, it->info);
        ++it;
    }
}

template <typename Key, typename Info>
Ring<Key, Info>::Data::Data(const Key &key, const Info &info)
{
    this->key = key;
    this->info = info;
}

template <typename Key, typename Info>
Ring<Key, Info>::Node::Node(const Key &key, const Info &info, Node *next, Node *previous) : data(key, info)
{
    this->next = next;
    this->previous = previous;
}

// assignment operator

template <typename Key, typename Info>
Ring<Key, Info> &Ring<Key, Info>::operator=(const Ring<Key, Info> &other)
{
    if (this == &other)
        return *this;

    Clear();

    const_iterator it = other.begin();
    for (int i = 0; i < other.size; i++)
    {
        PushBack(it->key, it->info);
        ++it;
    }

    return *this;
}

// comparison operators

template <typename Key, typename Info>
bool Ring<Key, Info>::operator==(const Ring<Key, Info> &other)
{
    if (size != other.size)
        return false;
    else
    {
        iterator itLeft = this->begin();
        const_iterator itRight = other.begin();
        for (int i = 0; i < size; i++)
        {
            if (itLeft->key != itRight->key || itLeft->info != itRight->info)
                return false;
            else
            {
                ++itLeft;
                ++itRight;
            }
        }
    }

    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::operator!=(const Ring<Key, Info> &other)
{
    return !operator==(other);
}

// iterators

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin()
{
    iterator it;
    it.node = first;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end()
{
    iterator it;
    it.node = nullptr;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::begin() const
{
    const_iterator it;
    it.node = first;
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::end() const
{
    const_iterator it;
    it.node = first;
    return it;
}

// adding methods

template <typename Key, typename Info>
void Ring<Key, Info>::PushBack(const Key &key, const Info &info)
{
    Node *newNode;
    if (first == nullptr)
    {
        newNode = new Node(key, info, nullptr, nullptr);
        newNode->next = newNode;
        newNode->previous = newNode;
        first = newNode;
        size++;
    }
    else
    {
        newNode = new Node(key, info, first, first->previous);
        first->previous->next = newNode;
        first->previous = newNode;
        size++;
    }
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Insert(const Key &key, const Info &info, const iterator &position)
{
    if (position == end())
        return false;
    else if (IsEmpty())
        PushBack(key, info);
    else
    {
        Node *newNode = new Node(key, info, position.node, position.node->previous);
        position.node->previous->next = newNode;
        position.node->previous = newNode;
        size++;
    }

    return true;
}

// removing methods

template <typename Key, typename Info>
bool Ring<Key, Info>::PopBack()
{
    if (IsEmpty())
        return false;
    else if (size == 1)
    {
        delete first;
        first = nullptr;
    }
    else
    {
        Node *temp = first->previous;
        temp->previous->next = first;
        first->previous = temp->previous;
        delete temp;
    }

    size--;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Remove(const iterator &position)
{
    if (position == end() || IsEmpty())
        return false;
    else if(size == 1)
        PopBack();
    else
    {
        position.node->previous->next = position.node->next;
        position.node->next->previous = position.node->previous;

        if (first == position.node)
            first = first->next;

        delete position.node;
        size--;
    }
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::RemoveAllOccurances(const Key &key)
{
    if (IsEmpty())
        return false;
    else
    {
        int occurances = 0;
        iterator it = begin();
        iterator temp;

        for (int i = 0; i < size; i++)
        {
            if (it->key == key)
            {
                occurances++;
                temp = it;
                ++it;
                Remove(temp);
            }
            else
                ++it;
        }

        if (occurances == 0)
            return false;
        else
            return true;
    }
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Clear()
{
    if (IsEmpty())
        return false;
    else
    {
        int numberOfIterations = size;

        for (int i = 0; i < numberOfIterations; i++)
            PopBack();
    }

    return true;
}

// other methods

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::Find(const Key &key, int whichOccurance)
{
    if (IsEmpty())
        return end();
    else
    {
        iterator it = begin();
        int counter = 0;

        for (int i = 0; i < size; i++)
        {
            if (it->key == key)
            {
                counter++;
                if (counter == whichOccurance)
                    return it;
            }
            ++it;
        }
        return end();
    }
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::Find(const Key &key, int whichOccurance) const
{
    if (IsEmpty())
        return end();
    else
    {
        const_iterator it = begin();
        int counter;

        for (int i = 0; i < size; i++)
        {
            if (it->key == key)
            {
                counter++;
                if (counter == whichOccurance)
                    return it;
            }
            ++it;
        }
        return end();
    }
}

template <typename Key, typename Info>
bool Ring<Key, Info>::IsEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template <typename Key, typename Info>
int Ring<Key, Info>::Size() const { return size; }

template <typename Key, typename Info>
int Ring<Key, Info>::NumberOfOccurances(const Key &key) const
{
    const_iterator it = begin();
    int counter = 0;

    for (int i = 0; i < size; i++)
    {
        if (it->key == key)
            counter++;
        ++it;
    }

    return counter;
}

template <typename Key, typename Info>
void Ring<Key, Info>::Print() const
{
    if (IsEmpty())
    {
        std::cout << "List is empty\n";
        return;
    }
    
    const_iterator it = begin();

    for (int i = 0; i < size; i++)
    {
        std::cout << "Key: " << it->key << " Info: " << it->info << std::endl;
        ++it;
    }
}

#include "iterators.hpp"

#endif