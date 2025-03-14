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
int interpolationSearch(vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
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
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        mergeSort(arr, left, mid);          // Sort left half
        mergeSort(arr, mid + 1, right);     // Sort right half
        merge(arr, left, mid, right);       // Merge sorted halves
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    vector<int> inputSizes = {10, 100, 1000, 10000, 100000, 1000000}; // Test with 6 sizes
    int target;

    for (int N : inputSizes) {
        cout << "\nTesting with N = " << N << "\n";

        // Generate random array
        vector<int> arr = generateRandomNumbers(N);

        // --- Sorting for Search Operations ---
        vector<int> arrForSearch = arr; // Copy for searching
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arrForSearch, 0, N - 1); // Sort for searching
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Merge Sort (for search) Time: " << duration.count() << " us\n";

        // --- Search Operations ---
        target = arrForSearch[N/2]; // Pick a middle element as target (likely to exist)

        // Binary Search
        start = chrono::high_resolution_clock::now();
        int binaryResult = binarySearch(arrForSearch, target);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Binary Search Time: " << duration.count() << " us\n";

        // Interpolation Search
        start = chrono::high_resolution_clock::now();
        int interpResult = interpolationSearch(arrForSearch, target);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Interpolation Search Time: " << duration.count() << " us\n";

        // --- Sorting Operations ---
        vector<int> arrForSort = arr; // Copy for sorting
        start = chrono::high_resolution_clock::now();
        selectionSort(arrForSort);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Selection Sort Time: " << duration.count() << " us\n";

        arrForSort = arr; // Reset array
        start = chrono::high_resolution_clock::now();
        mergeSort(arrForSort, 0, N - 1);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Merge Sort Time: " << duration.count() << " us\n";
    }

    return 0;
}
