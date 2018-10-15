/*
 * DynamicArray_test.c
 *
 *  Created on: Nov 18, 2017
 *      Author: 7
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../Headers/DynamicArray.h"
#include "../Headers/Course.h"

void addElements(Course course1,Course course2,Course course3,DynamicArray* arr)
{
	//Checking bad cases
	DAResult result1=addElementBefore(*arr,course1,-1);
	assert(result1==DA_ILLEGAL_INDEX);

	//Checking good cases
	//Adding Atam
	result1=addElementStart((*arr),course2);
	if (result1){
	}
	assert(result1==DA_OK);
	assert((*arr)->len==1);

	assert((*arr)->elements[0]->credits==course2->credits);
	assert(strcmp((*arr)->elements[0]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[0]->name,course2->name)==0);

	//Adding Matam
	result1=addElementEnd(*arr,course1);
	assert(result1==DA_OK);
	assert((*arr)->len==2);

	assert((*arr)->elements[0]->credits==course2->credits);
	assert(strcmp((*arr)->elements[0]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[0]->name,course2->name)==0);

	assert((*arr)->elements[1]->credits==course1->credits);
	assert(strcmp((*arr)->elements[1]->id,course1->id)==0);
	assert(strcmp((*arr)->elements[1]->name,course1->name)==0);

	//Adding Mavo
	result1=addElementBefore(*arr,course3,0);
	assert(result1==DA_OK);
	assert((*arr)->len==3);

	assert((*arr)->elements[0]->credits==course3->credits);
	assert(strcmp((*arr)->elements[0]->id,course3->id)==0);
	assert(strcmp((*arr)->elements[0]->name,course3->name)==0);

	assert((*arr)->elements[1]->credits==course2->credits);
	assert(strcmp((*arr)->elements[1]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[1]->name,course2->name)==0);

	assert((*arr)->elements[2]->credits==course1->credits);
	assert(strcmp((*arr)->elements[2]->id,course1->id)==0);
	assert(strcmp((*arr)->elements[2]->name,course1->name)==0);
    result1=DA_OK;
	//After this the courses are 234114 234118 234122
}

void indexOfElementsTest(DynamicArray arr,Course course1,Course course2,Course course3
		,Course course4)
{
	//Checking bad cases
	int index;
	DAResult result=indexOfElement(arr,course1,-1,&index);
	assert(result==DA_ILLEGAL_INDEX);
	assert(index==-1);

	result=indexOfElement(arr,course1,3,&index);
	assert(result==DA_ILLEGAL_INDEX);
	assert(index==-1);

	//Checking good cases
	//Checking Mavo
	result=indexOfElement(arr,course1,0,&index);
	assert(result==DA_OK);
	assert(index==0);

	//Checking Atam
	result=indexOfElement(arr,course2,0,&index);
	assert(result==DA_OK);
	assert(index==1);

	//Checking Matam
	result=indexOfElement(arr,course3,0,&index);
	assert(result==DA_OK);
	assert(index==2);

	//Checking a non-existent course
	result=indexOfElement(arr,course4,0,&index);
	assert(result==DA_OK);
	assert(index==-1);
}

void updateElementTest(DynamicArray* arr,Course course1,Course course2)
{
	//Checking bad cases
	DAResult result=updateElement(*arr,-1,course1);
	assert(result==DA_ILLEGAL_INDEX);

	result=updateElement(*arr,5,course1);
	assert(result==DA_ILLEGAL_INDEX);

	//Checking good cases
	result=updateElement(*arr,2,course2);
	assert(result==DA_OK);
	assert((*arr)->elements[2]->credits==course2->credits);
	assert(strcmp((*arr)->elements[2]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[2]->name,course2->name)==0);

	result=updateElement(*arr,2,course2);
	assert(result==DA_OK);
}

void displayElementTest(DynamicArray arr)
{
	//Checking bad cases
	DAResult result=displayElement(arr,-1);
	assert(result==DA_ILLEGAL_INDEX);
	result=displayElement(arr,3);
	assert(result==DA_ILLEGAL_INDEX);

	//Checking good cases
	result=displayElement(arr,0);
	assert(result==DA_OK);
	printf("\n");
	//Expected output:234114 Introduction For CS 4

	result=displayElement(arr,1);
	assert(result==DA_OK);
	printf("\n");
	//Expected output:234118 Computer Organization And Programming 3

	result=displayElement(arr,2);
	assert(result==DA_OK);
	printf("\n");
	//Expected output:234122 Introduction To System Programming 3
}

void displayAllElementsTest(DynamicArray arr)
{
	displayAllElements(arr);
	/* Expected output:
	 * 234114 Introduction For CS 4
	 * 234118 Computer Organization And Programming 3
	 * 234122 Introduction To System Programming 3
	 * */
}

void removeElements(DynamicArray* arr,Course course1,Course course2)
{
	//Checking bad cases
	DAResult result=removeElement(*arr,-1);
	assert(result==DA_ILLEGAL_INDEX);
	result=removeElement(*arr,3);
	assert(result==DA_ILLEGAL_INDEX);

	//Checking good cases
	result=removeElement(*arr,0);
	assert(result==DA_OK);
	assert((*arr)->len==2);

	//Making sure Atam and Matam are still there
	assert((*arr)->elements[0]->credits==course1->credits);
	assert(strcmp((*arr)->elements[0]->id,course1->id)==0);
	assert(strcmp((*arr)->elements[0]->name,course1->name)==0);

	assert((*arr)->elements[1]->credits==course2->credits);
	assert(strcmp((*arr)->elements[1]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[1]->name,course2->name)==0);

	//Making sure Matam is still there
	result=removeElement(*arr,0);
	assert(result==DA_OK);
	assert((*arr)->len==1);

	assert((*arr)->elements[0]->credits==course2->credits);
	assert(strcmp((*arr)->elements[0]->id,course2->id)==0);
	assert(strcmp((*arr)->elements[0]->name,course2->name)==0);

	result=removeElement(*arr,0);
	assert(result==DA_OK);
	assert((*arr)->len==0);
}

int main()
{
	Course matam,atam,mavo,infie;
	createCourse("234122","Introduction To System Programming",3,&matam);
	createCourse("234118","Computer Organization And Programming",3,&atam);
	createCourse("234114","Introduction For CS",4,&mavo);
	createCourse("104032","Infie 2M",5.5,&infie);
	DynamicArray arr=createDynamicArray();

	printf("Testing addElements\n");
	addElements(matam,atam,mavo,&arr);

	printf("Testing indexOfElement()\n");
	indexOfElementsTest(arr,mavo,atam,matam,infie);

	printf("Testing updateElement()\n");
	updateElementTest(&arr,infie,matam);

	printf("Testing displayElement()\n");
	displayElementTest(arr);

	printf("Testing displayAllElements()\n");
	displayAllElementsTest(arr);

	printf("Testing removeElements\n");
	removeElements(&arr,atam,matam);

	printf("All tests passed, well done!\n");

	destroyCourse(mavo);
	destroyCourse(matam);
	destroyCourse(atam);
	destroyCourse(infie);
	destroyDynamicArray(arr);
	return 0;
}
