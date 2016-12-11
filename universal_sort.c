#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Comparison)(void* a, void* b);

/* Returns a positive int if a > b, negative int if b > a, zero if equal
 * Arguments:
 * a:       A pointer to the first element for comparison.
 * b:       A pointer to the second element for comparison.
 */
int compare_int(void* a, void* b){
	return *(int*)a - *(int*)b;
}

/* This swaps two elements in an array.
 * Arguments:
 * size:    The size of every element in the array.
 * index_a: The index of the first element to be swapped.
 * index_b: The index of the second element to be swapped.
 * array:   The array to be sorted.
 */
void swap(int size, int index_a, int index_b, void* array){
	void* temp = malloc(size); //Free later
	memcpy(temp, array + (index_a * size), size);
	memcpy(array + (index_a * size), array + (index_b * size), size);
	memcpy(array + (index_b * size), temp, size);
	free(temp);
}

/* This is where the actual sorting is done.
 * Arguments:
 * n:       Number of elements in the array.
 * size:    The size of every element in the array.
 * compare: A pointer to the function to compare elements of the array.
 * array:   The array to be selection sorted.
 */
void* selection_sort(int n, int size, Comparison compare, void* array){
	int i;
	for(i = 0; i < n; i++){
		int j;
		int index_min = i;
		for(j = i; j < n; j++){
			if(compare(array + (j * size), array + (index_min * size)) < 0){
				index_min = j;
			}
		}
		swap(size, i, index_min, array);
	}
	return array;
}

int main(int argc, char** argv){
	int array[] = {6, 5, 3, 2, 7, 0, 4, 3};
	selection_sort(8, sizeof(int), compare_int, (void*) array);
	return 0;
}

