/*
 ============================================================================
 Aufgabe     : Datenstrukturen - Woche 4
 Autor       :
 Matrikel    :
 Version     :
 ============================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include "dhbwstudentlist.h"
#include "dhbwstudent.h"
#include <string.h>


//DIESE METHODEN NICHT AENDERN

StudentLP StudentLPAlloc(Student_p newStudent) {

    StudentLP newStudentLP = malloc(sizeof(StudentL));

    newStudentLP->student = newStudent;
    newStudentLP->next = NULL;

    return newStudentLP;
}

void StudentLInsertFirst(StudentLP *anchor_adr, Student_p newStudent) {
    StudentLP oldFirst = *anchor_adr;
    StudentLP newFirst = StudentLPAlloc(newStudent);
    *anchor_adr = newFirst;
    newFirst->next = oldFirst;
}

void StudentLInsertLast(StudentLP *anchor_adr, Student_p newStudent) {

    StudentLP current = *anchor_adr;
    StudentLP previous = NULL;

    StudentLP newLP = StudentLPAlloc(newStudent);

    while (current != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous != NULL) {
        previous->next = newLP;
    } else {
        *anchor_adr = newLP;
    }

}

int StudentLSize(StudentLP *anchor_adr) {

    StudentLP current = *anchor_adr;

    int size = 0;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}

void StudentLPFree(StudentLP info) {
    if (info == NULL)
        return;

    StudentFree(info->student);
    free(info);
    return;
}

void StudentLFree(StudentLP *anchor_adr) {

    StudentLP current = *anchor_adr;

    while (current) {
        StudentLP newCurrent = current->next;
        StudentLPFree(current);
        current = newCurrent;
    }

    *anchor_adr = NULL;
    return;
}

StudentLP deepLPCopy(StudentLP info) {
    if (info == NULL)
        return NULL;
    StudentLP copy = StudentLPAlloc(deepCopy(info->student));
    copy->next = NULL;
    return copy;
}

StudentLP* deepLCopy(StudentLP *anchor_adr) {
    if (anchor_adr == NULL)
        return NULL;

    StudentLP *copy = malloc(sizeof(StudentLP));
    *copy = NULL;

    StudentLP current = *anchor_adr;

    while (current) {
        StudentLInsertLast(copy, deepCopy(current->student));
        current = current->next;
    }

    return copy;
}

StudentLP* StudentsFromFile(char *filename) {

    FILE *in = fopen(filename, "r");

    char string[BUF_SIZE];
    StudentLP *all_students = malloc(sizeof(StudentLP));
    *all_students = NULL;
    StudentLP reverse_students_anchor = NULL;
    StudentLP *reverse_students = &reverse_students_anchor;

    while (fgets(string, BUF_SIZE, in)) {

        //remove newline (works for both windows and unix)
        string[strcspn(string, "\r\n")] = 0;

        //printf("%s\n", string);
        StudentLInsertFirst(reverse_students, StudentAlloc(string));
    }

    //create normal ordered list
    {
        StudentLP current = *reverse_students;
        while (current != NULL) {
            StudentLInsertFirst(all_students, deepCopy(current->student));
            current = current->next;
        }
    }

    StudentLFree(reverse_students);

    return all_students;
}

StudentLP* ArrayToStudentL(Student_p *array, int count, bool doDeepCopy) {

    StudentLP* list = malloc(sizeof(StudentLP));
    *list=NULL;

    for(int i = count -1; i >= 0; i--) {
        if(doDeepCopy) {
            StudentLInsertFirst(list, deepCopy(array[i]));
        }
        else {
            StudentLInsertFirst(list, array[i]);
        }
    }
    return list;
}

Student_p *StudentLToArray(StudentLP *anchor_adr, int *outcount, bool doDeepCopy) {

    *outcount = StudentLSize(anchor_adr);

    Student_p * array = calloc(*outcount, sizeof(Student_p));

    StudentLP current = *anchor_adr;
    int i = 0;
    while (current != NULL) {
        if(doDeepCopy) {
            array[i] = deepCopy(current->student);
        }
        else {
            array[i] = current->student;
        }
        current = current->next;
        i++;
    }

    return array;
}

//Bis hier nicht aendern



//Ab hier Aufgaben

bool StudentLImplemented() {
    //TODO: hier auf true aendern, damit Ihre Implementierung getestet wird
    return false;
}

bool StudentLContainsStudent(StudentLP *anchor_adr, Student_p student) {
    StudentLP temp = *anchor_adr; //points at first list element

    while(temp != NULL) {
        if (StudentEquals(student, temp->student)) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void StudentLPrint(StudentLP *anchor_adr) {
    StudentLP temp = *anchor_adr; //points at first list element

    while(temp != NULL) {
        printf("%d#%s\n", temp->student->matrnr, temp->student->lastname);
        temp = temp->next;
    }
}

StudentLP StudentLExtractStudent(StudentLP *anchor_adr, Student_p student) {
    StudentLP temp = *anchor_adr; //points at first list element
    StudentLP last = *anchor_adr; //one behind temp after checking first element

    //if list is not empty
    if(temp != NULL) {
        //if first element is to be removed, let anchor point at the next element
        if (StudentEquals(student, temp->student)) {
            *anchor_adr = temp->next;
            return temp;
        }
        //if the first element is not to be removed, move temp to the second element
        temp = temp->next;
    } else {
        return NULL;
    }
    //last now points at the first element, temp points at the second

    while(temp != NULL) {
        if (StudentEquals(student, temp->student)) {
            last->next = last->next->next;
            return temp;
        }
        temp = temp->next;
        last = last->next;
    }

    return NULL;
}

StudentLP StudentLFindStudent(StudentLP *anchor_adr, Student_p student) {
    StudentLP temp = *anchor_adr;

    while(temp != NULL) {
        if (StudentEquals(student, temp->student)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

StudentLP StudentLFindByMatr(StudentLP *anchor_adr, int matrnr) {
    StudentLP temp = *anchor_adr;

    while(temp != NULL) {
        if (temp->student->matrnr == matrnr) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

StudentLP StudentLFindByName(StudentLP *anchor_adr, char *lastname) {
    StudentLP temp = *anchor_adr;

    while(temp != NULL) {
        if (strcmp(temp->student->lastname, lastname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void StudentLInsertSorted(StudentLP *anchor_adr, Student_p newStudent) {
//aufsteigend
    StudentLP temp = *anchor_adr;
    StudentLP last = *anchor_adr;

    StudentLP newStudentLP = StudentLPAlloc(newStudent);

    //if list is not empty
    if(temp != NULL) {
        //if first element is larger
        if (newStudent->matrnr < temp->student->matrnr) {
            *anchor_adr = newStudentLP;
            newStudentLP->next = temp;
        }
        //if new element is not smaller than the first, let temp point to second element
        temp = temp->next;
    } else {
        //if list is empty, make new element first element
        *anchor_adr = newStudentLP;
    }


    while(temp != NULL) {
        //if new element is larger, advance to the next element
        if (newStudent->matrnr > temp->student->matrnr) {
            temp = temp->next;
            last = last->next;
            //if new element is smaller, add it before the current
        } else {
            last->next = newStudentLP;
            newStudentLP->next = temp;
            return;
        }

    }

}

