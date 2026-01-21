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
    int arr[4] = {0,2,1,0};
    cout << "The peak element is " << peakelement(arr, 4) << endl;
    return 0;
}
