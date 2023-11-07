#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;
typedef struct stud
 {
 char name[20];
 int rollno;
 int div;
 char addr[50];
 }rec;
 class student
{
 public:
 rec records;
 void create();
 void display();
 void update();
 void delet();
 void append();
 int search();
 };
 void student::create()
 {
 //char ch='y';
 fstream seqfile;
 seqfile.open("d://student.dat",ios::in|ios::out|ios::binary);
 //do
 //{
 cout<<"\n Enter name:";
 cin>>records.name;
 cout<<"\n Enter roll-no:";
 cin>>records.rollno;
 cout<<"\n Enter division:";
 cin>>records.div;
 cout<<"\n Enter address:";
 cin>>records.addr;
 //then write a record in the file
 seqfile.write((char*)&records,sizeof(records));
 // cout<<"\n Do you want to add more records:";
 //cin>>ch;
 // } //while(ch=='y');
 seqfile.close();
 }
void student::display()
{
 fstream seqfile;
 int n;
 seqfile.open("d://student.dat",ios::in|ios::out|ios::binary);
 //positioning the pointer in file at beginning
 seqfile.seekg(0,ios::beg);
 cout<<"\n The contents of the file are..."<<endl;
 //read the record sequentially

 while(seqfile.read((char*)&records,sizeof(records)))
 {
 if(records.rollno!=-1)
 {
 cout<<"\n Name : "<<records.name;
 cout<<"\n Roll no : "<<records.rollno;
 cout<<"\n Division : "<<records.div;
 cout<<"\n Address : "<<records.addr;
 cout<<"\n";
 }
 }
 int last_rec=seqfile.tellg(); //last record position
 // formula for computing total no of objects in file

 n= last_rec/(sizeof(rec));
 seqfile.close();
 }

 void student::update()
 {
 int pos;
 cout<<"\n For updation";
 fstream seqfile;
 seqfile.open("d://student.dat",ios::in|ios::out|ios::binary);
 seqfile.seekg(0,ios::beg);
 //obtaining the position of desired record in file
 pos=search();
 if(pos==-1)
 {
 cout<<"\n Record not present";
 return;
 }
 //calculate actual offset of desired record in file

 int offset=pos*sizeof(rec);
 seqfile.seekp(offset); //seeking record for modification
 cout<<"\n Enter the values for updation";
 cout<<"\n Enter name:";
 cin>>records.name;
 cout<<"\n Enter roll-no:";
 cin>>records.rollno;
 cout<<"\n Enter division:";
 cin>>records.div;
 cout<<"\n Enter address:";
 cin>>records.addr;
 seqfile.write((char*)&records,sizeof(records))<<flush;
 seqfile.seekg(0);
 seqfile.close();
 cout<<"\n Record is updated";

 }

 void student::delet()
 {
 int pos;
 cout<<"\n For deletion";
 fstream seqfile;
 seqfile.open("d://student.dat",ios::in|ios::out|ios::binary);
 seqfile.seekg(0,ios::beg); //seeking for reading
 pos=search();
 if(pos==-1)
 {
 cout<<"\n Record not present";
 return;
 }
 //calculate offset to locate desired record

 int offset=pos*sizeof(rec);
 seqfile.seekp(offset);
 strcpy(records.name,"");
 records.rollno=-1;
 records.div=-1;
 strcpy(records.addr,"");
 seqfile.write((char*)&records,sizeof(records))<<flush;
 seqfile.seekg(0);
 seqfile.close();
 cout<<"\n Record is deleted";
 }

 void student::append()
 {
 fstream seqfile;
 seqfile.open("d://student.dat",ios::in|ios::out|ios::binary);
 seqfile.seekg(0,ios::beg);
 int i=0;
 while(seqfile.read((char*)&records,sizeof(records)))
 {
 i++;
 }
 seqfile.clear();
 cout<<"\n Enter the record for appending";
 cout<<"\n Enter name:";
 cin>>records.name;
 cout<<"\n Enter roll-no:";
 cin>>records.rollno;
 cout<<"\n Enter division:";
 cin>>records.div;
 cout<<"\n Enter address:";
 cin>>records.addr;
 seqfile.write((char*)&records,sizeof(records));
 seqfile.seekg(0);
 seqfile.close();
 cout<<"\n Record is appended";
 }

 int student::search()
 {
 fstream seqfile;
 int id,pos;
 cout<<"\n Enter the rollno for searching the record:";
 cin>>id;
 seqfile.open("d://student.dat",ios::ate|ios::in|ios::out|ios::binary);
 seqfile.seekg(0,ios::beg);
 pos=-1;
 int i=0;
 while(seqfile.read((char*)&records,sizeof(records)))
 {
 if(id==records.rollno)
 {
 pos=i;
 break;
 }
 i++;
 }
 return pos;
 }
 int main()
{
 student obj;
 char ch='y';
 int choice,key;
 do{
 cout<<"\n Main Menu";
 cout<<"\n 1. Create";
 cout<<"\n 2. Display";
 cout<<"\n 3. Update";
 cout<<"\n 4. Delete";
 cout<<"\n 5. Append";
 cout<<"\n 6. Search";
 cout<<"\n 7. Exit";
 cout<<"\n Enter your choice:";
 cin>>choice;
 switch(choice)
 {
 case 1: obj.create();
 break;
 case 2:obj.display();
 break;
 case 3: obj.update();
 break;
 case 4: obj.delet();
 break;
 case 5: obj.append();
 break;
 case 6: obj.search();
 if(key<0)
 cout<<"\n Record is not present";
 else
 cout<<"\n Record is present";
 break;
 case 7: exit(0);
 }
 cout<<"\n Do you want to continue:";
 cin>>ch;

 }while(ch=='y');
 return 0;
}