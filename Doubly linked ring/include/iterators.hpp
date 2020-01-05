#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "ring.hpp"

template <typename Key, typename Info>
class iterator
{
public:
    iterator();

    typename Ring<Key, Info>::Data &operator*() const;
    typename Ring<Key, Info>::Data *operator->() const;

    iterator &operator++();
    iterator operator++(int);

    iterator &operator--();
    iterator operator--(int);

    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;

private:
    friend class Ring;
    Ring<Key, Info>::Node *node;
};

template <typename Key, typename Info>
class const_iterator
{
public:
    const_iterator();

    typename Ring<Key, Info>::Data &operator*() const;
    typename Ring<Key, Info>::Data *operator->() const;

    const_iterator &operator++();
    const_iterator operator++(int);

    const_iterator &operator--();
    const_iterator operator--(int);

    bool operator==(const const_iterator &) const;
    bool operator!=(const const_iterator &) const;

private:
    friend class Ring;
    const Ring<Key, Info>::Node *node;
};

// iterator

// ctor
template <typename Key, typename Info>
iterator<Key, Info>::iterator() { node = nullptr; }

// operators * and ->
template <typename Key, typename Info>
typename Ring<Key, Info>::Data &iterator<Key, Info>::operator*() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator *");
    else
        return node->data;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Data *iterator<Key, Info>::operator->() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator ->");
    else
        return &(node->data);
}

// operators ++
template <typename Key, typename Info>
iterator<Key, Info> &iterator<Key, Info>::operator++()
{
    if (node == nullptr)
        throw std::string("Cannot use operator ++");
    else
    {
        node = node->next;
        return *this;
    }
}

template <typename Key, typename Info>
iterator<Key, Info> iterator<Key, Info>::operator++(int)
{
    if (node == nullptr)
        throw std::string("Cannot use operator ++");
    else
    {
        iterator old = *this;
        node = node->next;
        return old;
    }
}

// operators --
template <typename Key, typename Info>
iterator<Key, Info> &iterator<Key, Info>::operator--()
{
    if (node == nullptr)
        throw std::string("Cannot use operator --");
    else
    {
        node = node->previous;
        return *this;
    }
}

template <typename Key, typename Info>
iterator<Key, Info> iterator<Key, Info>::operator--(int)
{
    if (node == nullptr)
        throw std::string("Cannot use operator --");
    else
    {
        iterator old = *this;
        node = node->previous;
        return old;
    }
}

// comparison operators
template <typename Key, typename Info>
bool iterator<Key, Info>::operator==(const iterator &other) const { return node == other.node }

template <typename Key, typename Info>
bool iterator<Key, Info>::operator!=(const iterator &other) const { return node == other.node }


// const_iterator

// ctor
template <typename Key, typename Info>
const_iterator<Key, Info>::const_iterator() { node = nullptr; }

// operators * and ->
template <typename Key, typename Info>
typename Ring<Key, Info>::Data &const_iterator<Key, Info>::operator*() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator *");
    else
        return node->data;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Data *const_iterator<Key, Info>::operator->() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator ->");
    else
        return &(node->data);
}

// operators ++
template <typename Key, typename Info>
const_iterator<Key, Info> &const_iterator<Key, Info>::operator++()
{
    if (node == nullptr)
        throw std::string("Cannot use operator ++");
    else
    {
        node = node->next;
        return *this;
    }
}

template <typename Key, typename Info>
const_iterator<Key, Info> const_iterator<Key, Info>::operator++(int)
{
    if (node == nullptr)
        throw std::string("Cannot use operator ++");
    else
    {
        const_iterator old = *this;
        node = node->next;
        return old;
    }
}

// operators --
template <typename Key, typename Info>
const_iterator<Key, Info> &const_iterator<Key, Info>::operator--()
{
    if (node == nullptr)
        throw std::string("Cannot use operator --");
    else
    {
        node = node->previous;
        return *this;
    }
}

template <typename Key, typename Info>
const_iterator<Key, Info> const_iterator<Key, Info>::operator--(int)
{
    if (node == nullptr)
        throw std::string("Cannot use operator --");
    else
    {
        const_iterator old = *this;
        node = node->previous;
        return old;
    }
}

// comparison operators
template <typename Key, typename Info>
bool const_iterator<Key, Info>::operator==(const const_iterator &other) const { return node == other.node }

template <typename Key, typename Info>
bool const_iterator<Key, Info>::operator!=(const const_iterator &other) const { return node == other.node }

#endif