#include <stdlib.h>
#include <stdio.h>
#include "ordered_records.h"
#include "unity.h"
#include <string.h>


#define INITIAL_CAPACITY 6

OrderedArray *ordered_array_create(int (*compar)(const void*, const void*)){
	if(compar == NULL){
		fprintf(stderr,"ordered_array_create: compar parameter cannot be NULL");
    	exit(EXIT_FAILURE);
	}

	OrderedArray *ordered_array = (OrderedArray *)malloc(sizeof(OrderedArray));

	if(ordered_array == NULL){
		fprintf(stderr, "ordered_array_create: unable to allocate memory for the ordered array");
    	exit(EXIT_FAILURE);
	}

	ordered_array->base = (void**)malloc(INITIAL_CAPACITY*sizeof(void*));

	if(ordered_array->base == NULL){
    	fprintf(stderr, "ordered_array_create: unable to allocate memory for the internal array");
    	exit(EXIT_FAILURE);
  	}

  	ordered_array->nitems = 0;
  	ordered_array->size = INITIAL_CAPACITY;
  	ordered_array->compar = compar;

  	return ordered_array;
}


void* ordered_array_get(OrderedArray *ordered_array, unsigned long i){
  if(ordered_array == NULL){
    fprintf(stderr,"ordered_array_get: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(i>=ordered_array->nitems){
    fprintf(stderr,"ordered_array_get: Index %lu is out of the array bounds",i);
    exit(EXIT_FAILURE);
  }
  return(ordered_array->base)[i];
}

void ordered_array_free_memory(OrderedArray *ordered_array){
  if(ordered_array == NULL){
    fprintf(stderr,"ordered_array_free_memory: ordered_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(ordered_array->base);
  free(ordered_array);
}

void fusion_array(void **base, size_t left, size_t mid, size_t right, int (*compar)(const void*, const void*)) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = 0;

    size_t size = right - left + 1;
    void **temp = malloc(size * sizeof(void *));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }

    while (i <= mid && j <= right) {
      if (compar(base[i], base[j]) <= 0) {
          temp[k] = base[i];
          i++;
      }else {
          temp[k] = base[j];
          j++;
      }
      k++;
    }

    while (i <= mid) {
        temp[k++] = base[i++];
    }

    while (j <= right) {
        temp[k++] = base[j++];
    }

    for (size_t m = 0; m < size; m++) {
        base[left + m] = temp[m];
    }

    free(temp);
}

void merge_sort_rec(void **base, size_t left, size_t right, int (*compar)(const void*, const void*)) {
    if (left < right) {
        size_t mid = (right + left) / 2;

        merge_sort_rec(base, left, mid, compar);
        merge_sort_rec(base, mid + 1, right, compar);

        fusion_array(base, left, mid, right, compar);
    }
}

void merge_sort(void **base, size_t nitems, int (*compar)(const void*, const void*)) {
    if (nitems > 1) {
        merge_sort_rec(base, 0, nitems - 1, compar);
    }
}


void quick_sort_rec(void **base, size_t nitems, int (*compar)(const void*, const void*)){

  if(nitems <= 1){
    return;
  }

  size_t index_rand = (size_t) rand() % nitems;
  void *pivot = base[index_rand];
  base[index_rand] = base[0];
  base[0] = pivot;
  
  void **tempLeft = malloc(nitems*sizeof(void *));
  void **tempRight = malloc(nitems*sizeof(void *));
  size_t k = 0;
  size_t j = 0;

  for(size_t i = 1; i < nitems; i++){
    if(compar(base[i],pivot) < 0){
      tempLeft[k] = base[i];
      k++;
    }else{
      tempRight[j] = base[i];
      j++;
    }
  }

  quick_sort_rec(tempLeft, k, compar);
  quick_sort_rec(tempRight, j, compar);

  for(size_t i = 0; i < k; i++){
    base[i] = tempLeft[i];
  }

  base[k] = pivot;

  for(size_t i = 0 ; i < j; i++){
    base[k+1+i] = tempRight[i];

  }

  free(tempLeft);
  free(tempRight);
}

void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*)){
  if(nitems > 1){
    quick_sort_rec(base,nitems, compar);
  }
}




