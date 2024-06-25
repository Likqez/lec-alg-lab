/*
 ============================================================================
 Aufgabe     : Sortieren - Woche 7
 Autor       :
 Matrikel    :
 Version     :
 ============================================================================
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dhbwsortsimple.h"

//Ab hier Aufgaben


//Auf true setzen, damit BubbleSort getestet wird
bool BubbleSortImplemented() {
	return true;
}

void swap(Student_p *a, Student_p *b) {
    Student_p temp = *a;
    *a = *b;
    *b = temp;
}

//BubbleSort
void BubbleSortArray(Student_p *array, int count) {
    bool swapped;

    for (int i = 0; i < count; ++i) {
        swapped = false;
        for (int j = 0; j < (count - 1); ++j) {
            if (array[j]->matrnr > array[j + 1]->matrnr) {
                swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }

}


//Auf true setzen, damit SelectionSort getestet wird
bool SelectionSortImplemented() {
	return true;
}

//SelectionSort
void SelectionSortArray(Student_p *array, int count) {
    for (int i = 0; i < (count - 1); i++) {
        int minIndex = i;
        for (int j = (i + 1); j < count; j++) {
            if (array[j]->matrnr < array[minIndex]->matrnr) {
                minIndex = j;
            }
        }
        swap(&array[i], &array[minIndex]);
    }
}

