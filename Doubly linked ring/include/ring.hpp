#ifndef RING_HPP
#define RING_HPP

template <typename Key, typename Info>
class Ring
{
public:
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
        struct Data
        {
            Key key;
            Info info;

            Data(const Key &key, const Info &info);
        };

        Data data;
        Node *next;
        Node *previous;
    };

    Node *first;
    int size;

    friend class iterator;
    friend class const_iterator;
};

// ctors and dtor


#endif