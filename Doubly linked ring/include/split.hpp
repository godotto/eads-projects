#ifndef SPLIT_HPP
#define SPLIT_HPP

#include "ring.hpp"

template <typename Key, typename Info>
void Split(const Ring<Key, Info> &source, bool direction,
           Ring<Key, Info> &result1, int sequence1, int rep1,
           Ring<Key, Info> &result2, int sequence2, int rep2)
{    
    if (!result1.IsEmpty())
        result1.Clear();
    if (!result2.IsEmpty())
        result2.Clear();

    if (source.IsEmpty())
        return;
    
    typename Ring<Key, Info>::const_iterator it = source.begin();

    if (direction)
    {
        while (rep1 + rep2 > 0)
        {
            if (rep1 > 0)
            {
                for (int i = 0; i < sequence1; i++)
                {
                    result1.PushBack(it->key, it->info);
                    ++it;
                }
                rep1--;
            }
            if (rep2 > 0)
            {
                for (int i = 0; i < sequence2; i++)
                {
                    result2.PushBack(it->key, it->info);
                    ++it;
                }
                rep2--;
            }
        }
    }
    else
    {
        while (rep1 + rep2 > 0)
        {
            if (rep1 > 0)
            {
                for (int i = 0; i < sequence1; i++)
                {
                    result1.PushBack(it->key, it->info);
                    --it;
                }
                rep1--;
            }
            if (rep2 > 0)
            {
                for (int i = 0; i < sequence2; i++)
                {
                    result2.PushBack(it->key, it->info);
                    --it;
                }
                rep2--;
            }
        }
    }
}

#endif