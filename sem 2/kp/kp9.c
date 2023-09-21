//метод простой вставки
//целый 4 отдельно 12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 50

typedef struct {
    int key;
    char data[30];
} element;

void swap(element *x, element *y) {
    element temp = *x;
    *x = *y;
    *y = temp;
}

void downheap(element a[], int i, int n) {
    int k = i, j = 2*k;
    while (j <= n) {
        if (j < n && a[j].key < a[j+1].key)
            j++;
        if (a[k].key >= a[j].key)
            break;
        swap(&a[k], &a[j]);
        k = j;
        j = 2*k;
    }
}

void heap_sort(element a[], int n) {
    int i;
    for (i = n/2; i > 0; i--)
        downheap(a, i, n);
    for (i = n-1; i > 0; i--) {
        swap(&a[1], &a[i+1]);
        downheap(a, 1, i);
    }
}
//бинарный поиск
int binsearch(element a[], int n, int key) {
    int low = 0, high = n-1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (key == a[mid].key)
            return mid;
        else if (key < a[mid].key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

void print_list(element a[], int n) {
    int i;
    printf("\n[ Key  |     Data ]\n");
    for (i = 0; i < n; i++)
    printf("[ %4d | %-10s ]\n", a[i].key, a[i].data);
}

int main() {
    int i, n, key, result;
    element a[MAX_ELEMENT];
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n < 12) {
        printf("Error: Minimum number of elements is 12.\n");
        exit(1);
    }

//ввод данных
printf("\nEnter the elements with their keys:\n");
for (i = 1; i <= n; i++) {
    printf("Enter data %d: ", i);
    scanf("%s", a[i].data);
    printf("Enter key %d : ", i);
    scanf("%d", &a[i].key);
}

//сортировка
heap_sort(a, n);

//печать сортировки
printf("\nAfter sorting: ");
print_list(a, n);

// Search the data
while (1) {
    printf("\nEnter the key to search (-1 to exit): ");
    scanf("%d", &key);
    if (key == -1)
        break;
    result = binsearch(a, n, key);
    if (result == -1)
        printf("Key not found.\n");
    else
        printf("Key found at index %d.\n[ %4d | %-10s ]\n", result, a[result].key, a[result].data);
}

return 0;
}