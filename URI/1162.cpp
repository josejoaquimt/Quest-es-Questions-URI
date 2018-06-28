// C++ program to count inversions using Binary Indexed Tree
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
 
// Returns sum of arr[0..index]. This function assumes
// that the array is preprocessed and partial sums of
// array elements are stored in BITree[].
int getSum(int BITree[], int index)
{
  int sum = 0; // Initialize result
 
  // Traverse ancestors of BITree[index]
  while (index > 0)
    {
      // Add current element of BITree to sum
      sum += BITree[index];
 
      // Move index to parent node in getSum View
      index -= index & (-index);
    }
  return sum;
}


void updateBIT(int BITree[], int n, int index, int val)
{
  // Traverse all ancestors and add 'val'
  while (index <= n)
    {
      // Add 'val' to current node of BI Tree
      BITree[index] += val;
 
      // Update index to that of parent in update View
      index += index & (-index);
    }
}
 
// Returns inversion count arr[0..n-1]
int getInvCount(int arr[], int n)
{
  int invcount = 0; // Initialize result
 
  // Find maximum element in arr[]
  int maxElement = 0;
  for (int i=0; i<n; i++)
    if (maxElement < arr[i])
      maxElement = arr[i];
 
  // Create a BIT with size equal to maxElement+1 (Extra
  // one is used so that elements can be directly be
  // used as index)
  int BIT[maxElement+1];
  for (int i=1; i<=maxElement; i++)
    BIT[i] = 0;
 
  // Traverse all elements from right.
  for (int i=n-1; i>=0; i--)
    {
      // Get count of elements smaller than arr[i]
      invcount += getSum(BIT, arr[i]-1);
 
      // Add current element to BIT
      updateBIT(BIT, maxElement, arr[i], 1);
    }
 
  return invcount;
}
 
// Driver program
int main()
{
  int T; cin >> T;
  while(T--) {
    int n; cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
      cin >> arr[i];
    }
    cout << "Optimal train swapping takes " << getInvCount(arr,n) << " swaps.\n";
  }
  return 0;
}
