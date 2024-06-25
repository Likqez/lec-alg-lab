/*
 ============================================================================
 Aufgabe     : Sortieren - Woche 8
 Autor       :
 Matrikel    :
 Version     :
 ============================================================================
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dhbwsortmerge.h"


//Ab hier Aufgaben


//Auf true setzen, damit Array-MergeSort getestet wird
bool MergeSortArrayImplemented() {
	return true;
}
//MergeSort mit Array
void MergeSortArray(Student_p *array, int count) {
    Student_p *temp = (Student_p *)malloc(count * sizeof(Student_p));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    mergeSort(array, temp, 0, count - 1);

    free(temp);
}

void mergeSort(Student_p *array, Student_p *temp, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(array, temp, left, mid);
        mergeSort(array, temp, mid + 1, right);
        merge(array, temp, left, mid, right);
    }
}

void merge(Student_p *array, Student_p *temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (array[i]->matrnr <= array[j]->matrnr) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = array[i++];
    }

    while (j <= right) {
        temp[k++] = array[j++];
    }

    for (i = left; i <= right; i++) {
        array[i] = temp[i];
    }
}




//Auf true setzen, damit Listen-MergeSort getestet wird
bool MergeSortListImplemented() {
	return true;
}
//MergeSort mit Liste
void MergeSortList(StudentLP *anchor_adr) {
    StudentLP head = *anchor_adr;
    StudentLP a, b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    splitList(head, &a, &b);

    MergeSortList(&a);
    MergeSortList(&b);

    *anchor_adr = mergeLists(a, b);
}

StudentLP mergeLists(StudentLP l1, StudentLP l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->student->matrnr < l2->student->matrnr) {
        l1->next = mergeLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeLists(l1, l2->next);
        return l2;
    }
}

void splitList(StudentLP source, StudentLP *front, StudentLP *back) {
    StudentLP slow = source;
    StudentLP fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}




