//
// Created by Dina on 24-Nov-17.
//
#include "../Headers/HelperFuncs.h"
#include "../Headers/DynamicArray.h"
#include "../Headers/Course.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

///=============STATIC FUNCTIONS===========###START

static DAResult push_element(DynamicArray array, int len , Element new_element, int target_index ){
    array->elements =realloc(array->elements,sizeof(Element)*(len+1));
    if (!array->elements){
        return DA_MEMORY_ERROR;
    }
    int i;
    for (i = len; i >target_index ; i--) {
        array->elements[i]=array->elements[i-1];
    }
    array->elements[target_index]=new_element;
    array->len++;
    return DA_OK;
}


///=============STATIC FUNCTIONS===========###END


DynamicArray createDynamicArray(){
    DynamicArray new_dynamic_array = malloc(sizeof(*new_dynamic_array));
    if (!new_dynamic_array){
        return NULL;
    }
    new_dynamic_array->elements = malloc(sizeof(new_dynamic_array->elements));   // creating space for da
   if( new_dynamic_array->elements == NULL){
       free(new_dynamic_array);
       return NULL;
   }
    new_dynamic_array->len=0;
    return new_dynamic_array;
}


DAResult addElementBefore(DynamicArray old_array, Element new_element, int index){
    if (index < 0 || index >= old_array->len || old_array->len == 0){
        return   DA_ILLEGAL_INDEX;
    }
    return push_element(old_array,old_array->len, new_element,index);
}


DAResult addElementStart(DynamicArray old_array, Element new_element){
    return push_element(old_array , old_array->len, new_element , 0);
}


DAResult addElementEnd(DynamicArray old_array, Element new_element){
    int len=old_array->len;
    old_array->elements =realloc(old_array->elements,sizeof(Element)*(len+1));
    if (!old_array->elements){
        return DA_MEMORY_ERROR;
    }
    old_array->elements[len]=new_element;
    old_array->len++;
    return DA_OK;
}

DAResult indexOfElement(DynamicArray da, Element c , int base_index, int *result_index) {
  assert(da != NULL && c != NULL && result_index != NULL);
   if ( base_index < 0 || base_index >= da->len || da->len == 0 ) {
     *result_index = -1;
     return DA_ILLEGAL_INDEX;
   }

    for ( int i=base_index; i<da->len ; i++){
        int result = coursesEqualId( (Course)c , (Course)da->elements[i] );
        if (result == 1){
            *result_index=i;
            return DA_OK;
        }
    }
    *result_index=-1;
    return DA_OK;
}


DAResult removeElement(DynamicArray array, int index){
    if ( index < 0 || index >= array->len) {
        return DA_ILLEGAL_INDEX;
    }
    Element *new_array = malloc(sizeof(Element)*(array->len-1));
    if (new_array == NULL){
        return DA_MEMORY_ERROR;
    }
    int j=0;    //index in new_array
    for (int i = 0; i < array->len; i++) {
        if ( i == index){
            continue;
        }
        new_array[j]=array->elements[i];
        j++;
    }
    array->len--;
    Element *tmp = array->elements;
    array->elements=new_array;
    new_array=tmp;
    free(new_array);

    return DA_OK;
}


DAResult updateElement(DynamicArray da, int id, Element element){
    if ( id < 0 || id >=da->len){
        return DA_ILLEGAL_INDEX;
    }
    da->elements[id]=element;
    return DA_OK;
}


DAResult displayElement(DynamicArray da, int i){
    if ( i < 0 || i >= da->len ){
        return DA_ILLEGAL_INDEX;
    }
    displayCourse((Course)da->elements[i]);
    return DA_OK;
}


void displayAllElements(DynamicArray array){
    for (int i = 0; i < array->len ; i++) {
        displayCourse((Course)array->elements[i]);
        printf("\n");
    }
}


int size(DynamicArray array){
    return array->len;
}


void destroyDynamicArray(DynamicArray array){///check again
    for (int i = 0; i < array->len; ++i) {
        if ( array->elements[i]!=NULL)
            removeElement(array , i);
    }
    free(array->elements);
    free(array);
}

