#include<iostream>
#include<string>
#include<ctime>
#include<vector>
using namespace std;

// Structures
struct Term;
struct Course;
struct Student;


struct Course{
    string name;
    int credit;
    string location;
    Term* term;
    int day;
    int hour;
    float length;
};

struct Term{
    int year;
    int semester;
    vector <Course> term_courses;
};

struct Student{
    string first_name;
    string last_name;
    string student_number;
    vector <Term> student_terms;
    vector <Course> student_courses;
};


// Vectors & Counters
vector <Term> terms;
vector <Course> courses;
vector <Student> students;


// Main Functions declaration
void addTerm();
void addCourse();
void addStudent();
void getTerms();
void getCourses();
void getStudents();
void getStudentSemesterCoursesCount();
void getStudentTotalCoursesCount();
void checkStudentCoursesConflicts();
void takeCourseForStudent();
void getStudentSemesterCourses();


// Side Functions declaration
Student getStudent(string student_number);
bool coursesCollide(Course course1, Course course2);
string getCurrentDateTime();
void systemPause();



int main(){
    // Tests
    Student student1;
    student1.student_number="2002";
    student1.first_name="Erfan";
    student1.last_name="Saberi";

    Course course1;
    Course course2;
    Course course3;
    Term term1;
    term1.year=1400;
    term1.semester=1;
    student1.student_terms.push_back(term1);
    course1.name="Math";
    course2.name="FCP";
    course3.name="Physics";

    course1.day=1;
    course2.day=1;
    course3.day=2;
    course1.term=&term1;
    course2.term=&term1;
    course3.term=&term1;
    course1.hour=10;
    course2.hour=11;
    course3.hour=15;
    course1.length=3;
    course2.length=1;
    course3.length=1;
    course1.credit=3;
    course2.credit=2;
    course3.credit=1;

    term1.term_courses.push_back(course1);
    term1.term_courses.push_back(course2);
    term1.term_courses.push_back(course3);
    terms.push_back(term1);

    student1.student_courses.push_back(course1);
    student1.student_courses.push_back(course2);
    students.push_back(student1);

    // End of Tests

    cout<<"[+] Welcome to FUS (Farhangian University System)\n";
    cout<<"[+] Logged in at "<<getCurrentDateTime()<<"\n";

    int choice;
    while (1){
        cout<<"\n :: Menu\n";
        cout<<"[1] Add Term (Semester)\n";
        cout<<"[2] Add Class (Course)\n";
        cout<<"[3] Add Student\n";
        cout<<"[4] Get Terms\n";
        cout<<"[5] Get Classes\n";
        cout<<"[6] Get Students\n";
        cout<<"[7] Courses count (for one semester for one student)\n";
        cout<<"[8] Total courses count (for one student)\n";
        cout<<"[9] Check conflict (for one student)\n";
        cout<<"[10] Take course (for one student)\n";
        cout<<"[11] Get Student courses (for one student)\n";
        cout<<"[0] Exit\n\n";
        cout<<"[>] Enter your choice: ";

        cin>>choice;

        switch (choice)
        {
        case 1: addTerm(); break;
        case 2: addCourse(); break;
        case 3: addStudent(); break;
        case 4: getTerms(); break;
        case 5: getCourses(); break;
        case 6: getStudents(); break;
        case 7: getStudentSemesterCoursesCount(); break;
        case 8: getStudentTotalCoursesCount(); break;
        case 9: checkStudentCoursesConflicts(); break;
        case 10: takeCourseForStudent(); break;
        case 11: getStudentSemesterCourses(); break;
        case 0: cout<<"[~] Have a nice day!"; return 0; break;

        default: cout<<"[!] Unknown choice!\n"; break;
        }
        systemPause();
    }

}

// Main functions definitions
void addTerm(){
    // Year & Semester
    Term term;
    int semester, year;

    cout<<"[?] Enter Year: ";
    cin>>year;
    term.year = year;

    cout<<"[?] Enter Semester (1 or 2): ";
    cin>>semester;

    switch (semester){
        case 1:
        case 2:
            term.semester = semester;
            terms.push_back(term);
            cout<<"[+] Term saved successfully\n";
            break;
        
        default:
            cout<<"[!] Semester must be 1 or 2!\n";
            break;
    }

}

void getTerms(){
    for (int i=0; i<terms.size(); i++)
    {
        cout<<"-"<<i<<"- ";
        cout<<"Year: "<<terms[i].year<<"\t";
        cout<<"Semester: "<<terms[i].semester<<"\n";
    }
}

