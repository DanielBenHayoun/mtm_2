/*
 * CourseSystem_test.c
 *
 *  Created on: Nov 19, 2017
 *      Author: 7
 */


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../Headers/CourseSystem.h"

void createSystemTest(CourseSystem* sys)
{
	*sys=createSystem("Computer Science");
	assert(*sys);
	assert(strcmp((*sys)->name,"Computer Science")==0);
	assert((*sys)->courses);
	assert(sysNumCourses(*sys)==0);
}

void sysAddCoursesTest(CourseSystem* sys,Course course1,Course course2,Course course3
		,Course course4,Course course5,Course course6,Course course7)
{
	//Adding Logic Design to the system
	SysResult result=sysAddCourse(*sys,course1);
	assert(result==SYS_OK);
	assert((*sys)->courses->len==1);
	assert((*sys)->courses->elements[0]->credits==course1->credits);
	assert(strcmp((*sys)->courses->elements[0]->id,course1->id)==0);
	assert(strcmp((*sys)->courses->elements[0]->name,course1->name)==0);

	//Adding Mavo to the system
	result=sysAddCourse(*sys,course2);
	assert(result==SYS_OK);
	assert((*sys)->courses->len==2);
	assert((*sys)->courses->elements[1]->credits==course2->credits);
	assert(strcmp((*sys)->courses->elements[1]->id,course2->id)==0);
	assert(strcmp((*sys)->courses->elements[1]->name,course2->name)==0);

	//Adding rest of the courses
	sysAddCourse(*sys,course3);
	sysAddCourse(*sys,course4);
	sysAddCourse(*sys,course5);
	sysAddCourse(*sys,course6);
	sysAddCourse(*sys,course7);

	//Checking bad cases
	result=sysAddCourse(*sys,course2);
	assert(result==SYS_COURSE_ALREADY_EXIST);

}

void sysAddPreCourseTest(CourseSystem* sys,Course course1,Course course2
		,Course course3,Course course4,Course course5,Course course6,Course course7)
{
	//logic_design,mavo,atam,matam,combi,digital_systems,mevne
	//Checking bad cases
	SysResult result=sysAddPreCourse(*sys,"234141","234111");
	assert(result==SYS_NOT_IN_SYSTEM);

	result=sysAddPreCourse(*sys,"234111","234114");
	assert(result==SYS_NOT_IN_SYSTEM);

	//Checking good cases
	//Adding Atam as a preCourse to Matam
	result=sysAddPreCourse(*sys,course4->id,course3->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[3]->preCourses->len==1);
	assert(strcmp((*sys)->courses->elements[3]->preCourses->elements[0]->id,"234118")==0);

	//Adding Mavo as a preCourse to Atam
	result=sysAddPreCourse(*sys,course3->id,course2->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[2]->preCourses->len==1);
	assert(strcmp((*sys)->courses->elements[2]->preCourses->elements[0]->id,"234114")==0);

	//Adding Mavo as a preCourse to Matam
	result=sysAddPreCourse(*sys,course4->id,course2->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[3]->preCourses->len==2);
	assert(strcmp((*sys)->courses->elements[3]->preCourses->elements[0]->id,"234114")==0);
	assert(strcmp((*sys)->courses->elements[3]->preCourses->elements[1]->id,"234118")==0);

	//Adding Matam as a preCourse to Mevne
	result=sysAddPreCourse(*sys,course7->id,course4->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[6]->preCourses->len==1);
	assert(strcmp((*sys)->courses->elements[6]->preCourses->elements[0]->id,"234122")==0);

	//Adding Combi as a preCourse to Mevne
	result=sysAddPreCourse(*sys,course7->id,course5->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[6]->preCourses->len==2);
	assert(strcmp((*sys)->courses->elements[6]->preCourses->elements[0]->id,"234122")==0);
	assert(strcmp((*sys)->courses->elements[6]->preCourses->elements[1]->id,"234141")==0);

	//Adding Digital Systems as a preCourse to Logic Design
	result=sysAddPreCourse(*sys,course1->id,course6->id);
	assert(result==SYS_OK);
	assert((*sys)->courses->elements[0]->preCourses->len==1);
	assert(strcmp((*sys)->courses->elements[0]->preCourses->elements[0]->id,"234145")==0);

	result=sysAddPreCourse(*sys,course4->id,course3->id);
	assert(result==SYS_ALREADY_PRE_COURSE);
}

