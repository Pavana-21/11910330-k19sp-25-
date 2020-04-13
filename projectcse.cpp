#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;
class book{
	char book_no[7];
	char book_name[50];
	char author[20];
	public:
		void create_book(){
			cout<<"\n New book Entry....";
			cout<<"\n Enter the book number";
			cin>>book_no;
			cout<<"\n Enter the book name";
			gets(book_name);
			cout<<"\n Enter the author name";
			gets(author);
		}
		void  show_book(){
			cout<<"\n book number"<<book_no;
			cout<<"\n book name";
			puts(book_name);
			cout<<"\n book author";
			puts(author);
		}
		void  modify_book(){
			cout<<"\n book number"<<book_no;
			cout<<"\n update book name";
			gets(book_name);
			cout<<"\n update author name";
			gets(author);
		}
		char* retbno(){
			return book_no;
		}
};

class student{
	char stid_no[7];
	char name[20];
	char stbno[7];
	int token;
	public:
		void create_student(){
			cout<<"\n new student entry";
			cout<<"\n enter the id number";
			cin>>stid_no;
			cout<<"enter the name of student";
			gets(name);
			token=0;
			cout<<"\n\n student record created";
		}
		void show_student(){
			cout<<"\n\n id number"<<stid_no;
			cout<<"\n\n student name";
			puts(name);
			 cout<<"\n no of book issued "<<token;
			 if(token==1)
			 	cout<<"\n\n book no"<<stbno;
		}
		char* retstid(){
			return stid_no;
		}
		char* retsbno(){
			return stbno;
		}
		int rettoken(){
			return token;
		}
		void addtoken(){
			token=1;
		}
		void resettoken(){
			token=0;
		}
		void getstbno(char t[]){
			strcpy(stbno,t);
		}
};
class staff_members{
	char id_no[7];
	char staff_name[20];
	char staff_no[10];
	public:
		void create_staff(){
			cout<<"\n\n new staff member entry";
			cout<<"enter the new staff member id number";
			cin>>id_no;
			cout<<"enter the staff member name";
			gets(staff_name);
			cout<<"enter the staff member mobile number";
			cin>>staff_no;
			cout<<"\n new staff member added ";
			
		}
		void modify_staff(){
			cout<<"\n\n staff id "<<id_no;
			cout<<"\n\n enter the modified name of staff member";
			gets(staff_name);
			cout<<"\n\n enter the modified phone number of staff member ";
			cin>>staff_no;
			cout<<"\n\n  staff member details modified ";
		}
		char* retstaffno(){
			return id_no;
		}
};


fstream fp,fp1;
book bk;
student st;
staff_members sm;

