
#ifndef ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm
#define ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm

/**
 * @struct _OrderedArray
 * @brief An array of any number of elements of any kind, ordered in non-descending order
 *        according to a specific precedence relation.
 * 
 * @var _OrderedArray::base
 * Pointer to the base of the array.
 * @var _OrderedArray::nitems
 * Number of items in the array.
 * @var _OrderedArray::size
 * Size of the array.
 * @var _OrderedArray::compar
 * Pointer to the comparison function that defines the precedence relation.
 */
struct _OrderedArray{
	void** base;
	size_t nitems;
	size_t size;
	int (*compar)(const void*, const void*);
};

typedef struct _OrderedArray OrderedArray;

/**
 * @brief Creates an empty ordered array and returns it.
 * 
 * @param compar Pointer to a function implementing the precedence relation between the array elements.
 *               This function must accept two pointers to elements and return 0 if the first element
 *               does not precede the second one and a non-zero value otherwise.
 *               The input parameter cannot be NULL.
 * 
 * @return Pointer to the created ordered array.
 */
OrderedArray *ordered_array_create(int (*compar)(const void*,const void*));

/**
 * @brief Returns the pointer to the i-th element of the ordered array.
 * 
 * @param array Pointer to an ordered array (cannot be NULL).
 * @param i Index of the element to retrieve (must be a valid position within the ordered array).
 * 
 * @return Pointer to the i-th element of the array.
 */
void* ordered_array_get(OrderedArray *, unsigned long);

/**
 * @brief Frees the memory allocated for the ordered array structure.
 * 
 * @param array Pointer to the ordered array (cannot be NULL).
 *              Note: This function does not free the memory allocated for the array elements.
 *              Freeing that memory is the responsibility of the function where the ordered array was created.
 */
void ordered_array_free_memory(OrderedArray *);

/**
 * @brief Sorts a sub-array using the merge sort algorithm (recursive implementation).
 * 
 * @param base Pointer to the sub-array.
 * @param left Index of the first element of the sub-array.
 * @param right Index of the last element of the sub-array.
 * @param compar Pointer to a function to compare two elements.
 */
void merge_sort_rec(void **base, size_t left, size_t right, int (*compar)(const void*, const void*));

/**
 * @brief Sorts an array using the merge sort algorithm.
 * 
 * @param base Pointer to the array.
 * @param nitems Number of items in the array.
 * @param compar Pointer to a function to compare two elements.
 */
void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));

/**
 * @brief Merges two sub-arrays into a sorted array.
 * 
 * @param base Pointer to the array.
 * @param left Index of the first element of the first sub-array.
 * @param mid Index of the last element of the first sub-array.
 * @param right Index of the last element of the second sub-array.
 * @param compar Pointer to a function to compare two elements.
 */
void fusion_array(void **base, size_t left, size_t mid, size_t right, int (*compar)(const void*, const void*));

/**
 * @brief Sorts an array using the quick sort algorithm.
 * 
 * @param base Pointer to the array.
 * @param nitems Number of items in the array.
 * @param compar Pointer to a function to compare two elements.
 */
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));


/**
 * @brief Recursively sorts a sub-array using the quick sort algorithm.
 * 
 * @param base Pointer to the sub-array.
 * @param nitems Number of items in the sub-array.
 * @param compar Pointer to a function to compare two elements.
 */
void quick_sort_rec(void **base, size_t nitems, int (*compar)(const void*, const void*));


/**
 * @brief Sorts records from an input file and outputs them to an output file.
 * 
 * @param infile Input file containing multiple rows, each with an id, "word", integer, and float value.
 * @param outfile Output file where the sorted rows will be written.
 * @param field Field to determine the sort key.
 * @param algo Algorithm choice to specify the sorting method.
 */
void sort_records(FILE *infile, FILE *outfile, int field, int algo);

#endif /* ORDERED_ARRAY_H_laokjsdnbudjllvfidkfmqm */
