/*
 ============================================================================
 Aufgabe     : Sortieren
 Autor       : koetter
 Matrikel    : DIESE DATEI NICHT AENDERN
 Version     : DIESE DATEI NICHT AENDERN
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dhbwstudent.h"
#include "dhbwstudentlist.h"
#include "dhbwstudenttree.h"


#ifndef DHBWSORTMERGE_H_
#define DHBWSORTMERGE_H_


//Auf true setzen, damit Array-MergeSort getestet wird
bool MergeSortArrayImplemented();
//MergeSort mit Array
void MergeSortArray(Student_p *array, int count);
void mergeSort(Student_p *array, Student_p *temp, int left, int right);
void merge(Student_p *array, Student_p *temp, int left, int mid, int right);


//Auf true setzen, damit Listen-MergeSort getestet wird
bool MergeSortListImplemented();
//MergeSort mit Liste
void MergeSortList(StudentLP *anchor_adr);
StudentLP mergeLists(StudentLP l1, StudentLP l2);
void splitList(StudentLP source, StudentLP *front, StudentLP *back);

#endif /* DHBWSORTMERGE_H_ */
