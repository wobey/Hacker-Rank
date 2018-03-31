// Author: John Fitzgerald
// Title: Arrays-Left-Rotation.cpp
// Date Modified: 3/30/2018
/* Description: 
A left rotation operation on an array of size N shifts each of the array's elements 1 unit to the left. 
For example, if 2 left rotations are performed on array [1, 2, 3, 4, 5], then the array would become [3,4,5,1,2].

Given an array of N integers and a number, D, perform D left rotations on the array. 
Then print the updated array as a single line of space-separated integers.

Input Format:
The first line contains two space-separated integers denoting the respective values of N (the number of integers) 
and D (the number of left rotations you must perform. The second line contains N space-separated integers describing 
the respective elements of the array's initial state.

Constraints:
- 1 <= N <= 10^5
- 1 <= D <= N
- 1 <= ai <= 10^6

Output Format:
Print a single line of N space-separated integers denoting the final state of the array after performing D left rotations.

Sample Input:
5 4
1 2 3 4 5

Sample Output:
5 1 2 3 4
*/

#include<iostream>
#include<vector>
using namespace std;

// rotates array left k times
vector<int> array_left_rotation(vector<int> a, int n, int k)
{
	int temp;

	// get 0'th index value
	// erase 0'th index
	// insert 0'th index value at end
	for (int i = 0; i < k; ++i)
	{
		temp = a[0];
		a.erase(a.begin());
		a.emplace_back(temp);
	}

	// for (int i = 0; i < n; ++i)
	//     cout << a[i] << " ";
	// cout << endl;

	return a;
}

int main() 
{
	int n;
	int k;
	
	cin >> n >> k;
	vector<int> a(n);

	for (int a_i = 0; a_i < n; a_i++) 
		cin >> a[a_i];

	vector<int> output = array_left_rotation(a, n, k);
	
	for (int i = 0; i < n; i++)
		cout << output[i] << " ";
	cout << endl;
	
	return 0;
}