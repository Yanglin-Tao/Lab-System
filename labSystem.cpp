/*
  rec06_start.cpp
 */

// Modeling a little part of the School of Engineering CS lab administration
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// create class Section, nesting class TimeSlot and class StudentRecord
class Section{
    friend ostream& operator << (ostream& os, const Section& someSection);
public:
    Section(const string& section, const string& day, int time) :
    sectionName(section), sectionTimeSlot(day, time){
    }
    
    size_t getSectionSize() const{
        return vectorStudentRecord.size();
    }
    
    void addStudent(const string& studentName){
        StudentRecord* studentRecordPointer = new StudentRecord(studentName);
        vectorStudentRecord.push_back(studentRecordPointer);
    }
    // asking student record to update the grades
    void addStudentGrade(const string& studentName, int grade, int week){
        for(size_t i = 0; i < vectorStudentRecord.size(); i++){
            if(vectorStudentRecord[i]->getStudentName() == studentName){
                vectorStudentRecord[i]->updateStudentGrade(week, grade);
                break;
            }
        }
        
    }
    
    // destructor
    ~Section(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        for(size_t i = 0; i < vectorStudentRecord.size(); i++){
            cout << "Deleting " << vectorStudentRecord[i]->getStudentName() << endl;;
            delete vectorStudentRecord[i];
            vectorStudentRecord[i] = nullptr;
        }
    }

    
    // copy constructor
    
    Section(const Section& anotherSection) :
    sectionName(anotherSection.sectionName),
    sectionTimeSlot(anotherSection.sectionTimeSlot){
        for(size_t i = 0; i < anotherSection.vectorStudentRecord.size(); i++){
            vectorStudentRecord.push_back
            (new StudentRecord(*anotherSection.vectorStudentRecord[i]));
        }
    }
    
    
    class TimeSlot{
        friend ostream& operator << (ostream& os, const Section::TimeSlot& someTimeSlot);
    public:
        TimeSlot(const string& day, int time) : weekDay(day), startTime(time){
        }
        
    private:
        string weekDay;
        int startTime;
    };
    
    class StudentRecord{
        friend ostream& operator << (ostream& os, const Section::StudentRecord&
                                     someStudentRecord);
    public:
        StudentRecord(const string& studentName) :
        studentName(studentName), studentRecord(14,-1){
        }
        const string& getStudentName() const{
            return studentName;
        }
        
        const vector<int>& getStudentRecord() const{
            return studentRecord;
        }
        // update student grades
        void updateStudentGrade(int week, int grade){
            studentRecord[week - 1] = grade;
        }
        
    
    private:
        string studentName;
        vector<int> studentRecord;
    };
    
private:
    string sectionName;
    TimeSlot sectionTimeSlot;
    vector<StudentRecord*> vectorStudentRecord;
    
};

class LabWorker{
    friend ostream& operator << (ostream& os, const LabWorker& someLabWorker);
public:
    LabWorker(const string& name) : labWorkerName(name), labWorkerSection(nullptr){
    }
    
    void addSection(Section& someSection){
        labWorkerSection = &someSection;
    }
    // asking section to add student grades
    void addGrade(const string& studentName, int grade, int week){
        if(labWorkerSection != nullptr){
            labWorkerSection -> addStudentGrade(studentName, grade, week);
        }

    }
    
private:
    string labWorkerName;
    Section* labWorkerSection;
    
};


// output operator for LabWorker class
ostream& operator << (ostream& os, const LabWorker& someLabWorker){
    os << someLabWorker.labWorkerName;
    if(someLabWorker.labWorkerSection == nullptr){
        os << " does not have a section";
    }
    else if(someLabWorker.labWorkerSection != nullptr){
        os << " has " << *someLabWorker.labWorkerSection;
    }
    return os;
}

// output operator for TimeSlot class
ostream& operator << (ostream& os, const Section::TimeSlot& someTimeSlot){
    os << "Time slot: ";
    os << "[Day: " << someTimeSlot.weekDay;
    if(someTimeSlot.startTime < 12){
        os << ", Start time: " << someTimeSlot.startTime << "am]";
    }
    else if(someTimeSlot.startTime > 12){
        os << ", Start time: " << someTimeSlot.startTime - 12 << "pm]";
    }
    return os;
}


// output operator for StudentRecord class
ostream& operator << (ostream& os, const Section::StudentRecord&
                      someStudentRecord){
    os << "Name: " << someStudentRecord.studentName << ", " << "Grades: ";
    for(size_t i = 0; i < someStudentRecord.studentRecord.size(); i++){
        os << someStudentRecord.studentRecord[i]<< " ";
    }
    os << endl;
    return os;
}

// output operator for Section class
ostream& operator << (ostream& os, const Section& someSection){
    os << "Section: " << someSection.sectionName << ", "
    << someSection.sectionTimeSlot;
    os << ", Students: " << endl;
    if(someSection.vectorStudentRecord.size() == 0){
        os << "none";
    }
    for(size_t i = 0; i < someSection.vectorStudentRecord.size();i++)
        os << *(someSection.vectorStudentRecord[i]);
    return os;
}

// function prototype
void doNothing(Section sec);

//Test code
void doNothing(Section sec) {
    cout << sec << endl;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main


