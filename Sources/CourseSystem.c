//
// Created by daniel on 11/30/2017.
//

#include "../Headers/CourseSystem.h"
#include "../Headers/HelperFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
///=============STATIC FUNCTIONS===========###START
static SysResult HandlName(CourseSystem sys  , char *name) {                             ///handling name
  sys->name = malloc(strlen(name) + 1);
  if (sys->name == NULL) {
    free(sys);
    return SYS_MEMORY_PROBLEM;
  }
  strcpy(sys->name,name);
  return  SYS_OK;
}


static SysResult HandleSysCourses(CourseSystem sys ){
  sys->courses=createDynamicArray();
  if (sys->courses == NULL){
    free(sys->name);
    free(sys);
    return SYS_MEMORY_PROBLEM;
  }
  return SYS_OK;
}
///=============STATIC FUNCTIONS===========###END

CourseSystem createSystem(char *name){
  CourseSystem new_sys = malloc(sizeof(*new_sys));
  if ( new_sys == NULL){
    return NULL;
  }
 /* new_sys->name = malloc(strlen(name)+1);
  if (new_sys->name == NULL){
    free(new_sys);
    return NULL;
  }
  strcpy(new_sys->name,name);
  new_sys->courses=createDynamicArray();
  if (new_sys->courses == NULL){
    free(new_sys->name);
    free(new_sys);
    return NULL;
  }*/
  SysResult result=HandlName(new_sys, name);
  if (result!=SYS_OK){
    return  NULL;
  }
  result=HandleSysCourses(new_sys);
  if (result!=SYS_OK) {
    return NULL;
  }
  return new_sys;
}


int sysNumCourses(CourseSystem sys){
  assert( sys != NULL);
  return sys->courses->len;
}


SysResult sysAddCourse(CourseSystem sys, Course c1){
  assert( sys != NULL && c1 != NULL);
  HelpResult result1= addSortedCourse(sys->courses, (Element) c1);
  if ( result1 == HELPER_ALREADY_EXISTS){
    return SYS_COURSE_ALREADY_EXIST;
  }
  if ( result1 == HELPER_MEMORY_ERROR){
    return SYS_MEMORY_PROBLEM;
  }
  return SYS_OK;
}


SysResult sysRemoveCourse(CourseSystem sys, char *course_id){
  assert( sys != NULL && course_id !=NULL);
  HelpResult result;
  Element element= getCourse(sys->courses, course_id);
  if (!element){
    return SYS_NOT_IN_SYSTEM;
  }
  updateSysAfterCourseRemove(sys, element);
  result=removeElementFromDA(sys->courses, element);
  assert(result==HELPER_OK);
  //updateSysAfterCourseRemove(sys, element);
  destroyCourse((Course)element);
  if(result==HELPER_OK){            ///this line is for the compiler
    return SYS_OK;
  }
  return SYS_OK;
}


SysResult sysIsPreCourse(CourseSystem sys, char *course_id1 , char *course_id2, int *ans){
  assert(sys != NULL && course_id1 !=NULL && course_id2!=NULL && ans!=NULL);
  Element course1= getCourse(sys->courses, course_id1);
  Element course2= getCourse(sys->courses, course_id2);
  if ( course1== NULL || course2 == NULL ){
    return SYS_NOT_IN_SYSTEM;
  }
  Element result= getCourse(course1->preCourses, course_id2);
  if (!result){
    *ans=0;
    return SYS_OK;
  }
  *ans=1;
  return SYS_OK;
}


SysResult sysAddPreCourse(CourseSystem sys, char *course_id1 , char *course_id2){
  assert(sys != NULL && course_id1 !=NULL && course_id2!=NULL );
  Element course1= getCourse(sys->courses, course_id1);
  Element course2= getCourse(sys->courses, course_id2);
  if ( course1== NULL || course2 == NULL ){
    return SYS_NOT_IN_SYSTEM;
  }
  int ans;
  sysIsPreCourse(sys , course_id1 , course_id2 , &ans);
  if (ans){
    return SYS_ALREADY_PRE_COURSE;
  }
  CourseResult result1=addPreCourse(course1 , course2);
  if ( result1 == COURSE_THE_SAME_COURSE){////THIS IS SPECIAL CASE NOT SPECIFIED ANYWHERE
    return  SYS_NOT_PRE_COURSE;
  }
  if ( result1 == COURSE_MEMORY_ERROR ){
    return  SYS_MEMORY_PROBLEM;
  }
  return  SYS_OK;
}


SysResult sysRemovePreCourse(CourseSystem sys, char *course_id1 , char *course_id2){
  assert(sys != NULL && course_id1 !=NULL && course_id2!=NULL );
  Element course1= getCourse(sys->courses, course_id1);
  Element course2= getCourse(sys->courses, course_id2);
  if ( course1== NULL || course2 == NULL ){
    return SYS_NOT_IN_SYSTEM;
  }
  int ans;
  sysIsPreCourse(sys , course_id1 , course_id2 , &ans);
  if (!ans ){
    return SYS_NOT_PRE_COURSE;
  }
  removeElementFromDA(course1->preCourses, course2); //add assert
    return  SYS_OK;
}

SysResult sysUpdateCourseName(CourseSystem sys, char *course_id, char *new_name){
  assert(sys != NULL && course_id !=NULL && new_name!=NULL );
  Element course= getCourse(sys->courses, course_id);
  if (!course ){
    return SYS_NOT_IN_SYSTEM ;
  }
 CourseResult result=courseUpdateName(course , new_name);
  if ( result == COURSE_MEMORY_ERROR){
    return SYS_MEMORY_PROBLEM;
  }
  return  SYS_OK;
}

void displaySystem(CourseSystem sys) {
  assert(sys != NULL);
  printf("%s\n", sys->name);
  for (int i = 0; i < sys->courses->len; ++i) {
    displayCourse(sys->courses->elements[i]);
    printf("\n");
  }
}


void destroySystem(CourseSystem sys){
  assert(sys!=NULL);
  for (int i = 0; i < sys->courses->len; ++i) {
    //sysRemoveCourse(sys,sys->courses->elements[i]->id);
    destroyCourse(sys->courses->elements[i]);
  }
  destroyDynamicArray(sys->courses);
  free(sys->name);
  free(sys);
}
