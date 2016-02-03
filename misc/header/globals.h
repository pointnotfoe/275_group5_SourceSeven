#ifndef GLOBALS_H
#define GLOBALS_H
#include "login.h"

extern QString userid;          // login username
extern QString courseid;        // course accessed
extern int actid;               // activity accessed
extern QString actID;
extern QString studentid;       // student accessed
extern QString value;
extern QString actname;         // activity name accessed
extern QString rubricid;        // rubric accessed
extern QString rubID;

QString getName();              // get name using userid
QString getCourseName();        // get course name using courseid
QString getActivityName();      // get activity name using actid
QString getStudentName();       // get student name using studentid
QString getUserType();          // get user type using userid
QString getTypeAssignment();    // get type assignment using actid

#endif // GLOBALS_H
