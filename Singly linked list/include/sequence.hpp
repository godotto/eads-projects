#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <iostream>

template <typename Key, typename Info>
class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence<Key, Info> &other);

    Sequence<Key, Info> &operator=(const Sequence<Key, Info> &other);
    bool operator==(const Sequence<Key, Info> &other);
    bool operator!=(const Sequence<Key, Info> &other);
    Sequence<Key, Info> operator+(const Sequence<Key, Info> &other);
    Sequence<Key, Info> &operator+=(const Sequence<Key, Info> &other);

    void PushFront(const Key &key, const Info &info);                                        // adds new element on the beginning
    void PushBack(const Key &key, const Info &info);                                         // adds new element on the end
    bool Insert(const Key &key, const Info &info, const Key &after, int whichOccurance = 1); // adds new element after chosen existing element

    bool PopFront();                                     // removes the first element
    bool PopBack();                                      // removes the last element
    bool Remove(const Key &key, int whichOccurance = 1); // removes chosen element
    bool Clear();                                        // removes all elements
    bool RemoveAllOccurances(const Key &key);            // removes all elements with chosen key

    bool IsEmpty() const;                                                   // returns true if list contains no elements
    int Size() const;                                                       // returns number of elements
    bool Find(const Key &key, int whichOccurance = 1) const;                // returns true if list contains sought element
    int NumberOfOccurances(const Key &key) const;                           // returns number of occurances of chosen key
    void Print() const;                                                     // prints whole list
    void Print(std::ostream &os) const;                                     // prints whole list and saves result of operation in ostream
    Sequence<Key, Info> GetFragmentOfSequence(int start, int length) const; // return a part of list

private:
    struct Node
    {
        Key key;
        Info info;
        Node *next;

        Node(const Key &key, const Info &info);
    };

    Node *head;
    int size;
};

