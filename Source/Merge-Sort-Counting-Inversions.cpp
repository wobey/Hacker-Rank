// Author: John Fitzgerald
// Title: Arrays-Left-Rotation.cpp
// Date Modified: 3/30/2018
/* Description:
https://www.hackerrank.com/challenges/ctci-merge-sort/problem
Given  datasets, print the number of inversions that must be swapped to sort each dataset on a new line.

Input Format:
The first line contains an integer, D, denoting the number of datasets.
The 2D subsequent lines describe each respective dataset over two lines:

1) The first line contains an integer, N, denoting the number of elements in the dataset.
2) The second line contains N space-separated integers describing the respective values of [a0, a1, a2...aN-1]

Constraints:
- 1 <= D <= 15
- 1 <= N <= 10^5
- 1 <= arri <= 10^7

For each of the D datasets, print the number of inversions that must be swapped to sort the dataset on a new line.

Sample Input:
2
5
1 1 1 2 2
5
2 1 3 1 2

Sample Output:
0
4
*/
#include <vector>
#include <iostream>
using namespace std;

long long NUM_INVERSIONS = 0;
long long count_inversions(vector<long long>);
void mergeSort(vector<long long>&, int, int);
void merge(vector<long long>&, int, int, int);

long long count_inversions(vector<long long> a)
{
	// long long num_inversions = 0;
	int size = a.size();
	bool isSorted = true;

	// TODO: try utilizing a lambda
	// determine if sorted already
	for (int i = 0; i < size - 1; ++i)
	{
		if (a[i] > a[i + 1])
		{
			isSorted = false;
			break;
		}
	}

	// perform merge sort and record number of inversions
	if (!isSorted)
		mergeSort(a, 0, a.size() - 1);

	// for_each(a.begin(), a.end(), [](int val) { cout << val << " "; });
	// cout << endl;

	return NUM_INVERSIONS;
}

void mergeSort(vector<long long>& elements, int left, int right)
{
	// split
	if (left < right)
	{
		int middle = (left + right) / 2;
		// split left
		mergeSort(elements, left, middle);
		// split right
		mergeSort(elements, middle + 1, right);

		// merge the two
		merge(elements, left, middle, right);
	}
}

// int mergeSort(vector<long long> a)
// {
//     int size = a.size();
//     vector<vector<long long>> elements;
//     for_each(a.begin(), a.end(), [&elements](int val) { elements.push_back(vector<long long>(1, val)); });  
//     // print
//     // for_each(elements.begin(), elements.end(), [](vector<long long> val) { cout << val[0] << " "; });  

//     // compare left half, and store in new left vector (repeat for right)
//     // continue until two remain

//     cout << "size=" << size << endl;

//     while (size > 1)
//     {
//         // resize vector<vector<long long>>
//         std::vector<vector<long long>>::const_iterator it = elements.begin();
//         int index = 0;
//         // for_each(elements.begin(), elements.end(), [&]() 
//         // { 
//         //     if (elements.at(index).empty())
//         //         elements.erase(elements.begin() + index);
//         //     ++index; 
//         // });

//         --size;
//     }

//     for (int i = 0; i < size; ++i)
//     {
//         cout << "i=" << i << " ";
//     }

//     return -1;
// }

void merge(vector<long long>& a, int left, int middle, int right)
{
	int size = right - left + 1;
	vector<long long> temp;

	// TODO: cut excess memory useage
	for (int i = 0; i < size; ++i)
		temp.push_back(a.at(left + i));

	middle = middle - left;
	right = right - left;
	int k = 0, i = 0, j = middle + 1;

	while (i <= middle && j <= right)
	{
		if (temp.at(i) <= temp.at(j))
		{
			a.at(k) = temp.at(i);
			++i;
		}
		else
		{
			a.at(k) = temp.at(j);
			++j;
		}
		++k;
	}

	// copy left
	if (i > middle)
	{
		for (; j <= right; ++j, ++k)
			a.at(k) = temp.at(j);
	}
	// copy right
	else
	{
		for (; i <= middle; ++i, ++k)
			a.at(k) = temp.at(i);
	}

	++NUM_INVERSIONS;
}

int main()
{
	int t;
	cin >> t;

	for (int a0 = 0; a0 < t; a0++) {
		int n;
		cin >> n;
		vector<long long> arr(n);
		
		for (int arr_i = 0; arr_i < n; arr_i++) 
		{
			cin >> arr[arr_i];
		}
		cout << count_inversions(arr) << endl;
		
		NUM_INVERSIONS = 0;
	}
	return 0;
}
