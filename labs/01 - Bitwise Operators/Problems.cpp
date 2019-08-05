#include<iostream>
#include<vector>
#include<math.h>

bool odd(int a)
{
    return a & 1;
    // Returns the rightmost bit of the number (0 & 1 is 0, 1 & 1 is 1)
    // Odd numbers have a set rightmost bit
}

bool powerOf2(int a)
{
    return a && !(a & (a-1));
    // Powers of 2 have 1 set bit followed by n 0 bits
    // The number before a power of 2 has n set bits in a row
    // The & of those 2 should be 0 (e.g. 1000 & 0111 = 0000)
}

int twoToThePowerOf(int p)
{
    return 1 << p;
    // Shifting a number once in this direction multiplies it by 2
}

int multiplyBySeven(int a)
{
    return (a << 3) - a;
    // multiply by 2 to the power of 3 (8) and subtract the number
}

int uniqueAmongPairs(std::vector<int> pairs)
{
    int result = pairs[0];
    int size = pairs.size();
    for (int i = 1 ; i < size ; i++)
    {
        result ^= pairs[i];
    }

    return result;

    // XOR of 2 identical numbers is 0
    // XOR of 0 and a number is the same number
    // The pairs will zero each other
}

bool nthBit(int a, unsigned n)
{
    return odd(a >> (n-1));
    // Shift n - 1 times and then get the last bit
}

int negative(int a)
{
    return (~a + 1);
    // Read about Two's Compliment
}

unsigned rightmostSetBit(int a)
{
    return log2(a & -a) + 1;
    // <WallOfText>
    // Again read about Two's Compliment to remember how negative numbers are represented
    // In the negative representation of a, the ending 0s will fist be flipped to 1 then back to 0 after we add 1
    // The rightmost 1 will be flipped to 0 and then back to 1 after we add 1
    // After the &, all the trailing 0s in the negative number will unset the trailing numbers in the original
    // The rightmost 1 in the original number will be also be 1 in the negative one
    // After the & we get ????10...0
    // log2 tells us how many times we should multiply 2 by itself (10 in binary) to get the above number
    // aka how many 0s we should add to 10 to get the above number
    // then add 1 (the 0 in 10)

    // e.g.
    // only looking at the last 3 bits (the rest don't matter)
    // 6(10) = ...110 (2)
    // For -6, first we flip the bits ...001
    // then we add 1 ...010, notice how the trailing 0s and the rightmost 1 remain the same
    // After & we get ...010
    // log2(...010) = 1
    // Add 1 to get 2 - the position of the rightmost bit
    // </WallOfText>

}

unsigned rightmostDifferentBit(int a, int b)
{
    return rightmostSetBit(a ^ b);
    // XOR will only return 1 if it gets 2 different bits
    // We search for the rightmost 1 after a XOR
}

int main()
{
    return 0;
}
