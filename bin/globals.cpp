#include "globals.h"

QString getName(){
    QString temp_name;

    QSqlQuery usr;

    usr.prepare("select name from Accounts where username = ?");
    usr.addBindValue(userid);
    usr.exec();
    usr.next();

    temp_name = usr.value(0).toString();
    return temp_name;
}

QString getCourseName(){
    QString temp_course;

    QSqlQuery c_name;

    c_name.prepare("select courseName from Courses where courseID = ?");
    c_name.addBindValue(courseid);
    c_name.exec();
    c_name.next();

    temp_course = c_name.value(0).toString();
    return temp_course;
}

QString getActivityName(){
    QString temp_act;

    QSqlQuery a_name;

    a_name.prepare("select activityName from Activity where activityID = ?");
    a_name.addBindValue(actid);
    a_name.exec();
    a_name.next();

    temp_act = a_name.value(0).toString();
    return temp_act;
}

QString getStudentName(){
    QString temp_stu;

    QSqlQuery s_name;

    s_name.prepare("select studentName from CoursesToStudent where studentID = ?");
    s_name.addBindValue(studentid);
    s_name.exec();
    s_name.next();

    temp_stu = s_name.value(0).toString();
    return temp_stu;
}

QString getUserType(){
    QString temp_type;

    QSqlQuery t_name;

    t_name.prepare("select userType from Accounts where username = ?");
    t_name.addBindValue(userid);
    t_name.exec();
    t_name.next();

    temp_type = t_name.value(0).toString();
    return temp_type;
}

QString getTypeAssignment(){
    QString temp_assign;

    QSqlQuery a_name;
    a_name.prepare("select TypeAssignment from Activity where activityID = ?");
    a_name.addBindValue(actid);
    a_name.exec();
    a_name.next();

    temp_assign = a_name.value(0).toString();
    return temp_assign;
}
