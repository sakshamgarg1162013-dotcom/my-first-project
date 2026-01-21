#include <iostream>
using namespace std;

int peakelement(int arr[], int n) {
    int s = 0, e = n - 1;

    while (s < e) {
        int mid = s + (e - s) / 2;

        if (arr[mid] < arr[mid + 1]) {
            s = mid + 1;
        }
        else {
            e = mid;
        }
    }

    return arr[s];
}

int main() {
    int arr[5] = {0, 10, 5, 3, 2};
    cout << "The peak element is " << peakelement(arr, 5) << endl;
    return 0;
}
