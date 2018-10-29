#include <bits/stdc++.h>
using namespace std;
#define TIME 0

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
        }
        TIME+=1;
    }
};



int main() {
	
	return 0;
}
