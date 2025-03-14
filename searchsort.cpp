#include <iostream>
#include <vector>
#include <chrono> // For runtime measurement
#include <cstdlib> // For rand()
#include <ctime> // For seeding rand()
using namespace std;

// Function to generate N random integers
vector<int> generateRandomNumbers(int N) {
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0 and 999
    }
    return arr;
}

// --- Binary Search Algorithm ---
// Explanation: Binary Search finds an element in a sorted array by repeatedly dividing the search range in half.
// Time Complexity: O(log N) - Best, Average, Worst (requires sorted array).
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        if (arr[mid] == target) {
            return mid; // Element found, return index
        }
        if (arr[mid] < target) {
            left = mid + 1; // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    return -1; // Element not found
}

// --- Interpolation Search Algorithm ---
// Explanation: Interpolation Search estimates the position of the target based on a linear interpolation formula.
// It works best for uniformly distributed sorted data. Time Complexity: O(log log N) average, O(N) worst.
int interpolationSearch(vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Interpolation formula to estimate position
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[pos] == target) {
            return pos; // Element found
        }
        if (arr[pos] < target) {
            low = pos + 1; // Search upper part
        } else {
            high = pos - 1; // Search lower part
        }
    }
    return -1; // Element not found
}

// --- Selection Sort Algorithm ---
// Explanation: Selection Sort repeatedly finds the minimum element from the unsorted part and places it at the beginning.
// Time Complexity: O(N^2) - Best, Average, Worst.
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // Assume current index has minimum value
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Update minimum index
            }
        }
        swap(arr[i], arr[min_idx]); // Swap current with minimum
    }
}

// --- Merge Sort Helper: Merge Function ---
// Merges two sorted subarrays into one sorted array
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray
    vector<int> L(n1), R(n2); // Temporary arrays

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left; // Indices for merging
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++]; // Take from left subarray
        } else {
            arr[k] = R[j++]; // Take from right subarray
        }
        k++;
    }
    // Copy remaining elements of L[] if any
    while (i < n1) arr[k++] = L[i++];
    // Copy remaining elements of R[] if any
    while (j < n2) arr[k++] = R[j++];
}

// --- Merge Sort Algorithm ---
// Explanation: Merge Sort divides the array into halves, recursively sorts them, and merges them back.
// Time Complexity: O(N log N) - Best, Average, Worst.
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        mergeSort(arr, left, mid);          // Sort left half
        mergeSort(arr, mid + 1, right);     // Sort right half
        merge(arr, left, mid, right);       // Merge sorted halves
    }
}

// Function to print array
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0)); // Seed random number generator
    int N, target;

    // Input number of elements
    cout << "Enter the number of random integers (N): ";
    cin >> N;

    // Generate random array
    vector<int> arr = generateRandomNumbers(N);
    cout << "Original Array: ";
    printArray(arr);

    // --- Sorting for Search Operations ---
    vector<int> arrForSearch = arr; // Copy for searching (needs to be sorted)
    mergeSort(arrForSearch, 0, N - 1); // Sort using Merge Sort for searching
    cout << "Sorted Array (for searching): ";
    printArray(arrForSearch);

    // --- Search Operations ---
    cout << "Enter a number to search: ";
    cin >> target;

    // Binary Search
    int binaryResult = binarySearch(arrForSearch, target);
    cout << "Binary Search: " << (binaryResult == -1 ? "Not found" : "Found at index " + to_string(binaryResult)) << endl;

    // Interpolation Search
    int interpResult = interpolationSearch(arrForSearch, target);
    cout << "Interpolation Search: " << (interpResult == -1 ? "Not found" : "Found at index " + to_string(interpResult)) << endl;

    // --- Sorting Operations ---
    vector<int> arrForSort = arr; // Copy for sorting
    cout << "\nSorting with Selection Sort...\n";
    selectionSort(arrForSort);
    cout << "Selection Sort Result: ";
    printArray(arrForSort);

    arrForSort = arr; // Reset array
    cout << "Sorting with Merge Sort...\n";
    mergeSort(arrForSort, 0, N - 1);
    cout << "Merge Sort Result: ";
    printArray(arrForSort);

    return 0;
}