#include<iostream>

#include <random>
#include <chrono>

//=================================================================================
//      FUNCTIONS
//=================================================================================
std::random_device dev;
std::mt19937 rnd(dev());

// Shuffle
void shuffleIntArray(const int number, int*& array)
{
    for (int i = number - 1; i > 0; i--)
    {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rnd);
        std::swap(array[i], array[j]);
    }
}

// Update
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

// Arraying
void arrayingArrays(const int number, int*& good_array, int*& bad_array, int*& random_array)
{
    updateIntArray(number, good_array, 0);
    updateIntArray(number, bad_array, 1);
    updateIntArray(number, random_array, 1);
    shuffleIntArray(number, random_array);
}

// Debug
void debugArray(const int number, int*& array)
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << "... ";
    for (int i = number - 5; i < number; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

// Benchmark
namespace chr = std::chrono;
void benchmark(const int number, int* good_array, int* bad_array, int* random_array, void (*sort)(const int, int*&))
{
    // Best
    chr::time_point start_time = chr::steady_clock::now();
    sort(number, good_array);
    chr::milliseconds time = chr::duration_cast<chr::milliseconds>(chr::steady_clock::now() - start_time);
    std::cout << "- Best: " << float(time.count()) / 1000 << "s\n";

    // Average
    start_time = chr::steady_clock::now();
    sort(number, random_array);
    time = chr::duration_cast<chr::milliseconds>(chr::steady_clock::now() - start_time);
    std::cout << "- Average: " << float(time.count()) / 1000 << "s\n";

    // Worst
    start_time = chr::steady_clock::now();
    sort(number, bad_array);
    time = chr::duration_cast<chr::milliseconds>(chr::steady_clock::now() - start_time);
    std::cout << "- Worst: " << float(time.count()) / 1000 << "s\n\n";
}

void printBenchmark(const char* name, const int number, int* good_array, int* bad_array, int* random_array, void (*sort)(const int, int*&))
{
    arrayingArrays(number, good_array, bad_array, random_array);
    std::cout << name << " for " << number << " numbers:\n";
    benchmark(number, good_array, bad_array, random_array, sort);
}

//---------------------------------------------------------------------------------
//      SORTS
//---------------------------------------------------------------------------------
//// Factorial
//unsigned long long fact(int a)
//{
//    unsigned long long ret = 1;
//    for (int i = 2; i <= a; i++)
//    {
//        ret *= i;
//    }
//    return ret;
//}

// Bogo - факториальная
//Best: O(1)
//Average: O(n!)
//Worst : O(n!)
bool verifyArrayIsSorted(int*& array, const int number)
{
    for (int i = 0; i < number; ++i)
    {
        if (array[i] != i)
            return 0;
    }
    return 1;
}

void bogoSort(const int number, int*& array)
{
    while (true) {
       if (verifyArrayIsSorted(array, number))
           break;
       shuffleIntArray(number, array);
    }
}

// Selection Sort - экспоненциальная
//Best: O(n ^ 2)
//Average: O(n ^ 2)
//Worst : O(n ^ 2)
void selectionSort(const int n, int*& arr)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

// Bubble Sort - полиминальная
//Best: O(n)
//Average: O(n ^ 2)
//Worst : O(n ^ 2)
void bubbleSort(const int n, int*& arr)
{
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// Heapsort - линейный логарифм
//Best: O(n log(n))
//Average: O(n log(n))
//Worst : O(n log(n))
void heapify(int*& arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(const int n, int*& arr)
{
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Перебор масива - линейная
// O(n)
void forArr(const int n, int*& arr)
{
    updateIntArray(n, arr, 0);
    std::cout << "Перебор массива на " << n << " цифр:\n";
    chr::time_point start_time = chr::steady_clock::now();
    for (int i = 0; i < n; ++i) arr[i];
    chr::milliseconds time = chr::duration_cast<chr::milliseconds>(chr::steady_clock::now() - start_time);
    std::cout << "- Time: " << float(time.count()) / 1000 << "s\n\n";
}

// Binary Search - логарифмическая
//Best: O(1)
//Average: O(log(n))
//Worst : O(log(n))
void binarySearch(const int n, int*& arr) {
    int low = 0;
    int high = n;
    int x = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return;

        if (arr[mid] < x)
            low = mid + 1;

        else
            high = mid - 1;
    }
}

//=================================================================================
//  MAIN
//=================================================================================
int main()
{
    setlocale(0, "");
    int* good_arr;
    int* bad_arr;
    int* rand_arr;
    arrayingArrays(5, good_arr, bad_arr, rand_arr);

    //std::ofstream file;
    //file.open("out.txt");
    //
    //for (int i = 0; i < number_of_numbers; i++)
    //{
    //    file << numbers[i] << " ";
    //}
    //
    //file.close();

    /*debugArray(number_of_numbers, good_numbers);
    debugArray(number_of_numbers, bad_numbers);
    debugArray(number_of_numbers, rand_numbers);*/

    printBenchmark("Bogosort", 10, good_arr, bad_arr, rand_arr, &bogoSort);

    printBenchmark("Selection Sort", 10000, good_arr, bad_arr, rand_arr, &selectionSort);

    printBenchmark("Bubble Sort", 10000, good_arr, bad_arr, rand_arr, &bubbleSort);

    printBenchmark("Heap Sort", 1000000, good_arr, bad_arr, rand_arr, &heapSort);

    forArr(1000000000, good_arr);

    printBenchmark("Binary Search", 100000000, good_arr, bad_arr, rand_arr, &binarySearch);


    delete[] good_arr;
    delete[] bad_arr;
    delete[] rand_arr;

    return 0;
}