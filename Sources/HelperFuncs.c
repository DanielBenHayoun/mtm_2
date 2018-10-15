//
// Created by daniel on 12/1/2017.
//


#include "../Headers/HelperFuncs.h"
#include <assert.h>



static  HelpResult insert(DynamicArray da , Element element){
  DAResult result1;
  int i;
  for (i = 0; i < da->len; ++i) {                         ///finding the right element
    if (strcmp(da->elements[i]->id, element->id) > 0) {
      break;
    }
  }
  if (i == 0) {                                           ///case 1: the given element is the smallest in the array
    result1=addElementStart(da, element);
    if (result1==DA_OK) {
      return HELPER_OK;
    }
  }
  if ( i == da->len){                                     ///case extreme : the given element is the biggest in the array
    result1=addElementEnd(da, element);
    if (result1==DA_OK) {
      return HELPER_OK;
    }
  }
  result1=addElementBefore(da, element, i);               /// case 2 :   normal
 /* if (result1== DA_MEMORY_ERROR){
    return HELPER_MEMORY_ERROR;
  } */
  assert(result1==DA_OK);                                 /// the only intresting return value is    DA_MEMORY_ERROR
  return HELPER_OK;

}

void printWithoutSpaces( char *string){
  for (int i = 0; string[i]!='\0' ; ++i) {
    if (string[i]== ' '){
      continue;
    }
    printf("%c" , string[i]);
  }
}


HelpResult  addSortedCourse(DynamicArray da, Element element) {
  int result;
 indexOfElement(da, element, 0, &result);           ///it doesn`t metter what the return value from indexOfElement
  if ( result!= -1 ) {                              /// because we send 0 as base_index anyway. if we get back DA_ILLEGAL_INDEX
    return HELPER_ALREADY_EXISTS;                   /// it means that the array is empty! and it`s OK.
  }
/*  int i;
  for (i = 0; i < da->len; ++i) {
    if (strcmp(da->elements[i]->id, element->id) > 0) {
      break;
    }
  }
  if (i == 0) {
    result1=addElementStart(da, element);
    if (result1==DA_OK) {
      return HELPER_OK;
    }
  }
  if ( i == da->len){                       ///case extreme
    result1=addElementEnd(da, element);
    if (result1==DA_OK) {
      return HELPER_OK;
    }
  }
  result1=addElementBefore(da, element, i);
  if (result1==DA_OK) {
    return HELPER_OK;
  }
  if (result1== DA_MEMORY_ERROR){
    return HELPER_MEMORY_ERROR;
  }*/
  return insert(da ,element);
}

HelpResult removeElementFromDA(DynamicArray da, Element element){
  int index;
  indexOfElement( da, element , 0 , &index);
  if ( index == -1){
  return  HELPER_NOT_EXIST;
  }
  DAResult result=removeElement( da , index);
  if ( result != DA_OK){
  return HELPER_NOT_EXIST;
  }
  return HELPER_OK;
}

Element getCourse(DynamicArray da, char *id){
  for (int i = 0; i < da->len; ++i) {
    if (strcmp(da->elements[i]->id, id) == 0) {
      return da->elements[i];
    }
  }
  return NULL;
}

void updateSysAfterCourseRemove(CourseSystem sys, Element course){
  int ans=-1;
  int index=-2;
  for (int i = 0; i < sys->courses->len; ++i) {
   sysIsPreCourse(sys , sys->courses->elements[i]->id , course->id ,&ans );
    if ( ans==1){
      indexOfElement(sys->courses->elements[i]->preCourses,  course , 0 , &index);

      removeElement(sys->courses->elements[i]->preCourses , index);

    }
  }
}