//
// Created by daniel on 12/1/2017.
//

#ifndef MTM_EX2_HELPERFUNCS_H
#define MTM_EX2_HELPERFUNCS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../Headers/CourseSystem.h"
#include "../Headers/Course.h"
#include "../Headers/DynamicArray.h"

typedef enum { HELPER_PROBLEM, HELPER_OK , HELPER_MEMORY_ERROR , HELPER_ILLEGAL_PARAMETER ,
  HELPER_THE_SAME , HELPER_ALREADY_EXISTS , HELPER_NOT_EXIST} HelpResult;

///=========This function gets a string and print it to the screen
/// without spaces ( if there is )
///
void printWithoutSpaces(char *string);

///========This function adds an element to a given DynamicArray ,in lexicographic order
/// return values: 1.HELPER_OK if everything went well
///                2.HELPER_ALREADY_EXISTS  if the given element is already in *this* DynamicArray
HelpResult  addSortedCourse(DynamicArray da, Element element);

///========This function gets an element and DynamicArray , and removes the element from the DynamicArray
///return values: 1. HELPER_NOT_EXIST if the given elemet is not in the array
///               2. HELPER_OK
HelpResult removeElementFromDA(DynamicArray da, Element element);

///======This function gets an DynamicArray and id returns the "element"(Course) that maches the id
///return values: 1. a pointer to the element
///               2. NULL if the element is not in the array
Element getCourse(DynamicArray da, char *id);

///======This function gets an CourseSystem  and Course , and update the system so after we removed a course
/// it will decrease the length of the relevant precourses of  Courses that are in the system
///return values: 1. a pointer to the element
///               2. NULL if the element is not in the array
void updateSysAfterCourseRemove(CourseSystem sys, Element course);




#endif //MTM_EX2_HELPERFUNCS_H
