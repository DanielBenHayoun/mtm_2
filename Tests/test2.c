//
// Created by daniel on 12/3/2017.
//
#include <stdio.h>
#include "../Headers/Course.h"

#define ASSERT(test_number , test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);

void checkCoursesEqualId(Course course1 , Course course2 , Course course3, Course course4){
  int result=coursesEqualId(course1 , course1);
  ASSERT("2.1" , result==1);
  result=coursesEqualId(course4 , course4);
  ASSERT("2.2" ,result==1);
  result=coursesEqualId(course1,course2);
  ASSERT("2.3", result==0);
  result=coursesEqualId(course3 , course4);
  ASSERT("2.4" , result==0);
}
void checkCourseLessThen(Course course1 , Course course2 , Course course3 ){
 // course1 =matam , course2=combi
  int result=courseLessThan( course1 , course2);
  ASSERT("3.1" , result==1);
  //course2=combi course3 = atam
  result=courseLessThan(course2 , course3 );
  ASSERT("3.2", result==0);
}

void checkCourseUpdateName(Course course1 , Course course2){
  //Good case only
  CourseResult result=courseUpdateName(course1 , "Introduction to Systems Programming");
  ASSERT("4.1" , result==COURSE_OK);
  result=courseUpdateName(course2 , "Combinatorics for Computer Science");
  ASSERT("4.2" , result==COURSE_OK);
}

void checkAddPreCourse(Course course1 , Course course2 ,Course course3 , Course course4){
  ///Good case
  //Adding mavo as precours of matam
  CourseResult result=addPreCourse(course1 , course4);
  ASSERT("5.1", result==COURSE_OK);
  // Adding infi1m as procourse of matam
  result=addPreCourse(course1 , course2);
  ASSERT("5.2", result==COURSE_OK);
  //adding mavo as precourse of atam
  result=addPreCourse(course3 , course4);
  ASSERT("5.3" , result==COURSE_OK);
  ///Bad case
  //the same course
  result=addPreCourse(course1 , course1);
  ASSERT("5.4" , result==COURSE_THE_SAME_COURSE);
  //course already exists
  result=addPreCourse(course1 , course2);
  ASSERT("5.5", result==COURSE_ALREADY_EXISTS);
}
 void checkRemovePreCourse(Course  course1 , Course course2 , Course course3){
   //COURSE1=MATAM , COURSE2=MAVO , COURSE3=ATAM
   ///cheack bad cases
   //trying to remove matam from atam
   CourseResult result=removePreCourse( course3 , course1);
   ASSERT("6.1", result==COURSE_NOT_EXIST);
   ///Good case
   //removing mavo as precourse of atam
   result=removePreCourse(course3 , course2);
   ASSERT("6.2", result==COURSE_OK);
 }

void checkDisplayCourse(Course course1 , Course course2 , Course course3){
  //COURSE1=MATAM , COURSE2=COMBI COURSE3=ATAM
  //Display matam
  displayCourse(course1);
  printf("\n");
  /*Expecting:
    Introduction to Systems Programming 3.0 234114 104031
   */
  displayCourse(course2);
  printf("\n");
  /*Expecting:
    Combinatorics for Computer Science 3.0
   */
  displayCourse(course3);
  /*Expecting
   atam 3.0
   */
}







int main() {
  Course course1;
  Course course2;
  Course course3;
  Course course4;
  Course course5;
  Course course6;
  ///TEST GOOD CASES
  printf("TEST 1.0\n");
  CourseResult result=createCourse("234122", "matam", 3 ,&course1 );
  ASSERT("1.1" , result==COURSE_OK)
  result=createCourse("234141" ,"combi", 3 , &course2 );
  ASSERT("1.2" , result==COURSE_OK)
  result=createCourse("234118","atam",3,&course3 );
  ASSERT("1.3" , result==COURSE_OK)
  result=createCourse("234114","mavo",3.5,&course4 );
  ASSERT("1.4" , result==COURSE_OK)
  result=createCourse("104031","infi1m",5.5,&course5 );
  ASSERT("1.5" , result==COURSE_OK)
  result=createCourse("104166","algebra1",5.5,&course6 );
  ASSERT("1.6" , result==COURSE_OK)

  ///TEST BAD CASE
  result=createCourse("1" , "a" ,-1 , &course1 );
  ASSERT("1.7" , result==COURSE_ILLEGAL_PARAMETER);
  result=createCourse("2" , "b" ,-2 , &course1 );
  ASSERT("1.7" , result==COURSE_ILLEGAL_PARAMETER);
  result=createCourse("3" , "c" ,-3 , &course1 );
  ASSERT("1.7" , result==COURSE_ILLEGAL_PARAMETER);
  result=createCourse("4" , "d" ,-4 , &course1 );
  ASSERT("1.7" , result==COURSE_ILLEGAL_PARAMETER);
  result=createCourse("89" , "o" ,-10 , &course1 );
  ASSERT("1.7" , result==COURSE_ILLEGAL_PARAMETER);
  printf("\nTEST 2.0");
  checkCoursesEqualId(course1 , course2 , course3 , course4);
  printf("\nTEST 3.0");
  checkCourseLessThen(course1 , course2 ,course3);
  printf("\nTEST 4.0");
  checkCourseUpdateName(course1 , course2);
  printf("\nTEST 5.0");
  checkAddPreCourse(course1 ,course5 ,course3 , course4 );
  printf("\nTEST 6.0");
  checkRemovePreCourse(course1 , course4 , course3);
  printf("\nTEST 7.0\n");
  checkDisplayCourse(course1 , course2, course3);
  destroyCourse(course1);
  destroyCourse(course2);
  destroyCourse(course3);
  destroyCourse(course4);
  destroyCourse(course5);
  destroyCourse(course6);
  return 0;
}