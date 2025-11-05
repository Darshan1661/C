#include <stdio.h>
#include <time.h>

#define ARR_SIZE 1000000

int binary_search_original(int arr[], int n, int x) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int binary_search_single_test(int arr[], int n, int x) {
    int low = 0, high = n;
    int mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    if (low < n && arr[low] == x) {
        return low;
    } else {
        return -1;
    }
}

int main() {
    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = i * 2;  // sample sorted array of even numbers
    }

    int target = 987654;

    clock_t start, end;
    double time_orig, time_single;

    // Test original binary search
    start = clock();
    int res_orig = binary_search_original(arr, ARR_SIZE, target);
    end = clock();
    time_orig = (double)(end - start) / CLOCKS_PER_SEC;

    // Test single-test binary search
    start = clock();
    int res_single = binary_search_single_test(arr, ARR_SIZE, target);
    end = clock();
    time_single = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Original binary search result: %d, time: %e seconds\n", res_orig, time_orig);
    printf("Single-test binary search result: %d, time: %e seconds\n", res_single, time_single);

    return 0;
}

