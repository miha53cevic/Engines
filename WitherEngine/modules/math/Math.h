#pragma once
#include <random>

#define PI 3.141592f

class Math
{
public:
    Math() {}

    // Random number generator in given range
    static float fRandom(float first, float second)
    {
        std::random_device rd;
        std::default_random_engine generator(rd()); // rd() provides a random seed
        std::uniform_real_distribution<float> distribution(first, second);

        return distribution(generator);
    }

    static int iRandom(int first, int second)
    {
        std::random_device rd;
        std::default_random_engine generator(rd()); // rd() provides a random seed
        std::uniform_int_distribution<int> distribution(first, second);

        return distribution(generator);
    }

    // Converts degress to radians
    static float toRadian(float deg)
    {
        return deg * (PI / 180);
    }

    // Maps values from one range to another
    static float map(float s, float a1, float a2, float b1, float b2)
    {
        return b1 + ((s - a1) * (b2 - b1)) / (a2 - a1);
    }

private:
};