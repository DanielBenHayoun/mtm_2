#include <stdio.h>

#include "../Headers/Course.h"
#include "../Headers/CourseSystem.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);


int main(int argc, char **argv)
{

  CourseSystem sys=NULL;
  SysResult rs = SYS_OK;
  CourseResult rc = COURSE_OK;

  sys=createSystem("   (silly Sy stem %na $mes ");
  ASSERT("1.1" , sys!=NULL)

  Course c1;
  rc = createCourse(" sp  a c e s ", " intro    to cumber$0m# $pelling", -4, &c1);
  ASSERT("1.2" , rc==COURSE_ILLEGAL_PARAMETER)
  rc = createCourse(" sp  a c e s ", " intro    to cumber$0m# $pelling", 4, &c1);
  ASSERT("1.3" , rc==COURSE_OK)

  int n=sysNumCourses(sys);
  ASSERT("1.4" , n==0)

  rs=sysAddCourse(sys, c1);
  n=sysNumCourses(sys);
  ASSERT("1.5" , n==1)

  rs=sysAddCourse(sys, c1);
  ASSERT("1.6" , rs==SYS_COURSE_ALREADY_EXIST)

  rc = createCourse("A 89   00 B Q &", "Data Structures 1", 3, &c1);
  rs=sysAddCourse(sys, c1);
  n=sysNumCourses(sys);
  ASSERT("1.5" , n==2)

  int ans=-1;
  rs=sysIsPreCourse(sys, "   00ber  ", " sp  a c e s ", &ans);
  ASSERT("1.6" , rs==SYS_NOT_IN_SYSTEM && ans==-1)

  rc = createCourse("   00ber  ", "&&&&", 3, &c1);
  rs=sysAddCourse(sys, c1);
  n=sysNumCourses(sys);
  ASSERT("1.7" , n==3)

  rs=sysAddPreCourse(sys, "   00ber  ", " sp  a c e s ");
  ASSERT("1.6" , rs==SYS_OK)

  rs=sysAddPreCourse(sys, "   00ber  ", " sp  a c e s ");
  ASSERT("1.8" , rs==SYS_ALREADY_PRE_COURSE)

  displaySystem(sys);
/*
   (silly Sy stem %na $mes 
234114  intro    to cumber$0m# $pelling 4
   00ber   &&&& 3 234114
A 89   00 B Q & Data Structures 1 3
*/

  rs=sysRemovePreCourse(sys, "   00ber  ", " sp  a c e s ");
  ASSERT("1.9" , rs==SYS_OK)

  rs=sysRemovePreCourse(sys, "   00ber  ", " sp  a c e s ");
  ASSERT("1.10" , rs==SYS_NOT_PRE_COURSE)

  displaySystem(sys);
/*
   (silly Sy stem %na $mes 
234114  intro    to cumber$0m# $pelling 4
   00ber   &&&& 3
A 89   00 B Q & Data Structures 1 3
*/

  rs=sysAddPreCourse(sys, "A 89   00 B Q &", "   00ber  ");
  ASSERT("1.11" , rs==SYS_OK)
  displaySystem(sys);
/*
   (silly Sy stem %na $mes 
234114  intro    to cumber$0m# $pelling 4
   00ber   &&&& 3
A 89   00 B Q & Data Structures 1 3    00ber  
*/

  rs=sysRemoveCourse(sys, "234118");
  ASSERT("1.12" , rs==SYS_NOT_IN_SYSTEM)

  rs=sysRemoveCourse(sys, "   00ber  ");
  ASSERT("1.13" , rs==SYS_OK)
  displaySystem(sys);
/*
   (silly Sy stem %na $mes 
234114  intro    to cumber$0m# $pelling 4
A 89   00 B Q & Data Structures 1 3
*/
/* remark - also destroy    00ber   */

  n=sysNumCourses(sys);
  ASSERT("1.14" , n==2)

  rs=sysUpdateCourseName(sys, "   00ber  ", "Systems Programming");
  ASSERT("1.15" , rs==SYS_NOT_IN_SYSTEM)

  rs=sysUpdateCourseName(sys, " sp  a c e s ", " intro    to cumber$0m# $pelling M");
  ASSERT("1.16" , rs==SYS_OK)

  displaySystem(sys);
/*
   (silly Sy stem %na $mes 
234114  intro    to cumber$0m# $pelling M 4
A 89   00 B Q & Data Structures 1 3
*/

  destroySystem(sys);
  return 0;
}