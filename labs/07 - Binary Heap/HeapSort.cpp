#include<iostream>

size_t parent(int i)
{
    return (i-1)/2;
}

size_t leftChild(int i)
{
    return i*2+1;
}

size_t rightChild(int i)
{
    return i*2+2;
}

template <typename T>
void heapify(T* v, size_t n, size_t i)
{
    while(true)
    {
        size_t largest = i;
        size_t l = leftChild(i);
        size_t r = rightChild(i);
        if (l < n && v[largest] < v[l])
            largest = l;
        if (r < n && v[largest] < v[r])
            largest = r;
        if (largest == i)
            break;
        else
        {
            std::swap(v[i], v[largest]);
            i = largest;
        }
    }
}

template <typename T>
void buildHeap(T* v, int n) //linear time
{
    size_t last = n - 1;
    for(int i = last; i >= 0 ; i--)
    {
        heapify(v,n,i);
    }
}

template <typename T>
void heapSort(T* v, size_t n)
{
    buildHeap(v,n);
    for (int i = n-1 ; i > 0; i--)
    {
        std::swap(v[0],v[n-1]);
        n--;
        heapify(v,i,0);
    }
}

int main()
{
    int arr[5] = {3,4,5,1,2};
    heapSort(arr,5);
    for(int i = 0 ; i < 5; i++)
        std::cout<<arr[i]<<" ";
    std::cout<<"\n";

    return 0;
}
