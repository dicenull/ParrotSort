#pragma once

class Counter
{
    int max;
    bool refresh = false;

public:
    int count;

public:
    Counter(int max)
        :count(0), max(max)
    {}

    void increment()
    {
        count++;
        count %= max;

        refresh = (count == 0);
    }

    bool isRefresh() { return refresh; }
};