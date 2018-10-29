#include <bits/stdc++.h>
using namespace std;
#define TIME 0

int search_refernce_table(string ref)
{
    return //map's index
}

class Person
{
    string name,address;
    int id;
    Person(string nm,string ad,int ide)
    {
        this->name=nm;
        this->address=ad;
        this->id=ide;
    }
};

class Doctor:virtual public Person
{
    string department;
    public:
    Doctor(string nm,string ad,string dept,int ide):Person(nm,ad,ide)
    {
        this->department=dept;
    }
    void Assign_Patient()
    {
        //Perform assigning to patients
        //Maintain a matrix where doctor schedules him
    }
};

class Patient:virtual public Person
{
    string reference,problem;
    public:
    Patient(string nm,string ad,string prob,int ide,string ref):Person(nm,ad,ide)
    {
        this->problem=prob;
        this->reference=ref;
        this->Assign_Doctor();
    }
    void Assign_Doctor()
    {
        if(this->reference=="Self")
        {
            cout<<"Go to general Doctor\n";
        }
        else
        {
            cout<<"Go to "<<this->reference<<" doctor\n";
            int doc_id=search_reference_table(this->reference);//searches for the match of reference and doctor id
        }
        TIME+=1;
    }
};



int main() {
	//When the second patient comes direct him to the same doctor as done by the previous done
	//Perform priority queue
	return 0;
}