void sysIsPreCourseTest(CourseSystem sys)
{
	//Checking bad cases
	int answer=-1;
	SysResult result=sysIsPreCourse(sys,"234111","234114",&answer);
	assert(result==SYS_NOT_IN_SYSTEM);
	assert(answer==-1);

	result=sysIsPreCourse(sys,"234114","234111",&answer);
	assert(result==SYS_NOT_IN_SYSTEM);
	assert(answer==-1);

	//Checking good cases
	result=sysIsPreCourse(sys,"234118","234114",&answer);
	assert(result==SYS_OK);
	assert(answer==1);

	result=sysIsPreCourse(sys,"234118","234122",&answer);
	assert(result==SYS_OK);
	assert(answer==0);
}

void sysUpdateCourseNameTest(CourseSystem* sys)
{
	//Checking bad cases
	SysResult result=sysUpdateCourseName(*sys,"104031","Wrong");
	assert(result==SYS_NOT_IN_SYSTEM);

	//Checking good cases
	result=sysUpdateCourseName(*sys,"234118","Atam");
	assert(result==SYS_OK);
	assert(strcmp((*sys)->courses->elements[2]->name,"Atam")==0);
	assert(strcmp((*sys)->courses->elements[3]->preCourses->elements[1]->name
			,"Atam")==0);
	sysUpdateCourseName(*sys,"234118","Computer Organization And Programming");
}

void displaySystemTest(CourseSystem sys)
{
	displaySystem(sys);
	/*Expected output:
	 * Computer Science
	 * 044262 Logic Design 3 234145
	 * 234114 Introduction To CS 4
	 * 234118 Computer Organization And Programming 3 234114
	 * 234122 Introduction To System Programming 3 234114 234118
	 * 234141 Combinatorics For CS 3
	 * 234145 Digital Systems 3
	 * 234218 Data Structures 1 3 234122 234141
	 * */
}

void sysRemoveCourseTest(CourseSystem* sys)
{
	//Checking bad cases
	SysResult result=sysRemovePreCourse(*sys,"234114","234118");
	assert(result==SYS_NOT_PRE_COURSE);

	result=sysRemoveCourse(*sys,"234111");
	assert(result==SYS_NOT_IN_SYSTEM);

	result=sysRemovePreCourse(*sys,"234111","234114");
	assert(result==SYS_NOT_IN_SYSTEM);

	//Checking good cases
	//Removing Matam from Mevne
	result=sysRemovePreCourse(*sys,"234218","234122");
	assert(result==SYS_OK);
	assert((*sys)->courses->len==7);
	assert((*sys)->courses->elements[6]->preCourses->len==1);
	assert(strcmp((*sys)->courses->elements[6]->preCourses->elements[0]->id,"234141")==0);

	//Removing Mavo from system
	result=sysRemoveCourse(*sys,"234114");
	assert(result==SYS_OK);
	assert((*sys)->courses->len==6);
	assert(strcmp((*sys)->courses->elements[0]->id,"044262")==0);
	assert(strcmp((*sys)->courses->elements[1]->id,"234118")==0);
	assert(strcmp((*sys)->courses->elements[2]->id,"234122")==0);
	assert(strcmp((*sys)->courses->elements[3]->id,"234141")==0);
	assert(strcmp((*sys)->courses->elements[4]->id,"234145")==0);
	assert(strcmp((*sys)->courses->elements[5]->id,"234218")==0);
	assert((*sys)->courses->elements[1]->preCourses->len==0);
	assert((*sys)->courses->elements[2]->preCourses->len==1);
	if( result)
		return;
}

int main()
{
	Course logic_design,mavo,atam,matam,combi,digital_systems,mevne;
	createCourse("044262","Logic Design",3,&logic_design);
	createCourse("234114","Introduction to CS",4,&mavo);
	createCourse("234118","Computer Organization And Programming",3,&atam);
	createCourse("234122","Introduction To System Programming",3,&matam);
	createCourse("234141","Combinatorics For CS",3,&combi);
	createCourse("234145","Digital Systems",3,&digital_systems);
	createCourse("234218","Data Structures 1",3,&mevne);
	CourseSystem sys;

	printf("Testing createSystem()\n");
	createSystemTest(&sys);

	printf("Testing sysAddCourse()\n");
	sysAddCoursesTest(&sys,logic_design,mavo,atam,matam,combi,digital_systems,mevne);

	printf("Testing sysAddPreCourse()\n");
	sysAddPreCourseTest(&sys,logic_design,mavo,atam,matam,combi,digital_systems,mevne);

	printf("Testing sysIsPreCourse()\n");
	sysIsPreCourseTest(sys);

	printf("Testing sysUpdateCourseName()\n");
	sysUpdateCourseNameTest(&sys);

	printf("Testing displaySystem()\n");
	displaySystemTest(sys);

	printf("Testing sysRemovePreCourse() and sysRemoveCourse()\n");
	sysRemoveCourseTest(&sys);

	printf("All tests passed, well done!\n");
	destroySystem(sys);

	return 0;
}
