#ifndef ITERATORS_HPP
#define ITERATORS_HPP

template <typename Key, typename Info>
class Ring<Key, Info>::iterator
{
public:
    iterator();

    Data &operator*() const;
    Data *operator->() const;

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
class Ring<Key, Info>::const_iterator
{
public:
    const_iterator();

    Data &operator*() const;
    Data *operator->() const;

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
Ring<Key, Info>::iterator::iterator() { node = nullptr; }

// operators * and ->
template <typename Key, typename Info>
typename Ring<Key, Info>::Data &Ring<Key, Info>::iterator::operator*() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator *");
    else
        return node->data;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Data *Ring<Key, Info>::iterator::operator->() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator ->");
    else
        return &(node->data);
}

// operators ++
template <typename Key, typename Info>
typename Ring<Key, Info>::iterator &Ring<Key, Info>::iterator::operator++()
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
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator++(int)
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
typename Ring<Key, Info>::iterator &Ring<Key, Info>::iterator::operator--()
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
typename Ring<Key, Info>::iterator Ring<Key, Info>::iterator::operator--(int)
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
bool Ring<Key, Info>::iterator::operator==(const iterator &other) const { return node == other.node; }

template <typename Key, typename Info>
bool Ring<Key, Info>::iterator::operator!=(const iterator &other) const { return node == other.node; }

// const_iterator

// ctor
template <typename Key, typename Info>
Ring<Key, Info>::const_iterator::const_iterator() { node = nullptr; }

// operators * and ->
template <typename Key, typename Info>
typename Ring<Key, Info>::Data &Ring<Key, Info>::const_iterator::operator*() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator *");
    else
        return node->data;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Data *Ring<Key, Info>::const_iterator::operator->() const
{
    if (node == nullptr)
        throw std::string("Cannot use operator ->");
    else
        return &(node->data);
}

// operators ++
template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator &Ring<Key, Info>::const_iterator::operator++()
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
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator++(int)
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
typename Ring<Key, Info>::const_iterator &Ring<Key, Info>::const_iterator::operator--()
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
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_iterator::operator--(int)
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
bool Ring<Key, Info>::const_iterator::operator==(const const_iterator &other) const { return node == other.node; }

template <typename Key, typename Info>
bool Ring<Key, Info>::const_iterator::operator!=(const const_iterator &other) const { return node == other.node; }

#endif