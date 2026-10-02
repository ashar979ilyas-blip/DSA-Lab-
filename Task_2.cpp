#include<iostream>
#include<string>
using namespace std;

template <typename T>
void printArray(T arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

template<typename T>
void selectionsort(T arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int smallest = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[smallest])
				smallest = j;
		}
		T temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
	}
}

int main() {
	int intArray[5] = { 64, 25, 12, 22, 11 };
	cout << "Original integer array: ";
	printArray(intArray,5);

	selectionsort(intArray,5);
	cout << "Sorted integer array: ";

	printArray(intArray,5);

	string stringArray[4] = { "apple", "orange", "banana", "grape" };
	cout << "\nOriginal string array: ";

	printArray(stringArray,5);

	selectionsort(stringArray,5);
	cout << "Sorted string array: ";

	printArray(stringArray,5);
	return 0;
}

