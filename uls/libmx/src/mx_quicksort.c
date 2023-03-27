#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
  char *pivot;
  char *temp;
  int count = 0;

  if (left < right) {
    pivot = arr[(left + right) / 2];

  while(left < right){
    while(mx_strlen(arr[left]) <= mx_strlen(pivot) && left < right)
      left++;

    while(mx_strlen(arr[right]) > mx_strlen(pivot))
      right--;

    if (left < right){
      temp = arr[left];
      arr[left] = arr[right];
      arr[right] = temp;
      count++;
    }
  }

  temp = arr[left + 1];
  arr[left + 1] = arr[right];
  arr[right] = temp;
  count++;

    mx_quicksort(arr,left, right - 1);
    mx_quicksort(arr,right + 1,right);
  }
  return count;
}
