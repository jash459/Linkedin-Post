


#include <bits/stdc++.h>
using namespace std;

int helper(vector<int> &arr, int pages) {
    int n = arr.size(); 
    int students = 1;  
    long long pagesStudent = 0; 
    for (int i = 0; i < n; i++) {
        if (pagesStudent + arr[i] <= pages) {   // if page count is less the number of page given, then we can assign that book to the current student 
            pagesStudent += arr[i];
        }
        else {
            students++;   // if page count more then the number of page given, then we incremnet the student count and assign that book to the current student
            pagesStudent = arr[i];
        }
    }
    return students;  // we return the no of students we are able to assign all pages
}

int findPages(vector<int>& arr, int n, int m) {
    if (n < m) return -1;  // if no of books is less then no. of students , then its not possible to assign books to each students, hence return -1

    int low = INT_MIN;
    int high = 0;
    for (int i = 0; i < n; i++) {
        low = max(low, arr[i]);  // calculate the lowest range of search space 
        high += arr[i];  // calculate the maximum range of search space 
    }    

    for (int pages = low; pages <= high; pages++) {  
        if (helper(arr, pages) == m) {   // check if value return from helper function == no of student, means we are able to allocate books to each students
            return pages;
        }
    }
    return low;  // we will return low boz we need to find the minimum no of pages we need to allocate to all students 
}

int main()
{
    vector<int> arr = {25, 46, 28, 49, 24};
    int n = 5;
    int m = 4;
    int ans = findPages(arr, n, m);
    cout << "The answer is: " << ans << "\n";
    return 0;
}

