
#ifndef ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm
#define ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm

//An array of any number of elements of any kind, ordered in non descending order
//according to a specific precedence relation.
struct _OrderedArray{
	void** base;
	size_t nitems;
	size_t size;
	int (*compar)(const void*, const void*);
};

typedef struct _OrderedArray OrderedArray;


//It creates an empty ordered array and returns the created ordered array.
//It accepts as input a pointer to a function implementing the 
//precedence relation between the array elements. 
//Such a function must accept as input two pointers to elements and
//return 0 iff the first element does not precede the second one and
//a number different from zero otherwise.
//The input parameter cannot be NULL.
OrderedArray *ordered_array_create(int (*compar)(const void*,const void*));

//It accepts as input a pointer to an ordered array and an integer "i" and
//it returns the pointer to the i-th element of the ordered array
//The first parameter cannot be NULL; the second parameter must be a valid position 
//within the orderd array.
void* ordered_array_get(OrderedArray *, unsigned long);

//It accepts as input a pointer to an ordered array and 
//it frees the memory allocated to store the ordered array. 
//It does not free the memory allocated to store the array elements,
//since freing that memory is responsibility of the function where
//the ordered array was created.
//The input parameters cannot be NULL.
void ordered_array_free_memory(OrderedArray *);

// Takes a pointer to a sub-array and divides the array using the merge sort algorithm with recursion.
// Also requires the number of items and a comparison function pointer to compare two elements.
void merge_sort_rec(void **base, size_t left, size_t right, int (*compar)(const void*, const void*));

// Takes a pointer to an array and calls the recursive version of the merge sort function.
// Also requires the number of items and a comparison function pointer to compare two elements.
void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));

// Takes a pointer to an array, the indices of the first element, middle, and last element of a sub-array.
// Returns the original array sorted.
void fusion_array(void **base, size_t left, size_t mid, size_t right, int (*compar)(const void*, const void*));

// Takes a pointer to an array, the number of items, and a comparison function pointer.
// Calls the recursive version of the quick sort function.
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));


// Takes a pointer to a sub-array, the number of items, and a comparison function pointer.
// Recursively divides the array into sub-arrays for sorting.
void quick_sort_rec(void **base, size_t nitems, int (*compar)(const void*, const void*));


// Takes an input file with multiple rows where each row contains an id, "word", integer, and float value.
// Accepts a field for determining the sort key and an algorithm choice to specify the sorting method.
// Outputs the rows sorted by the specified field to the output file.
void sort_records(FILE *infile, FILE *outfile, int field, int algo);

#endif /* ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm */
