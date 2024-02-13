#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>

using namespace std;

struct student{  //true
	string name;
	int id;
	char gender;
	float gpa;
    //Define struct student with four member (name ,id , gender, gpa);
    
};

struct course{
	string name;
	int id;
	vector<string> lecture_list;
	vector<student *> student_list;
};

student * findstudent(vector<student> &allstudents,int key){ //There is something wrong in this line.   true &allstudents
	for(unsigned int i = 0; i < allstudents.size(); i++){
		if(allstudents[i].id  == key) return &allstudents[i];
	}
	return 0;
}

void printreport(vector<course> allcourses){
	for(unsigned int i = 0;i < allcourses.size(); i++){
		cout << "-----------------------------------------------------------------------------\n";
		cout << left << setw(20);
		cout << "Course:" << allcourses[i].name << " ("<< allcourses[i].id << ")\n\n";
		cout << left << setw(20);
		cout << "Lecturers:";
		for(unsigned int j = 0; j < allcourses[i].lecture_list.size();j++){
			if(j != 0) cout << ", ";
			cout << allcourses[i].lecture_list[j];
		}
		cout << "\n\n";
		cout << left << setw(20);
		cout << "Students:";
		for(unsigned int j = 0; j < allcourses[i].student_list.size();j++){
			if(j != 0) cout << left << setw(20) << " ";
			cout << left << setw(20) << allcourses[i].student_list[j]->name;
			cout << left << setw(10) << allcourses[i].student_list[j]->id;
			cout << left << setw(3) << allcourses[i].student_list[j]->gender;
			cout << left << setw(5) << setprecision(2) << fixed << allcourses[i].student_list[j]->gpa << "\n";
		} 
		
	}
	cout << "-----------------------------------------------------------------------------\n";
}

int main(){
	ifstream student_file("students.txt");
	ifstream course_file("courses.txt");
	vector<student> allstudents;
	vector<course> allcourses;
	
	string textline;
	while(getline(student_file,textline)){
		student s; 

		char name[50]; //
		sscanf(textline.c_str(),"%[^,],%d,%c,%f" , name, &s.id, &s.gender, &s.gpa); // string ใช้ไม่ได้ เปลี่ยนเป็น char[50] มันไม่ใช่ค่าใส่ค่า 
		s.name = name;   //ให้รู้ค่าทีหลังได้



		allstudents.push_back(s); 		
	}
	
int state = 1;
	while(getline(course_file,textline)){
		if(state == 1){
			course c;
			int loc = textline.find_first_of('(');
			c.name = textline.substr(0,loc-1);
			c.id = atof(textline.substr(loc+1,5).c_str());
			getline(course_file,textline);
			allcourses.push_back(c);
			state = 2;			
		}else if(state == 2){
			if(textline == "> Students"){
				state = 3;
			}else{
		
			 allcourses.back().lecture_list.push_back(textline);  //allcourse lecture push
			    //Append (push_back) textline to lecture_list[] of the recently added course in allcourses[];
			    //allcourses.back() is used to access the last element (the most recently added element)
				//in the allcourses vector. It returns a reference to this last element. Then, student_list.push_back(p)
				// is called on this last element to add a new element to the student_list vector.
			}			
		}else{
			if(textline == "---------------------------------------"){
				state = 1;
			}else{
				student *p = findstudent(allstudents,atof(textline.c_str()));
 				allcourses.back().student_list.push_back(p);
				//Append (push_back) p to student_list of the recently added course in allcourses[];
				
			}
		}
	}
	printreport(allcourses);
	
}
