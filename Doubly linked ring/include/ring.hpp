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



#include "iterators.hpp"

#endif