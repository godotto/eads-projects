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

    void PushFront(const Key &key, const Info &info);
    void PushBack(const Key &key, const Info &info);
    bool Insert(const Key &key, const Info &info, const iterator &position);

    bool PopFront();
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
Ring<Key, Info>::~Ring()
{
}

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

// other methods

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
void Ring<Key, Info>::Print() const
{
    const_iterator it = begin();

    for (int i = 0; i < size; i++)
    {
        std::cout << "Key: " << it->key << " Info: " << it->info << std::endl;
        ++it;
    }
}

#include "iterators.hpp"

#endif