/*
 ============================================================================
 Aufgabe     : Sortieren - Woche 9
 Autor       :
 Matrikel    :
 Version     :
 ============================================================================
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dhbwsortheap.h"


//Ab hier Aufgaben

//Auf true setzen, damit Heapsort getestet wird
bool HeapSortImplemented() {
    return true;
}

//Hilfsfunktionen

//Lasse kleinen Knoten nach unten sinken
void HeapBubbleDown(Student_p *array, int nodeIndex, int end) {
    int lci = 2 * nodeIndex + 1;  // left child index
    while (lci < end) {  // while node is not a leaf
        int gci = lci;  // greater child index
        int rci = lci + 1;  // right child index

        // Check if right child exists and is greater than left child
        if (rci < end && array[rci]->matrnr > array[lci]->matrnr) {
            gci = rci;
        }

        // If the greater childs value is greater than the nodes value, swap them
        if (array[gci]->matrnr > array[nodeIndex]->matrnr) {
            Student_p temp = array[nodeIndex];
            array[nodeIndex] = array[gci];
            array[gci] = temp;

            // Move down to the greater child
            nodeIndex = gci;
            lci = 2 * nodeIndex + 1;
        } else break;
    }
}

//Stellt Heap-Eigenschaft in einem Array (als Binaerbaum interpretiert) her
void Heapify(Student_p *array, int count) {
    int end = count;
    int last = (end - 1) / 2;
    for (int node = last; node >= 0; node--) {
        HeapBubbleDown(array, node, end);
    }
}


//Heapsort mit Array
void HeapSortArray(Student_p *array, int count) {
    // Turn the array into a max heap
    Heapify(array, count);

    // Swap the first element with the last element of the unsorted part of the array,
    // and bubble down the new first element to its correct position
    for (int i = count - 1; i > 0; i--) {
        // Swap array[0] and array[i]
        Student_p temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Bubble down the new first element
        HeapBubbleDown(array, 0, i);
    }
}