// ctors and dtor

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence()
{
    head = nullptr;
    size = 0;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    Clear();
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &other)
{
    head = nullptr;
    size = 0;

    Node *temp = other.head;
    while (temp != nullptr)
    {
        PushBack(temp->key, temp->info);
        temp = temp->next;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info>::Node::Node(const Key &key, const Info &info)
{
    this->key = key;
    this->info = info;
}

// operators overloading

template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &other)
{
    if (this == &other)
        return *this;

    Clear();

    Node *temp = other.head;
    while (temp != nullptr)
    {
        PushBack(temp->key, temp->info);
        temp = temp->next;
    }

    return *this;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info> &other)
{
    if (size != other.size)
        return false;

    Node *temp1 = this->head, *temp2 = other.head;
    while (temp1 != nullptr)
    {
        if ((temp1->key != temp2->key) || (temp1->info != temp2->info))
            return false;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info> &other)
{
    return !operator==(other);
}
template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info> &other)
{
    Sequence<Key, Info> newSequence;
    Node *temp = this->head;

    while (temp != nullptr)
    {
        newSequence.PushBack(temp->key, temp->info);
        temp = temp->next;
    }

    temp = other.head;
    while (temp != nullptr)
    {
        newSequence.PushBack(temp->key, temp->info);
        temp = temp->next;
    }

    return newSequence;
}

template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator+=(const Sequence<Key, Info> &other)
{
    Node *temp = other.head;
    while (temp != nullptr)
    {
        this->PushBack(temp->key, temp->info);
        temp = temp->next;
    }

    return *this;
}

// adding methods

template <typename Key, typename Info>
void Sequence<Key, Info>::PushFront(const Key &key, const Info &info)
{
    if (IsEmpty())
    {
        head = new Node(key, info);
        head->next = nullptr;
        size++;
    }
    else
    {
        Node *temp = new Node(key, info);
        temp->next = head;
        head = temp;
        size++;
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::PushBack(const Key &key, const Info &info)
{
    if (IsEmpty())
    {
        head = new Node(key, info);
        head->next = nullptr;
        size++;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = new Node(key, info);
        temp->next->next = nullptr;
        size++;
    }
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Insert(const Key &key, const Info &info, const Key &after, int whichOccurance)
{
    int counter = 0;

    Node *temp1 = head;
    while (temp1 != nullptr)
    {
        if (after == temp1->key)
        {
            counter++;
            if (whichOccurance == counter)
            {
                Node *temp2 = new Node(key, info);
                temp2->next = temp1->next;
                temp1->next = temp2;
                size++;
                return true;
            }
        }
        temp1 = temp1->next;
    }

    return false;
}

// removing methods

template <typename Key, typename Info>
bool Sequence<Key, Info>::PopFront()
{
    if (IsEmpty())
        return false;

    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::PopBack()
{
    if (IsEmpty())
        return false;

    if (size == 1)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node *temp1 = head;
        while (temp1->next->next != nullptr)
            temp1 = temp1->next;

        Node *temp2 = temp1->next;
        temp1->next = temp2->next;
        delete temp2;
    }
    size--;

    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Remove(const Key &key, int whichOccurance)
{
    int counter = 0;

    if (IsEmpty())
        return false;
    else if (head->key == key && whichOccurance == 1)
    {
        PopFront();
        return true;
    }
    else if (head->key == key)
        counter++;

    Node *temp1 = head, *temp2;
    while (temp1->next != nullptr)
    {
        if (key == temp1->next->key)
        {
            counter++;
            if (whichOccurance == counter)
            {
                Node *temp2 = temp1->next;
                temp1->next = temp2->next;
                delete temp2;
                size--;
                return true;
            }
        }
        temp1 = temp1->next;
    }

    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Clear()
{
    if (IsEmpty())
        return false;

    int numberOfIterations = size;
    for (int i = 0; i < numberOfIterations; i++)
        PopFront();

    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::RemoveAllOccurances(const Key &key)
{
    if (IsEmpty())
        return false;

    int occurances = 0;
    while (head != nullptr && head->key == key)
    {
        PopFront();
        occurances++;
    }

    if (IsEmpty())
        return true;

    Node *temp1 = head, *temp2;

    while (temp1->next != nullptr)
    {
        if (key == temp1->next->key)
        {
            Node *temp2 = temp1->next;
            temp1->next = temp2->next;
            delete temp2;
            size--;
            occurances++;
        }
        temp1 = temp1->next;
    }

    if (occurances)
        return true;
    else
        return false;
}

// other methods

template <typename Key, typename Info>
bool Sequence<Key, Info>::IsEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template <typename Key, typename Info>
int Sequence<Key, Info>::Size() const { return size; }

template <typename Key, typename Info>
bool Sequence<Key, Info>::Find(const Key &key, int whichOccurance) const
{
    Node *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (key == temp->key)
        {
            counter++;
            if (whichOccurance == counter)
                return true;
        }
        temp = temp->next;
    }

    return false;
}

template <typename Key, typename Info>
int Sequence<Key, Info>::NumberOfOccurances(const Key &key) const
{
    Node *temp = head;
    int counter = 0;

    while (temp != nullptr)
    {
        if (temp->key == key)
            counter++;
        temp = temp->next;
    }
    return counter;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::Print() const
{
    if (IsEmpty())
    {
        std::cout << "List is empty\n";
    }
    else
    {
        std::cout << "--------------------\n";
        const typename Sequence<Key, Info>::Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << "Key: " << temp->key << "\nInfo: " << temp->info << std::endl
                      << std::endl;
            temp = temp->next;
        }

        std::cout << "--------------------\n";
    }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::Print(std::ostream &os) const
{
    if (size == 0)
    {
        std::cout << "List is empty\n";
        os << "empty list" << std::endl;
    }
    else
    {
        std::cout << "--------------------\n";
        const typename Sequence<Key, Info>::Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << "Key: " << temp->key << "\nInfo: " << temp->info << std::endl
                      << std::endl;
            temp = temp->next;
        }

        std::cout << "--------------------\n";

        os << "successful" << std::endl;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::GetFragmentOfSequence(int start, int length) const
{
    Sequence<Key, Info> fragmentOfSequence;
    Node *temp = head;

    for (int i = 0; i < start && temp != nullptr; i++)
        temp = temp->next;

    for (int i = 0; i < length && temp != nullptr; i++)
    {
        fragmentOfSequence.PushBack(temp->key, temp->info);
        temp = temp->next;
    }

    return fragmentOfSequence;
}

#endif