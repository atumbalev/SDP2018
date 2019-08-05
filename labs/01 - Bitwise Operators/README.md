# Bitwise Operations

Operations that work on a variable on the level of it's individual bits.

## Advantages
* Faster than arithmetic operations
* Can be used to pack bits in a larger variable to save memory (e.g. A single boolean variable which has 2 possible values so it can be represented by a single bit. The smallest adressable unit in a computer is the byte so the bool type in c++ is 1 byte or 8 bits. While we are unable to create a 1 bit variable we could for example use bitwise operators to save 8 different boolean values in one bool variable)
* A lot of encryption and compression algorithms are done on bit and not byte level.

## Disadvantages
* Makes code hard to read.
* As computers get faster the difference in speed becomes less relevant (though if you want maximum optimization, you can't escape them)

## Bitwise operators
Equivalents of some logical operators ( OR (||), AND (&&), NOT(!), XOR(not part of the c++ standard)) but applied on each individual bit

### Bitwise OR (|)

#### General usage

```
6(10) = 0...0110(2)
5(10) = 0...0101(2)

Applying | to the two

...0110
...0101
_______ |
...0111

If either of the 2 bits that share a position are set, the bit in the same position in the result will also be set, otherwise it's unset.
Result: 6 | 5 = 7 
```

### Bitwise AND (&)

```
6(10) = 0...0110(2)
5(10) = 0...0101(2)

Applying & to the two

...0110
...0101
_______ &
...0100

If both of the 2 bits that share a position are set, the bit in the same position in the result will also be set, otherwise it's unset.
Result: 6 & 5 = 4 
```

### Bitwise XOR (^)

```
6(10) = 0...0110(2)
5(10) = 0...0101(2)

Applying ^ to the two

...0110
...0101
_______ &
...0011

If 2 bits that share a position are different, the bit in the same position in the result will be set, otherwise it's unset.
Result: 6 & 5 = 3
```

### Bitwise XOR (^)

```
Swap every bit in a variable
~0111(2) = 1000(2)

NB!: Negative numbers in modern computers are done using Two's Compliment. We first apply ~, then add 1.
~14(10) + 1(10) = -14(10)
```

## Bitshift Operators
Shift bits either to the right or to the left, the "shifted out" bits will be discarded and replaced with 0s on the other end

### Left shift ( << )
```
NB! Actual numbers in computers don't have 5 bits, this is just an example

01100(2) << 2(10)
First we shift twice in the given direction (the leftmost 2 bits 01 are discared)
100(2)
Then we add two 0s on the other end
10000(2) 
```

### Right shift ( >> )
```
NB! Actual numbers in computers don't have 5 bits, this is just an example

01100(2) >> 2(10)
First we shift twice in the given direction (the rightmost 2 bits 00 are discared)
011(2)
Then we add two 0s on the other end
00011(2) 
```

## Some applications

### Fast multiplication by 2

```
Shifting left once multiples the number by 2
7(10) = 0...0111(2)
0...0111(2) << 1(10) = 0...01110(2) = 14(10) = 7(10) * 2(10)
```

### Fast whole division by 2
```
Shifting right once divides the number by 2 (whole division)
6(10) = 0...0110(2)
7(10) = 0...0111(2)

0...0110(2) >> 1(10) = 0...0011(10) = 3(10) = 6(10) / 2(10)
0...0111(2) >> 1(10) = 0...0011(10) = 3(10) = 7(10) / 2(10)
```

### Working with packed bits
Say we've packed 8 boolean variables in one byte
values = 00110001(2) would mean that the 1st, 5th and 6th (counting from the right) of these variables are true and the rest are false
We will need a set of operations to work with these values

#### Setting a bit
```
If we want to make the first value true:
values | 1
Result:
00110001
00000001
________ |
00110001

The first seven 0s won't change anything (x | 0 = x)
The last 1 will set the last bit (x | 1 = 1)

The same logic can be applied to every other bit by padding with enough 0s at the end
Setting the nth bit:
values |= (1 << n);
```
#### Unsetting a bit
```
If we want to make the first value false:
values | 11111110(2)
Result:
00110001
11111110
________ |
00110000

The first seven 1s won't change anything (x | 1 = x)
The last 0 will unset the last bit (x | 0 = 0)

The same logic can be applied to every other bit by padding with enough 1s at the end
Unsetting the nth bit:
values &= ~(1 << (n - 1));
```

#### Toggling a bit
```
If we want to change the first value:
values ^ 00000001(2)
Result:
00110001
00000001
________ |
00110000

The first seven 0s won't change anything (x ^ 0 = x)
The last 1 will toggle the last bit (x ^ 1 = ~x)

The same logic can be applied to every other bit by padding with enough 1s at the end
Toggling the nth bit:
values ^= (1 << (n - 1));
```

#### Checking a bit
```
If we want to get the value of the first bit:
values & 00000001(2)
Result:
00110001
00000001
________ |
00000001

00110000
00000001
________ |
00000000

The first seven 0s will unset the first 7 bits (x & 0 = 0)
The last 1 will keep the value of the last bit (x & 1 = x)

The same logic can be applied to every other bit by shifting the packed bits until the one we want to check is first
Checking the nth bit:
(values  >> (n-1)) & 1
```