void addCourse(){
    int term_id;
    cout<<"[?] Enter term id: ";
    cin>>term_id;

    if (term_id>=terms.size()){
        cout<<"[!] Term not found!\n";
        return;
    }

    Term* term = &terms[term_id];
    cout<<"[*] Year: "<<terms[term_id].year<<"\t";
    cout<<"Semester: "<<terms[term_id].semester<<"\n";


    while (1){
        Course course;
        course.term = term;
        cout<<"[?] Enter class name (Can't contain whitespace): ";
        cin>> course.name;
        cout<<"[?] Enter course credit: ";
        cin>> course.credit;
        cout<<"[?] Enter class location (Can't contain whitespace): ";
        cin>> course.location;
        cout<<"[?] Enter class day (0:Saturday / 6:Friday): ";
        cin>> course.day;
        course.day = course.day % 7;
        cout<<"[?] Enter class start hour: ";
        cin>> course.hour;
        course.hour = course.hour % 24;
        cout<<"[?] Enter class length (hours): ";
        cin>> course.length;
        terms[term_id].term_courses.push_back(course);
        cout<<"[+] Course Saved\n";
        cout<<"[?] Do you want to add another course to this term? (y/n): ";
        char choice;
        cin>>choice;
        if (choice!='y') break;
    }
};

void getCourses(){
    int term_id, term_courses_count;
    cout<<"[?] Enter term id: ";
    cin>>term_id;

    if (term_id>=terms.size()){
        cout<<"[!] Term not found!\n";
        return;
    }

    Term term = terms[term_id];
    term_courses_count = term.term_courses.size();
    for (int i=0; i<term_courses_count; i++)
    {
        cout<<"-"<<i<<"- ";
        cout<<"Name: "<<term.term_courses[i].name<<"\t";
        cout<<"Credit: "<<term.term_courses[i].credit<<"\t";
        cout<<"Location: "<<term.term_courses[i].location<<"\n";
        cout<<"    Day: "<<term.term_courses[i].day<<"\t";
        cout<<"Hour: "<<term.term_courses[i].hour<<" \t";
        cout<<"Length: "<<term.term_courses[i].length<<" hours\n";
    }
};

void addStudent(){
    while (1){
        Student student;
        cout<<"[?] Student first name: ";
        cin>>student.first_name;
        cout<<"[?] Student last name: ";
        cin>>student.last_name;
        cout<<"[?] Student number: ";
        cin>>student.student_number;
        if (getStudent(student.student_number).student_number == "-1"){
            students.push_back(student);
            cout<<"[+] Student saved\n";
            cout<<"[?] Do you want to add another student? (y/n): ";
        }
        else{
            cout<<"[+] Student number is in use (Must be unique)\n";
            cout<<"[?] Do you want to try again? (y/n): ";
        }
        char choice;
        cin>>choice;
        if (choice!='y') break;
    }
};

void getStudents(){
    for (int i=0; i<students.size(); i++){
        cout<<"-"<<i<<"- ";
        cout<<"First Name: "<<students[i].first_name<<"\t";
        cout<<"Last Name: "<<students[i].last_name<<"\t";
        cout<<"Student Number: "<<students[i].student_number<<"\n";
    }
};

void getStudentSemesterCoursesCount(){
    Student student;
    Term term;
    string student_number;
    int counter=0, term_id=0;
    // Get Student
    cout<<"[?] Enter student number: ";
    cin>>student_number;
    student = getStudent(student_number);
    if (student.student_number == "-1"){
        cout<<"[!] Student not found!\n";
        return;
    }
    // Get Term
    cout<<"[?] Enter term id: ";
    cin>>term_id;
    if (term_id>=terms.size()){
        cout<<"[!] Term id out of range\n";
        return;
    }
    term = terms[term_id];

    int credit=0, student_courses_count=student.student_courses.size();
    for (int i=0; i<student_courses_count; i++){
        if (student.student_courses[i].term->year==term.year && student.student_courses[i].term->semester==term.semester){
            credit+=student.student_courses[i].credit;
        }
    }
    cout<<"[+] Student Courses Credit in ";
    if (term.semester==1){
        cout<<"First ";
    }
    else {
        cout<<"Second ";
    }
    cout<<"semester of "<<term.year<<" is "<<credit<<"\n";
};

void getStudentTotalCoursesCount(){
    Student student;
    string student_number;
    int counter=0;

    // Get Student
    cout<<"[?] Enter student number: ";
    cin>>student_number;
    student = getStudent(student_number);
    if (student.student_number=="-1"){
        cout<<"[!] Student not found!\n";
        return;
    }

    int credit=0, student_courses_count=student.student_courses.size();
    for (int i=0; i<student_courses_count; i++){
        credit+=student.student_courses[i].credit;
    }
    cout<<"[+] Student Total Courses Credit is "<<credit<<"\n";
};

void checkStudentCoursesConflicts(){
    Student student;
    string student_number;
    cout<<"[?] Enter student number: ";
    cin>>student_number;
    student = getStudent(student_number);
    if (student.student_number=="-1"){
        cout<<"[!] Student not found!\n";
        return;
    }

    int courses_count=student.student_courses.size(); //Term, Day, Hour, Length
    int collisions=0;
    for (int i=0; i<courses_count; i++){
        for (int j=i+1; j<courses_count; j++){
            if (coursesCollide(student.student_courses[i], student.student_courses[j])){
                collisions++;
                cout<<"[#] Collision <"<<collisions<<">\n";
                cout<<" - [i] Name:"<<student.student_courses[i].name;
                cout<<" \tTerm:"<<student.student_courses[i].term->year<<":"<<student.student_courses[i].term->semester;
                cout<<" Day: "<<student.student_courses[i].day<<" Hour: "<<student.student_courses[i].hour<<" Length: "<<student.student_courses[i].length<<"\n";
                cout<<" - [i] Name:"<<student.student_courses[j].name;
                cout<<" \tTerm:"<<student.student_courses[j].term->year<<":"<<student.student_courses[j].term->semester;
                cout<<" Day: "<<student.student_courses[j].day<<" Hour: "<<student.student_courses[j].hour<<" Length: "<<student.student_courses[j].length<<"\n\n";
            }
        }
    }
};