// writing the details
void write_book(){
	char ch;
	fp.open("book.txt",ios::out|ios::app);
	do{
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\n do you want to add more book  (Y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void write_student(){
		char ch;
	fp.open("student.txt",ios::out|ios::app);
	do{
	st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\n do you want to add more student details  (Y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_staff(){
	char ch;
	fp.open("staff.txt",ios::out|ios::app);
	do{
		sm.create_staff();
		fp.write((char*)&sm,sizeof(staff_members));
		cout<<"\n\n do you want to add staff members details  (Y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

//modify the data
void modify_book(){
	char n[7];
	int found=0;
	cout<<"\n\n modify book record... ";
	cout<<"\n\n enter tne book number ";
	cin>>n;
	fp.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0){
		if(strcmpi(bk.retbno(),n)==0){
			bk.show_book();
			cout<<"\n\n enter the new book details"<<endl;
			bk.modify_book();
			int pos=1*sizeof(book);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n record updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<" record not found";
}

void modify_staff(){
	char n[7];
	int found=0;
	cout<<"\n\n modify staff record... ";
	cout<<"\n\n enter tne staff id number ";
	cin>>n;
	fp.open("staff.txt",ios::in|ios::out);
	while(fp.read((char*)&sm,sizeof(staff_members)) && found==0){
		if(strcmpi(sm.retstaffno(),n)==0){
			cout<<"\n\n enter the new staff details"<<endl;
			sm.create_staff();
			int pos=1*sizeof(staff_members);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&sm,sizeof(staff_members));
			cout<<"\n\n record updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n record not found";
}

//delete book
 void delete_staff(){
 	char n[7];
 	int flag=0;
 	cout<<"\n\n delete student....";
 	cout<<"\n\n enter  the student id number ";
 	cin>>n;
 	fp.open("student.txt",ios::in|ios::out);
 	fstream fp2;
 	fp2.open("temp.txt",ios::out);
 	fp.seekg(0,ios::beg);
 	while(fp.read((char*)&sm,sizeof(staff_members))){
 			if(strcmp(sm.retstaffno(),n)==0){
 				fp2.write((char*)&sm,sizeof(staff_members));
			 }	
			 else
			 {
			 	flag=1;
			 }
	 }
	 fp2.close();
	 fp.close();
	 remove("student.txt");
	 rename("temp.txt","student.txt");
	 if(flag==1)
	 	cout<<"\n\n record deleted..";
	else
		cout<<"\n\n not found";	 
 }
 
 void delete_book(){
	char n[7];
 	cout<<"\n\n delete book....";
 	cout<<"\n\n enter  the book number ";
 	cin>>n;
 	fp.open("book.txt",ios::in|ios::out);
 	fstream fp2;
 	fp2.open("temp.txt",ios::out);
 	fp.seekg(0,ios::beg);
 	while(fp.read((char*)&sm,sizeof(staff_members))){
 			if(strcmp(sm.retstaffno(),n)==0){
 				fp2.write((char*)&sm,sizeof(staff_members));
			 }	
	 }
	 fp2.close();
	 fp.close();
	 remove("student.txt");
	 rename("temp.txt","student.txt");
	 	cout<<"\n\n record deleted..";
}

//display book

void display_book(){
	fp.open("book.txt",ios::in);
	if(!fp){
		cout<<"error file could not open ";
		return ;
	}
	cout<<"\n\n list of books";
	while(fp.read((char*)&bk,sizeof(book))){
		bk.show_book();
	}
	fp.close();
}

// to issue a book

void book_issue(){
	char sn[7],bn[7];
	int found=0,flag=0;
	cout<<"\n\n book issue";
	cout<<"\n\n enter the student's id number";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
	fp1.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0){
		if(strcmp(st.retstid(),sn)==0){
			found=1;
			if(st.rettoken()==0){
				cout<<"enter book no";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0){
					if(strcmp(bk.retbno(),bn)==0){
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
							int pos=1*sizeof(st);
							fp.seekp(pos,ios::cur);
							fp.write((char*)&st,sizeof(student));
							cout<<"\n\n book is issued plz write date and time ";
					}
					
				}
				if(flag==0)
					cout<<"book does not exit";
					}
			else
				cout<<"you have not return the last book";
		}
	}
	if(found==0)
		cout<<"student record doesnot exist..";
	fp.close();
	fp1.close();
	
}

//to deposit the book


void book_deposit(){
	char sn[7],bn[7];
	int found=0,flag=0,day,fine;
	cout<<"\n\n book deposit";
	cout<<"\n\n enter the student's id number";
	cin>>sn;
	fp.open("student.txt",ios::in|ios::out);
	fp1.open("book.txt",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0){
		if(strcmp(st.retstid(),sn)==0){
			found=1;
			if(st.rettoken()==1){
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0){
					if(strcmp(bk.retbno(),bn)==0){
						bk.show_book();
						flag=1;
						cout<<"\n\n book deposited in days";
						cin>>day;
						if(day>15){
							fine=(day-15)*1;
							cout<<"\n\n fine"<<fine;
						}
						st.resettoken();
							int pos=1*sizeof(st);
							fp.seekp(pos,ios::cur);
							fp.write((char*)&st,sizeof(student));
							cout<<"\n\n book deposited successfully ";
					}
					
				}
				if(flag==0)
					cout<<"book does not exit";
			}
			else
				cout<<"no book is issued... plz check";
		}
	}
	if(found==0)
		cout<<"student record doesnot exist..";
	fp.close();
	fp1.close();
	
}
void book_menu(){
	int ch2;
	cout<<"\n\nBOOK Menu";
	cout<<"\n\n\n 1.create book";
	cout<<"\n\n\n 2.modify book";
	cout<<"\n\n\n 3.delete book";
	cout<<"\n\n\n 4.back to main menu";
	cin>>ch2;
	switch(ch2){
		case 1:
			write_book();
			break;
		case 2:
			modify_book();
			break;
		case 3:
			delete_book();
			break;
		case 4:
			return;
	}
	
	book_menu();
}

void staff_menu(){
	int ch2;
	cout<<"\n\nstaff Menu";
	cout<<"\n\n\n 1.create staff member";
	cout<<"\n\n\n 2.modify staff member";
	cout<<"\n\n\n 3.delete staff member";
	cout<<"\n\n\n 4.create student ";
	cout<<"\n\n\n 4.back to main menu";
	cin>>ch2;
	switch(ch2){
		case 1:
			write_staff();
			break;
		case 2:
			modify_staff();
			break;
		case 3:
			delete_staff();
			break;
		case 4:
			write_student();
			break;
		case 5:
			return;
	}
	
	staff_menu();
}


int main(){
	int choice;
	cout<<"Main Menu ";
	cout<<"\n1.Book issue";
	cout<<"\n2.Book deposit ";
	cout<<"\n3.book Menu";
	cout<<"\n4.staff menu ";
	cout<<"\n5.Exit";
	cout<<"\nChoice  1-5 numbers";
	cin>>choice;
	do{
		switch(choice){
		case 1:
			book_issue();
			break;
		case 2:
			book_deposit();
			break;
		case 3:
			book_menu();
			break;
		case 4:
			staff_menu();
			break;
		case 5:
			exit(0);
		
        }
    }
    while(choice!=4);
}
