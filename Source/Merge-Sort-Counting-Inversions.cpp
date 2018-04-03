// Author: John Fitzgerald
// Title: Arrays-Left-Rotation.cpp
// Date Modified: 4/3/2018
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
#include <fstream>
#include <string>
using namespace std;

void readFromFile();
unsigned long long count_inversions(vector<int>&);
unsigned long long mergeSort(vector<int>&, int, int);
unsigned long long merge(vector<int>&, int, int, int);

unsigned long long NUM_INVERSIONS_TEST = 0;

unsigned long long count_inversions(vector<int>& a)
{
	// unsigned long long num_inversions = 0;
	int size = a.size();
	bool is_sorted = true;

	// determine if sorted already
	for (int i = 0; i < size - 1; ++i)
	{
		if (a[i] > a[i + 1])
		{
			is_sorted = false;
			break;
		}
	}

	// perform merge sort and record number of inversions
	if (!is_sorted)
		return mergeSort(a, 0, a.size() - 1);

	return 0;
}

// split vector into vectors of size 1 and merge sort into a single vector
unsigned long long mergeSort(vector<int>& elements, int left, int right)
{
	unsigned long long num_inversions = 0;

	// split (if left IS NOT less than right: they're equal, so it's a single value in a vector)
	if (left < right)
	{
		int middle = (left + right) / 2; // floor if original vector size is odd

		// split left
		num_inversions += mergeSort(elements, left, middle);
		// split right
		num_inversions += mergeSort(elements, middle + 1, right);

		// merge the two
		num_inversions += merge(elements, left, middle, right);
	}

	return num_inversions;
}

// merge sorts two sides of vector into a single vector
unsigned long long merge(vector<int>& elements, int left, int middle, int right)
{
	int size = right - left + 1, num_inversions = 0, left_index, right_index, merged_index;
	vector<int> temp(size);
	middle = middle - left;
	right = right - left;

	// temp vector and merged vector indices
	left_index = 0;
	right_index = middle + 1;
	merged_index = left;

	// copy values to be compared (simulate two vectors with three indexes: left, middle, right)
	for (int i = 0; i < size; ++i)
		temp.at(i) = elements.at(left + i);

	// merge smallest value from each side of temp vector
	while (left_index <= middle && right_index <= right)
	{
		if (temp.at(left_index) <= temp.at(right_index))
		{
			elements.at(merged_index) = temp.at(left_index);
			++left_index;
		}
		else
		{
			elements.at(merged_index) = temp.at(right_index);
			num_inversions += middle - left_index + 1;
			++right_index;
		}

		++merged_index;
	}

	// copy the remaining temp's left to original vector
	if (left_index > middle)
	{
		for (; right_index <= right; ++right_index, ++merged_index)
			elements.at(merged_index) = temp.at(right_index);
	}
	// copy the remaining temp's right to original vector
	else
	{
		for (; left_index <= middle; ++left_index, ++merged_index)
			elements.at(merged_index) = temp.at(left_index);
	}

	return num_inversions;
}

int main()
{
	// do we read from a file
	bool is_file = false;

	if (is_file)
		readFromFile();
	else
	{
		int t, n;
		cin >> t;
		
		for (int a0 = 0; a0 < t; a0++) {
			unsigned long long n;
			cin >> n;
			vector<int> arr(n);

			for (int arr_i = 0; arr_i < n; arr_i++)
				cin >> arr[arr_i];

			cout << count_inversions(arr) << endl;
		}
	}

	return 0;
}

void readFromFile()
{
	string file_name, line;
	cout << "Please enter filename to read from: ";
	cin >> file_name;

	ifstream file(file_name);

	if (file.good())
	{
		getline(file, line);
		int num = stoi(line);
		int *nums = new int[num];
		vector<int> arr(num);
		int size, val;

		// read N number of arrays
		for (int i = 0; i < num; ++i)
		{
			file >> size;
			vector<int> arr(size);

			for (int i = 0; i < size; ++i)
			{
				file >> val;
				arr.push_back(val);
			}

			cout << count_inversions(arr) << endl;
		}
	}

	file.close();
}