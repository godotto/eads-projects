#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "ring.hpp"

template <typename Key, typename Info>
class iterator
{
public:
    Ring<Key, Info>::Node::Data &operator*() const;
    Ring<Key, Info>::Node::Data *operator->() const;

    iterator& operator++();
    iterator operator++(int);

    iterator& operator--();
    iterator operator--(int);

    bool operator==(const iterator&) const;
    bool operator!=(const iterator&) const;

private:
    friend class Ring;
    Ring<Key, Info>::Node *node;
};

template <typename Key, typename Info>
class const_iterator
{
public:
    Ring<Key, Info>::Node::Data &operator*() const;
    Ring<Key, Info>::Node::Data *operator->() const;

    const_iterator& operator++();
    const_iterator operator++(int);

    const_iterator& operator--();
    const_iterator operator--(int);

    bool operator==(const const_iterator&) const;
    bool operator!=(const const_iterator&) const;

private:
    friend class Ring;
    const Ring<Key, Info>::Node *node;
};

#endif