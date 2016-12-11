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
/* Returns a function with a name matching the input string. Wish C had
 * a better way to do this (ie: reflection). Returns NULL if the function
 * does not exist.
 * Arguments:
 * function_name: Name of the function to return.
 */
void* lookup_function(char* function_name){
	if(!strcmp(function_name, "compare_int")){
		return compare_int;
	}
	return NULL;
}

/* This swaps two elements in an array.
 * Arguments:
 * size:    The size of every element in the array in bytes.
 * index_a: The index of the first element to be swapped.
 * index_b: The index of the second element to be swapped.
 * array:   The array to be sorted.
 */
void swap(int size, int index_a, int index_b, void* array){
	if(index_a != index_b){
		void* temp = malloc(size); //Free later
		memcpy(temp, array + (index_a * size), size);
		memcpy(array + (index_a * size), array + (index_b * size), size);
		memcpy(array + (index_b * size), temp, size);
		free(temp);
	}
}

/* This is where the actual sorting is done.
 * Arguments:
 * n:       Number of elements in the array.
 * size:    The size of every element in the array in bytes.
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

/* Main function. Inputs are accepted as
 * ./universal_sort <function> <size> [element 1] [element 2] [element 3]...
 * Arguments:
 * argc:    Number of strings typed (will be number of elements minus 2).
 * argv:    Array of strings typed. Indices [3-argc] will be array elements.
 * Sub-arguments:
 * function:Name of the function used to compare array elements.
 * size:    The size of every element in the array in bytes.
 */
int main(int argc, char** argv){
	if(!argv[1] || !argv[2]){
		printf("Correct use: ./universal_sort <function> <size> [element 1] [element 2] [element 3]...\n");
		return 1;
	}
	void* function = lookup_function(argv[1]);
	if(!function){
		printf("<function> must be a valid function name.\n");
		return 1;
	}
	int size = atoi(argv[2]);
	if(size == 0){
		printf("<size> must be a valid integer.\n");
		return 1;
	}
	int num_elements = argc - 3;
	void* array = malloc(num_elements * size); //Free later
	int i;
	for(i = 0; i < num_elements; i++){
		*((int*)(array + (i * size))) = atoi(argv[i + 3]);
		//memcpy(array + (i * size), (void*)argv[i + 3], size);
	}
	selection_sort(num_elements, size, function, array);
	printf("Sorted array of %d elements using %s:\n[", num_elements, argv[1]);
	for(i = 0; i < num_elements; i++){
		if(i < num_elements - 1){
			printf("%d, ", *(int*)(array + (i * size))); //This is really janky
		}
		else{
			printf("%d].\n", *(int*)(array + (i * size)));
		}
	}
	free(array);
	return 0;
}