void takeCourseForStudent(){
    Student student;
    Term term;
    string student_number;
    int counter=0, term_id=0;
    // Get Student
    cout<<"[?] Enter student number: ";
    cin>>student_number;
    student = getStudent(student_number);
    if (student.student_number == "-1"){
        cout<<"[!] Student not found!\n";
        return;
    }
    // Get Term
    cout<<"[?] Enter term id: ";
    cin>>term_id;
    if (term_id>=terms.size()){
        cout<<"[!] Term id out of range\n";
        return;
    }
    term = terms[term_id];
    cout<<"[+] Year: "<<term.year<<"\tSemester: "<<term.semester<<"\n";
    cout<<"[+] Courses list: \n";
    for (int i=0; i<term.term_courses.size(); i++){
        cout<<"-"<<i<<"- Name: "<<term.term_courses[i].name<<"\t"<<"\tCredit: "<<term.term_courses[i].credit<<"\t Location: "<<term.term_courses[i].location<<"\n";
        cout<<"    Day: "<<term.term_courses[i].day<<"\tHour: "<<term.term_courses[i].hour<<"\tLength: "<<term.term_courses[i].length<<"\n";
    }

    cout<<"[?] Enter Course id: ";
    int course_id;
    bool cantake=1;
    cin>>course_id;
    for (int i=0; i<student.student_courses.size(); i++){
        if (coursesCollide(term.term_courses[course_id], student.student_courses[i])){
            cantake = 0;
            cout<<"[!] Course Collides with:\n";
            cout<<"    Name: "<<term.term_courses[i].name<<"\t"<<"\tCredit: "<<term.term_courses[i].credit<<"\t Location: "<<term.term_courses[i].location<<"\n";
            cout<<"    Day: "<<term.term_courses[i].day<<"\tHour: "<<term.term_courses[i].hour<<"\tLength: "<<term.term_courses[i].length<<"\n";
        }
    }
    if (cantake){
        for (int i=0; i<students.size(); i++){
            if (students[i].student_number==student_number){
                students[i].student_courses.push_back(term.term_courses[course_id]);
                cout<<"[+] Class added to student\n";
                return;
            }
        }
    }
    else {
        cout<<"[!] Try again with another course\n";
    }
};

void getStudentSemesterCourses(){
    Student student;
    Term term;
    string student_number;
    int counter=0, term_id=0;
    // Get Student
    cout<<"[?] Enter student number: ";
    cin>>student_number;
    student = getStudent(student_number);
    if (student.student_number == "-1"){
        cout<<"[!] Student not found!\n";
        return;
    }
    // Get Term
    cout<<"[?] Enter term id: ";
    cin>>term_id;
    if (term_id>=terms.size()){
        cout<<"[!] Term id out of range\n";
        return;
    }
    term = terms[term_id];

    int student_courses_count=student.student_courses.size();
    for (int i=0; i<student_courses_count; i++){
        if (student.student_courses[i].term->year==term.year && student.student_courses[i].term->semester==term.semester){
            counter++;
            cout<<"["<<counter<<"] Name:"<<student.student_courses[i].name;
            cout<<"\tTerm:"<<student.student_courses[i].term->year<<":"<<student.student_courses[i].term->semester<<"\n";
            cout<<"    Day: "<<student.student_courses[i].day<<"\tHour: "<<student.student_courses[i].hour<<"\tLength: "<<student.student_courses[i].length<<"\n";
            cout<<"    Location: "<<student.student_courses[i].location<<"\tCredit: "<<student.student_courses[i].credit<<"\n";
                
        }
    }
    cout<<"[+] Student Courses in ";
    if (term.semester==1){
        cout<<"First ";
    }
    else {
        cout<<"Second ";
    }
    cout<<"semester of "<<term.year<<"\n";
};

// Side functions definitions
string getCurrentDateTime(){
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

void systemPause(){
    cout<<"[~] ";
    system("pause");
}

Student getStudent(string student_number){
    int students_size=students.size();
    for (int i=0; i<students_size; i++){
        if (students[i].student_number == student_number){
            return students[i];
        }
    }
    Student null_student;
    null_student.student_number="-1";
    return null_student;
}

bool coursesCollide(Course course1, Course course2){
    if (course1.term->year!=course2.term->year) return 0;
    if (course1.term->semester!=course2.term->semester) return 0;
    if (course1.day!=course2.day) return 0;
    if (course1.hour+course1.length<=course2.hour) return 0;
    if (course2.hour+course2.length<=course1.hour) return 0;
    return 1;
}