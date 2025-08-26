/*problem statement: A customer purchased groceries from a store and wants to verify the prices of specific items in the bill where the items are not in sorted order. 
Write a C++/Java program to apply any 02 appropriate Searching Algorithms to check the cost of a particular item in the bill. Mention the Time and Space Complexities of Algorithms.//

//1. Linear Search

Check each element one by one until match found.
Works on unsorted or sorted arrays.

Time Complexity:
Best: O(1)
Worst: O(n)
Avg: O(n)
Space: O(1)

2. Sentinel Search

Improvement of Linear Search.
Place the target (key) as a sentinel at the end to avoid boundary checking.

Time Complexity: Same as Linear (O(n)) but slightly faster in practice.
Space: O(1)

3. Binary Search

Works only on sorted arrays.
Divide array into halves, compare middle element, repeat.

Time Complexity:
Best: O(1)
Worst/Avg: O(log n)
Space: O(1) (iterative)

4. Fibonacci Search

Works on sorted arrays using Fibonacci numbers to divide search range.
Similar to Binary, but uses Fibonacci split instead of half.

Time Complexity: O(log n)
Space: O(1)

5. Interpolation Search

Works on sorted, uniformly distributed arrays.
Uses a formula to guess position instead of always taking the middle.
Formula:
pos = low + ((key - arr[low]) * (high - low)) / (arr[high] - arr[low])

Time Complexity:
Best: O(1)
Avg: O(log log n)
Worst: O(n) (if data not uniformly distributed)
Space: O(1)*/

#include <iostream>
using namespace std;

// ---------- Searching Algorithms ----------

// Linear Search
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// Sentinel Search
int sentinelSearch(int arr[], int n, int key) {
    int last = arr[n - 1];
    arr[n - 1] = key; // place sentinel

    int i = 0;
    while (arr[i] != key)
        i++;

    arr[n - 1] = last; // restore last element
    if (i < n - 1 || arr[n - 1] == key)
        return i;
    return -1;
}

// Binary Search (works only on sorted arrays)
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Fibonacci Search (works on sorted arrays)
int min(int a, int b) { return (a < b) ? a : b; }

int fibonacciSearch(int arr[], int n, int key) {
    int fib2 = 0, fib1 = 1;
    int fib = fib1 + fib2;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        if (arr[i] < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if (arr[i] > key) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else
            return i;
    }
    if (fib1 && arr[offset + 1] == key)
        return offset + 1;
    return -1;
}

// Interpolation Search (works best for uniformly distributed sorted arrays)
int interpolationSearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high && key >= arr[low] && key <= arr[high]) {
        if (low == high) {
            if (arr[low] == key) return low;
            return -1;
        }

        int pos = low + ((double)(high - low) / 
                        (arr[high] - arr[low])) * (key - arr[low]);

        if (arr[pos] == key)
            return pos;
        if (arr[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

// ---------- Main Function ----------
int main() {
    int n, key, choice;

    cout << "Enter number of items in bill: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " item prices:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter item price to search: ";
    cin >> key;

    cout << "\nChoose Searching Algorithm:\n";
    cout << "1. Linear Search\n";
    cout << "2. Sentinel Search\n";
    cout << "3. Binary Search (sorted array required)\n";
    cout << "4. Fibonacci Search (sorted array required)\n";
    cout << "5. Interpolation Search (sorted array required)\n";
    cout << "Enter choice: ";
    cin >> choice;

    int index = -1;

    switch (choice) {
        case 1:
            index = linearSearch(arr, n, key);
            break;
        case 2:
            index = sentinelSearch(arr, n, key);
            break;
        case 3:
            index = binarySearch(arr, n, key);
            break;
        case 4:
            index = fibonacciSearch(arr, n, key);
            break;
        case 5:
            index = interpolationSearch(arr, n, key);
            break;
        default:
            cout << "Invalid choice!";
            return 0;
    }

    if (index != -1)
        cout << "\nItem found at index " << index << " (0-based index)\n";
    else
        cout << "\nItem not found in bill!\n";

    return 0;
}