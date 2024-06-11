/*
 ============================================================================
 Aufgabe     : Datenstrukturen - Woche 5
 Autor       : Lukas Lanzner
 Matrikel    :
 Version     : 0.1
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include "dhbwstudent.h"
#include "dhbwstudenttree.h"

//DIESE METHODEN NICHT AENDERN

StudentTP StudentTPAlloc(Student_p newStudent) {
    StudentTP newStudentTP = malloc(sizeof(StudentT));

    newStudentTP->student = newStudent;
    newStudentTP->lchild = NULL;
    newStudentTP->rchild = NULL;

    return newStudentTP;
}


void StudentTPFree(StudentTP tree) {
    if (tree == NULL)
        return;

    StudentFree(tree->student);
    free(tree);
    return;
}

void StudentTFree(StudentTP *root_adr) {

    StudentTP current = *root_adr;

    if (current == NULL) {
        return;
    }
    StudentTFree(&(current->lchild));
    StudentTFree(&(current->rchild));

    StudentTPFree(current);
    return;
}

StudentTP deepTPCopy(StudentTP info) {
    if (info == NULL)
        return NULL;
    StudentTP copy = StudentTPAlloc(deepCopy(info->student));
    copy->lchild = NULL;
    copy->rchild = NULL;
    return copy;
}



//Bis hier nicht �ndern



//Ab hier Aufgaben



bool StudentTImplemented() {
    return true;
}

bool StudentTContainsStudent(StudentTP *root_adr, Student_p student) {
    StudentTP node = *root_adr;
    if (node == NULL) return false;
    if (node->student == NULL) return false;

    if (node->student->matrnr == student->matrnr)
        return true;

    bool res_left = StudentTContainsStudent(&node->lchild, student);
    if (res_left)
        return true;

    return StudentTContainsStudent(&node->rchild, student);
}

StudentTP StudentTFindByMatr(StudentTP *root_adr, int matrnr) {
    StudentTP node = *root_adr;
    if (node == NULL) return NULL;
    if (node->student == NULL) return NULL;

    if (node->student->matrnr == matrnr)
        return node;

    StudentTP res_left = StudentTFindByMatr(&node->lchild, matrnr);
    if (res_left != NULL)
        return res_left;

    return StudentTFindByMatr(&node->rchild, matrnr);
}

StudentTP StudentTFindByName(StudentTP *root_adr, char *lastname) {
    StudentTP node = *root_adr;
    if (node == NULL) return NULL;
    if (node->student == NULL) return NULL;

    if (!strcmp(node->student->lastname, lastname))
        return node;

    StudentTP res_left = StudentTFindByName(&node->lchild, lastname);
    if (res_left != NULL)
        return res_left;

    return StudentTFindByName(&node->rchild, lastname);
}

void addTtoSortedList(StudentTP* root_adr, StudentLP* result){
    StudentTP current = *root_adr;
    if(current == NULL)return;

    addTtoSortedList(&(current->lchild),result);
    StudentLInsertLast(result, deepCopy(current->student));
    addTtoSortedList(&(current->rchild), result);
}

StudentLP* StudentTToSortedList(StudentTP* root_adr) {
    StudentLP* result = malloc(sizeof (StudentLP));
    *result = NULL;
    addTtoSortedList(root_adr,result);
    return result;
}

void StudentTInsertSorted(StudentTP *root_adr, Student_p newStudent) {
    StudentTP node = *root_adr;

    if (node == NULL) {
        (*root_adr) = StudentTPAlloc(newStudent);
        return;
    }

    // check for collisions
    if (newStudent->matrnr == node->student->matrnr)
        return;

    // figure out whether to insert at right or left node
    if (newStudent->matrnr < node->student->matrnr) {
        StudentTInsertSorted(&node->lchild, newStudent);
    } else {
        StudentTInsertSorted(&node->rchild, newStudent);
    }
}

int StudentTSize(StudentTP *root_adr) {
    if (*root_adr == NULL) {
        return 0;
    }

    StudentTP node = *root_adr;

    int left_size = StudentTSize(&node->lchild);
    int right_size = StudentTSize(&node->rchild);

    return 1 + left_size + right_size;
}

int StudentTDepth(StudentTP *root_adr) {
    if (*root_adr == NULL) {
        return 0;
    }

    StudentTP node = *root_adr;

    int left_depth = StudentTDepth(&node->lchild);
    int right_depth = StudentTDepth(&node->rchild);

    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}


