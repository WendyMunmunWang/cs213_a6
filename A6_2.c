#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Person_class{

	void* super;
	void (*toString) (void*,char*,int);
};
struct Person {
	struct Person_class* class; //a person is the jump table
	char* name;//
};

void Person_toString (void* person, char* buf, int bufSize) {
	struct Person* personpointer = person; //personpointer is the pointer to the type struct Person 
	                                       //person is the type struct Person 
    snprintf (buf, bufSize, "Name: %s", personpointer->name);
}
struct Person_class Person_class_obj = {NULL, Person_toString};

struct Person* new_Person(char* name) {
  struct Person* obj = malloc (sizeof (struct Person)); //create memory space
  obj->class = &Person_class_obj; //the object pointing to the class equals to this person 
  obj->name = strdup(name);
  return obj; //return this person 
}

/*
 * Class Student extends Person
 */

struct Student_class{
	 struct Person_class* super;
	 void (* toString) (void*, char*, int);
 };
struct Student {
	struct Student_class* class;
	char* name;
	int sid;
 };
void Student_toString(void* student, char* buf, int bufSize){
	struct Student* this = student;
	
	char STUDENT_buf[bufSize]; //pointer 
	this->class->super->toString(this, STUDENT_buf, bufSize); //name is stored in the buf 
	snprintf (buf, bufSize, "%s, SID: %d", STUDENT_buf, this->sid); //printing and store the information in the buf
	                                                                   //get the name and sid of the person 
 }
 
struct Student_class Student_class_obj={&Person_class_obj, Student_toString};

struct Student* new_Student(char* name, int sid){
	 struct Student* obj=malloc(sizeof (struct Student));
	 obj->class = &Student_class_obj;
	 obj->name=strdup(name);
	 obj->sid=sid;
	 return obj;
 }
 
 
 /*
 * Main
 */
 
 
 int main(int argc, char** argv){
	 struct Person* people[2] = {new_Person("Alex"),(struct Person*)new_Student("Alice", 300)};
	 char buf [1000];
	 for (int i=0;i<sizeof(people)/sizeof(people[0]);i++){
		 people[i]->class->toString(people[i],buf,1000);
		 printf("%s\n",buf);// we don't need this because it prints already in the toString method
		                 
	 }
 }
 
 
 
 

 
 
 
 
 
 
 
 