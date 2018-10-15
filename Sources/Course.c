//
// Created by daniel on 11/24/2017.
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "../Headers/Course.h"
#include "../Headers/HelperFuncs.h"



///=============STATIC FUNCTIONS===========###START

static CourseResult HandleId(Course course1 , char * id){
    course1->id = malloc(strlen(id)+1);                                               ///handling id
    if (!course1->id) {
        free(course1);
        return COURSE_MEMORY_ERROR;
    }
    strcpy(course1->id, id);
    return COURSE_OK;
}


static CourseResult HandleName(Course course1 ,char *name){
    course1->name = malloc(strlen(name)+1);                                           ///handling name
    if (!course1->name) {
        free(course1->id);
        free(course1);
        return COURSE_MEMORY_ERROR;
    }
    strcpy(course1->name, name);
    return COURSE_OK;
}

///=============STATIC FUNCTIONS===========###END


CourseResult createCourse(char *id, char *name, double credits, Course *course) {
    assert(id != NULL && name != NULL && course != NULL);                                ///assert none of the parmeters are NULL
    CourseResult result;
    if (credits < 0) {
        return COURSE_ILLEGAL_PARAMETER;
    }
    Course new_course = malloc(sizeof(*new_course));                                     ///create new struct
    if (!new_course) {
        return COURSE_MEMORY_ERROR;
    }
    result=HandleId(new_course , id);
    if(result!=COURSE_OK){
        return result;
    }
    /*  new_course->id = malloc(strlen(id)+1);                                               ///handling id
      if (!new_course->id) {
          free(new_course);
          return COURSE_MEMORY_ERROR;
      }
      strcpy(new_course->id, id);
    */
    result=HandleName(new_course , name);
    if(result!=COURSE_OK){
        return result;
    }
    /* new_course->name = malloc(strlen(name)+1);                                           ///handling name
     if (!new_course->name) {
         free(new_course->id);
         free(new_course);
         return COURSE_MEMORY_ERROR;
     }
     strcpy(new_course->name, name);*/

    new_course->preCourses=createDynamicArray();
    assert(new_course->preCourses!=NULL);
    new_course->credits = credits;
    *course=new_course;
    return COURSE_OK;
}

int coursesEqualId(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);

    return strcmp(course1->id, course2->id) == 0 ? 1 : 0;
}

int courseLessThan(Course course1, Course course2){
    assert(course1!=NULL && course2!=NULL);
    return  strcmp(course1->id,course2->id) < 0 ? 1 : 0 ;
}

CourseResult courseUpdateName(Course course1, char *new_name){ // not finished
    assert(new_name!=NULL);
    char   *old_name=malloc(strlen(new_name)+1);
    if ( old_name == NULL) {
        return COURSE_MEMORY_ERROR;
    }
    free(course1->name);
    strcpy(old_name,new_name);
    course1->name=old_name;
    return COURSE_OK;
}


CourseResult addPreCourse(Course course1, Course course2){
    assert(course1 != NULL && course2 != NULL);
    if (coursesEqualId( course1 , course2 )){
        return COURSE_THE_SAME_COURSE;
    }
    HelpResult result= addSortedCourse(course1->preCourses, (Element) course2);
    if (result == HELPER_ALREADY_EXISTS){
        return COURSE_ALREADY_EXISTS;
    }
    return COURSE_OK;
}


CourseResult removePreCourse(Course course1, Course course2){
    assert(course1 != NULL && course2 != NULL);
    HelpResult result= removeElementFromDA(course1->preCourses, (Element) course2);
    if ( result == HELPER_NOT_EXIST){
        return COURSE_NOT_EXIST;
    }
    return COURSE_OK;
}

void displayCourse(Course course1){ // NEED TO VERIFY THE SPACES :: israel said that like this is ok
    int len= course1->preCourses->len;
    printWithoutSpaces(course1->id);
    printf(" ");
    printf("%s",course1->name);
    printf(" ");
    printf("%.1f" , course1->credits);
    if(len>0) {
        printf(" ");
    }
    for (int i = 0; i < len; ++i) {
        printWithoutSpaces(course1->preCourses->elements[i]->id);
        if(i == len-1){
            break;
        }
        printf(" ");
    }
}

void destroyCourse(Course course1){
    free(course1->name);
    free( course1->id);
    destroyDynamicArray(course1->preCourses);
    free(course1);
}




