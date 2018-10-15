

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../Headers/Course.h"

void buildCourses(Course* course1,Course* course2,Course* course3)
{
	//Checking bad cases
	CourseResult result;
	result=createCourse("234122","Introduction To System Programming",-1,course1);
	assert(result==COURSE_ILLEGAL_PARAMETER);

	//Checking good cases
	//First course-Creating Matam
	result=createCourse("234122","Introduction To System Programming",3,course1);
	assert(result==COURSE_OK);
	assert(strcmp((*course1)->name,"Introduction To System Programming")==0);
	assert(strcmp((*course1)->id,"234122")==0);
	assert((*course1)->credits==3);
	assert((*course1)->preCourses);

	//Second course-Creating Atam
	result=createCourse("234118","Computer Organization And Programming",3,course2);
	assert(result==COURSE_OK);
	assert(strcmp((*course2)->name,"Computer Organization And Programming")==0);
	assert(strcmp((*course2)->id,"234118")==0);
	assert((*course2)->credits==3);
	assert((*course2)->preCourses);

	//Third course-Creating Mavo
	result=createCourse("234114","Introduction to CS",4,course3);
	assert(result==COURSE_OK);
	assert(strcmp((*course3)->name,"Introduction to CS")==0);
	assert(strcmp((*course3)->id,"234114")==0);
	assert((*course3)->credits==4);
	assert((*course3)->preCourses);
}

void courseIdTest(Course course1,Course course2,Course course3)
{
	assert(coursesEqualId(course1,course2)==0);
	assert(coursesEqualId(course1,course3)==1);
	assert(courseLessThan(course1,course2)==0);
	assert(courseLessThan(course2,course1)==1);
}

void addPreCourseTest(Course course1,Course course2,Course course3)
{
	//Checking bad cases
	CourseResult result=addPreCourse(course1,course1);
	assert(result==COURSE_THE_SAME_COURSE);

	//Checking good cases
	//Adding Mavo as a preCourse to Atam
	result=addPreCourse(course2,course3);
	assert(result==COURSE_OK);
	assert(course2->preCourses->len==1);
	assert(course2->preCourses->elements[0]->credits==course3->credits);
	assert(course2->preCourses->elements[0]->id==course3->id);
	assert(course2->preCourses->elements[0]->name==course3->name);

	//Adding Atam as a preCourse to Matam
	result=addPreCourse(course1,course2);
	assert(result==COURSE_OK);
	assert(course1->preCourses->len==1);
	assert(course1->preCourses->elements[0]->credits==course2->credits);
	assert(course1->preCourses->elements[0]->id==course2->id);
	assert(course1->preCourses->elements[0]->name==course2->name);

	//Adding Mavo as a preCourse to Matam
	result=addPreCourse(course1,course3);
	assert(result==COURSE_OK);
	assert(course1->preCourses->len==2);
	assert(course1->preCourses->elements[0]->credits==course3->credits);
	assert(course1->preCourses->elements[0]->id==course3->id);
	assert(course1->preCourses->elements[0]->name==course3->name);
	assert(course1->preCourses->elements[1]->credits==course2->credits);
	assert(course1->preCourses->elements[1]->id==course2->id);
	assert(course1->preCourses->elements[1]->name==course2->name);

	result=addPreCourse(course1,course2);
	assert(result==COURSE_ALREADY_EXISTS);
}

void courseUpdateNameTest(Course course1,Course course2,Course course3)
{
	char* original={"Introduction to CS"},*new={"Mavo"};
	courseUpdateName(course1,new);
	assert(strcmp(course1->name,new)==0);
	assert(strcmp(course2->preCourses->elements[0]->name,new)==0);
	courseUpdateName(course1,original);
}

void displayCourseTest(Course course1,Course course2,Course course3)
{
	//Printing Mavo
	//Expected output: 234114 Introduction to CS 4
	displayCourse(course2);
	printf("\n");

	//Printing Matam
	//Expected output: 234122 Introduction To System Programming 3 234114 234118
	displayCourse(course1);
	printf("\n");

	//Printing Atam
	//Expected output: 234118 Computer Organization And Programming 3 234114
	displayCourse(course3);
	printf("\n");
}

void removePreCourseTest(Course course1,Course course2,Course course3)
{
	//Removing Mavo from Atam
	CourseResult result=removePreCourse(course2,course3);
	assert(result==COURSE_OK);
	assert(course2->preCourses->len==0);

	result=removePreCourse(course2,course3);
	assert(result==COURSE_NOT_EXIST);

	//Removing Atam from Matam
	result=removePreCourse(course1,course2);
	assert(result==COURSE_OK);
	assert(course1->preCourses->len==1);
}

int main()
{
	Course matam,atam,mavo;

	printf("Testing createCourse()\n");
	buildCourses(&matam,&atam,&mavo);

	printf("Testing courseEqualId() and courseLessThan()\n");
	courseIdTest(matam,atam,matam);

	printf("Testing addPreCourse()\n");
	addPreCourseTest(matam,atam,mavo);

	printf("Testing courseUpdateName()\n");
	courseUpdateNameTest(mavo,atam,matam);

	printf("Testing displayCourse()\n");
	displayCourseTest(matam,mavo,atam);

	printf("Testing removePreCourse()\n");
	removePreCourseTest(matam,atam,mavo);

	printf("All tests passed, well done!\n");

	destroyCourse(atam);
	destroyCourse(mavo);
	destroyCourse(matam);
	return 0;
}
