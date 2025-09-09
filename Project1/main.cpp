#include<iostream>

#include <random>
#include <filesystem>
#include <fstream>


std::random_device dev;
std::mt19937 rnd(dev());

void shuffleIntArray(const int number, int*& array)
{
    for (int i = number - 1; i > 0; i--)
    {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rnd);
        std::swap(array[i], array[j]);
    }
}

void updateIntArray(const int number, int*& array, bool do_reverse)
{
    array = new int[number];
    if (!do_reverse)
    {
        for (int i = 0; i < number; i++) array[i] = i;
    }
    else
    {
        for (int i = 0, j = number - 1; i < number; i++, j--) array[i] = j;
    }
}




unsigned long long fact(int a)
{
    unsigned long long ret = 1;
    for (int i = 2; i <= a; i++)
    {
        ret *= i;
    }
    return ret;
}

// An optimized version of Bubble Sort
//Best: O(n)
//Average: O(n ^ 2)
//Worst : O(n ^ 2)
void bubbleSort(int*& arr, int n, int& counter) {
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
                counter++;
            }
        }

        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

// To heapify a subtree rooted with node i
// which is an index in arr[].
void heapify(int*& arr, int n, int i, int& counter) {
    counter++;

    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, counter);
    }
}

// Main function to do heap sort
void heapSort(int*& arr, int n, int& counter) {

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, counter);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {

        // Move current root to end
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0, counter);
    }
}

int main()
{
    int number_of_numbers = 1000;
    int* good_numbers;
    int* bad_numbers;
    updateIntArray(number_of_numbers, good_numbers, 0);
    updateIntArray(number_of_numbers, bad_numbers, 1);
    //shuffleIntArray(number_of_numbers, numbers);
    
    //std::ofstream file;
    //file.open("out.txt");
    //
    //for (int i = 0; i < number_of_numbers; i++)
    //{
    //    file << numbers[i] << " ";
    //}
    //
    //file.close();
    int counter = 0;
    heapSort(good_numbers, number_of_numbers, counter);
    std::cout << "Best: " << counter << '\n';
    counter = 0;
    heapSort(bad_numbers, number_of_numbers, counter);
    std::cout << "Worst: " << counter << "\n\n";

    updateIntArray(number_of_numbers, good_numbers, 0);
    updateIntArray(number_of_numbers, bad_numbers, 1);

    bubbleSort(good_numbers, number_of_numbers, counter);
    std::cout << "Best: " << counter << '\n';
    counter = 0;
    bubbleSort(bad_numbers, number_of_numbers, counter);
    std::cout << "Worst: " << counter << "\n\n";

    updateIntArray(number_of_numbers, good_numbers, 0);
    updateIntArray(number_of_numbers, bad_numbers, 1);

    delete[] good_numbers;
    delete[] bad_numbers;

    return 0;
}