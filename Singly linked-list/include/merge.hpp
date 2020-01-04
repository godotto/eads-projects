#ifndef MERGE_HPP
#define MERGE_HPP

#include "sequence.hpp"

template <typename Key, typename Info>
Sequence<Key, Info> Merge(const Sequence<Key, Info> &sequence1, int start1, int len1,
                          const Sequence<Key, Info> &sequence2, int start2, int len2,
                          int count)
{
    Sequence<Key, Info> newSequence;

    if (sequence1.IsEmpty() && sequence2.IsEmpty())
        return newSequence;

    for (int i = 0; i < count; i++)
    {
        newSequence += sequence1.GetFragmentOfSequence(start1, len1);
        newSequence += sequence2.GetFragmentOfSequence(start2, len2);

        start1 += len1;
        start2 += len2;
    }

    return newSequence;
}

#endif