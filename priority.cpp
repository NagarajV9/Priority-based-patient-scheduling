#include<bits/stdc++.h>
using namespace std;

struct Patient{
    string name;
    int urgency; //The higher the number, the more urgent
    //string specialist;
    string notes;
    Patient *parent;
    Patient *left;
    Patient *right;
    Patient(string n, int u, string note){
        name=n;
        urgency=u;
        //s=specialist;
        notes=note;
    }

};

class PQueue
{
    //vector <Patient* > patientQueue;
    int arraySize; //the initial size of the array
    Patient ** patientArray; //The array that holds the structure of the heap
    Patient * largestChild(Patient* parent); //Will find and return the child of Patient * parent with the highest urgency.
    void swapPatientsByIndex(int indChild, int indParent); //Will swap the pointers at indChild and indParent
    void swapPatients(Patient *child, Patient* parent); //Will swap child and parent within the heap.

public:
    PQueue();
    ~PQueue();
    void insertNewPatient(string name, int urgency,string notes); //creates a new patient and adds it to the queue.
    Patient *pop(); //gets the root of the heap- the patient with the maximum urgency.
    void printArray(); //prints out every patient in the array, with their indexes.
    void doubleArray(); //Doubles the size of the array- this is called when you try and add a patient to a full array.
    Patient * findPatient(string name); //Will search through heap for a pointer with name "name"
    int removePatient(string name); //Will remove a patient from name- finds the pointer and index, then calls deletePatient
    int deletePatient(Patient * nextP, int patientIndex); //removes a patient and restructures the heap.
    void printPatientData(string name); //Will find a patient with name "name" and print out the name, urgency, and notes.
    void printPatientPointer(Patient * p); //Will print out the name, urgency, and notes of pointer p.
    void printPatients();//prints all the patients.

};

PQueue::PQueue(){
    //cout << "Creating new queue" << endl;
    arraySize = 10;
    patientArray=new Patient*[arraySize]; //set to ten
    for(int i=0; i< arraySize; i++)
        patientArray[i]=NULL;

}

PQueue::~PQueue(){
    for(int i=0; i< arraySize; i++){
        if(patientArray[i]!=NULL){
            delete patientArray[i];
        }
    }
   // cout << "Deleted Values!" << endl;

}

void PQueue::printPatients()
{
    for(int k=0; k < arraySize; k++)
    {
        if(patientArray[k]!=NULL){
            printPatientPointer(patientArray[k]);
        }
    }

}

void PQueue::printArray()
{
    for(int k=0; k < arraySize; k++)
    {
        if(patientArray[k]!=NULL)
        {
            cout << "patientArray[" << k << "]: " << patientArray[k]->name;
            cout <<", urgency: " << patientArray[k]->urgency << endl;
        }
    }

}


void PQueue::printPatientData(string name)
{
        Patient * p = findPatient(name);
        if(p==NULL){
            cout<< "Patient not found." << endl;
        }
        else{
            printPatientPointer(p);
        }
}

void PQueue::printPatientPointer(Patient * p)
{
    cout << "^^^^^^^^^^^^^^" << endl;
    cout << "Patient Name: " << p->name << endl;
    cout << "Urgency: " << p->urgency << endl;
    //cout << "Specialist: " << p->specialist << endl;
    cout << "Notes: " << p->notes << endl;
    cout << "^^^^^^^^^^^^^^" << endl;
}

void PQueue::insertNewPatient(string name, int urgency, string notes){
    Patient* p=new Patient(name, urgency, notes);
    //cout << "New patient: " << p->name << endl;
    Patient* prevP=patientArray[1]; //the root of the heap
    int index=1;
    if(prevP==NULL){
        //cout << "Root" << endl;
    }
    while(prevP!=NULL&&index<arraySize){
        index++;

        prevP=patientArray[index];
    }

    //cout << "Index: " << index << endl;

    //Index is now equal to the next empty spot in the array.
    if(index==1){ //heap is empty
        patientArray[index] = p;
        p->parent=NULL;
        p->left=NULL;
        p->right=NULL;
    }
    else{
        if(index == arraySize){
            doubleArray();
        }
        patientArray[index]=p;
        Patient *parent=patientArray[index/2];
        if(parent->left==NULL){
            parent->left=p;
        }
        else if(parent->right==NULL){
            parent->right=p;
        }
        else{
            cout << "Error finding parent!" << endl;
        }
        p->parent=parent;
        p->left=NULL;
        p->right=NULL;
        if(parent!=NULL){
            //cout << "Parent: " << parent->name << endl;
        }
        //else
            //cout << "Parent is null. Parent index: " << index/2 <<endl;
        //to maintain heap properties: The parent has to have higher urgency

        while(parent!=NULL&&parent->urgency < p->urgency){
            /*cout << "Parent: " << parent->name << " Parent urgency: " <<parent->urgency << ", child urgency: " << p->urgency << endl;
            cout << "Swapping" << endl;
            cout << "indChild: " << index << " indParent: " << index/2 << endl;
            cout << "Child: " << p->name << " Parent: " << parent->name << endl;*/

            swapPatientsByIndex(index, index/2);
            if(p->parent!=NULL)
            {
                parent=p->parent;
                //cout << "Setting new parent to " << parent->name << endl;
            }
            else
                parent=NULL;
        }



    }
    /*for(int k=0; k < arraySize; k++){
        if(patientArray[k]!=NULL)
            cout << "patientArray[" << k << "]: " << patientArray[k]->name << endl;
        else
            cout << "patientArray[" << k << "]: NULL" << endl;
    }*/

}


//Will swap the two patients within the array- used for maintaining heap rules
void PQueue::swapPatients(Patient* child, Patient* parent){
    int ch=-1, pa=-1;
    for(int i=0; i< arraySize; i++){
        if(patientArray[i]==child){
            ch=i;
        }
        if(patientArray[i]==parent){
            pa=i;
        }
    }
    if(ch==-1||pa==-1){
        cout << "One or both not found in swapPatients" << endl;
    }
    else{
        swapPatientsByIndex(ch, pa);
    }

}

//will swap two elements in the array at indexes indChild and indParent
void PQueue::swapPatientsByIndex(int indChild, int indParent){
    //cout << "Starting swap" << endl;
    Patient * child=patientArray[indChild];
    Patient * parent=patientArray[indParent];
    if(child==NULL){
        cout << "Child null" << endl;
    }
    if(parent==NULL){
        cout << "Parent null" << endl;
    }
    //cout << "parent: " << parent->name << " child: " << child->name << endl;
    Patient *otherChild;
    bool left=false;
    if(parent->left==child){
        //cout << "child to left" << endl;
        otherChild=parent->right;
        left=true;
    }
    else{
        otherChild=parent->left;
    }
    //cout << "Setting parents" << endl;
    child->parent=parent->parent;
    if(parent->parent!=NULL){
        if(parent->parent->left==parent)
            parent->parent->left=child;
        else
            parent->parent->right=child;
    }
    parent->parent=child;
    //cout << "Parents set" << endl;
    if(child->left!=NULL)
        child->left->parent=parent;
    if(child->right!=NULL)
        child->right->parent=parent;
    parent->left=child->left;
    parent->right=child->right;
    //cout << "Children set" << endl;
    if(otherChild!=NULL)
        otherChild->parent=child;
    if(left){
        child->left=parent;
        child->right=otherChild;
    }
    else{
        child->right=parent;
        child->left=otherChild;
    }
    //cout << "Setting in array" << endl;
    patientArray[indChild]=parent;
    patientArray[indParent]=child;
    //cout << "Swapped " << parent->name << " with " << child->name << endl;


}


//Will return the patient with the greatest urgency, and remove it from the queue.
Patient * PQueue::pop(){
    Patient * nextP = patientArray[1]; //the root of the array, the patient with max urgency
    if(nextP==NULL){
        //cout << "Queue empty (pop)" << endl;
        return NULL;
    }
    int i=deletePatient(nextP, 1);
    if(i==0){
        //cout << "Successfully deleted" << endl;
    }

    return nextP;

}

//Deletes patient nextP at indexToDelete
//returns 0 if successful, 1 otherwise
int PQueue::deletePatient(Patient * nextP, int indexToDelete){
    if(indexToDelete > arraySize){
        cout << "Error: Index greater than array size" << endl;
        return 1;
    }
    Patient * endOfArray=patientArray[1];
    int i=1;
    while(patientArray[i+1]!=NULL&&i<arraySize){
        i++;
        endOfArray=patientArray[i];
    }

    //cout << "End of array: " << endOfArray->name <<endl;
    if(i!=1){ //if there is more than one element in the heap

        patientArray[indexToDelete]=endOfArray;
        patientArray[i]=NULL;
        //cout << "Setting array at " << i << " to null. " << endl;
        if(endOfArray->parent->left==endOfArray){
            endOfArray->parent->left=NULL;
        }
        else
            endOfArray->parent->right=NULL;
        endOfArray->left=nextP->left;
        if(endOfArray->left!=NULL){
            //cout << "new left child: " << endOfArray->left->name << endl;

        }
        else
            //cout << "Left child null." << endl;
        if(endOfArray->right!=NULL){
            //cout << "new right child: " << endOfArray->right->name << endl;

        }
       // else
            //cout << "Right child null." << endl;
        endOfArray->right=nextP->right;
        endOfArray->parent=nextP->parent;
        //If the new root has children that are higher urgency (Should always be true, basically)
        Patient * largerChild=NULL;
        largerChild= largestChild(endOfArray);

        while(largerChild!=NULL){
           // cout << "New Root: " << endOfArray->name << ", largest Child: " << largerChild->name << endl;
            if(largerChild->urgency > endOfArray->urgency){
                //cout << "Swapping " << endOfArray->name << " and " << largerChild->name <<endl;
                swapPatients(largerChild, endOfArray);
                largerChild = largestChild(endOfArray);
            }
            else{
                largerChild=NULL;
            }

        }

    }
    else{ //If there is only one patient in the array
        patientArray[1]=NULL;

    }


    return 0;

}
 //returns one if unsuccessful. Will delete a patient based off of a name.
int PQueue::removePatient(string name){
    Patient *p=NULL;
    int index=0;
    for(int i=0; i<arraySize; i++){
        if(patientArray[i]!=NULL && patientArray[i]->name == name){
            p=patientArray[i];
            index=i;
        }
    }
    if(p!=NULL){
        return deletePatient(p, index);
    }

    return 1;
}


Patient* PQueue::largestChild(Patient* parent){
    Patient* largerChild=NULL;
    if(parent->left!=NULL||parent->right!=NULL){

            if(parent->left!=NULL){
                if(parent->right!=NULL){
                    if(parent->left->urgency > parent->right->urgency) //the left is larger
                        largerChild = parent->left;
                    else
                        largerChild = parent->right;

                }
                else //If left exist and right is null
                    largerChild = parent->left;

            }
            else //If right exists and left is null
                largerChild = parent->right;

        }
    return largerChild;

}

void PQueue::doubleArray(){
    Patient ** temp=new Patient*[arraySize*2];
    for(int i=0; i<arraySize; i++){
        temp[i]=patientArray[i];

    }
    for(int k=arraySize; k<arraySize*2; k++){
        temp[k]=NULL;
    }
    delete[] patientArray;
    patientArray=temp;
    arraySize=arraySize*2;
    //cout << "Array doubled" << endl;

}

Patient * PQueue::findPatient(string name)
{
    Patient * p=NULL;
    for(int i=0; i<arraySize; i++){
        if(patientArray[i]!=NULL && patientArray[i]->name == name){
            p=patientArray[i];
        }
    }
    return p;
}





int main(){

    PQueue q;
    string s="";
    int i;
    do {
        cout << "======Main Menu======" << endl;
        cout << "1. Enter a new patient" << endl; //To add a new patient to the heap
        cout << "2. Print patients" << endl; //Will print out the names and urgencies of all the patients currently in the heap
        //Will return and remove the patient with the highest urgency from the heap. Used for getting the next patient who needs to
        //be treated.
        cout << "3. Get next patient" << endl;
        cout << "4. Remove patient from queue" << endl; //Will remove a patient by name.
        cout << "5. Find a patient" << endl; //Will print out the info for a patient searched by name.
        cout << "6. Edit patient" << endl; //Will delete an entered patient and allow you to re-enter the data.
        cout << "7. Quit" << endl;
        cin >> s;
        try{
            i=stoi(s);
        }
        catch(...){
            i=0;
            cout << "Error: Please enter an integer." << endl;
        }
        switch(i){
            case 1:{
                bool correct=false;
                string name, notes, u;
                int urgency=-1;
                cin.ignore();
                while(!correct){

                    cout << "Please enter the name of the patient. " << endl;
                    getline(cin, name);
                    cin.clear();
                    while(urgency==-1){
                        cout << "Please enter the urgency as a number. The higher the number, the more urgency and the earlier in the queue." << endl;
                        getline(cin, u);
                        try{
                            urgency=stoi(u);

                        }
                        catch(...){
                            urgency=-1;
                            cout << "Error: Please enter an integer for the urgency." << endl;
                        }
                    }
                    //cout << "Please enter the specialist for the patient. If none, enter 'none'" << endl;
                    //getline(cin, special);
                    cout << "Please enter any special notes about the patient. If none, enter 'none'" << endl;
                    getline(cin, notes);
                    bool valid = false;
                    do {
                        cout << "Is this information correct? (Y) or (N)" << endl;
                        cout << "Name: " << name << ", Urgency: " << urgency << ", notes: " << notes << endl;
                        string check;
                        getline(cin, check);
                        if(check=="no"||check=="n"||check=="NO"||check=="N"||check=="No"){
                            urgency = -1;
                            cout << "Please re-enter the information." << endl;
                            valid = true;
                        }
                        else if (check=="yes"||check=="y"||check=="YES"||check=="Y"||check=="Yes"){
                            correct=true;
                            valid = true;
                        }
                        else {
                            cout<<"Please enter a valid input"<<endl;
                        }

                    }
                    while (!valid);

                }

                q.insertNewPatient(name, urgency, notes); //Inserts the new patient into the heap
                break;

            }
            case 2:{
                q.printPatients();
                break;

            }
            case 3:{
                cout << "Next Patient: " << endl;
                Patient * p=q.pop();
                if(p==NULL){
                    cout << "Queue Empty." << endl;
                }
                else{
                    q.printPatientPointer(p); //Will print out name, urgency, and notes.
                }
                break;

            }
            case 4:{
                cout << "Enter a patient name. "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);
                int removed=q.removePatient(findName);
                if(removed!=0){
                    cout << "Error removing patient." << endl;
                }
                else{
                    cout << "Successfully removed patient." << endl;
                }
                break;

            }
            case 5:{
                cout << "Enter a patient name. "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);
                q.printPatientData(findName);
                break;

            }
            case 6:{
                cout << "Enter a patient name. "  << endl;
                string findName;
                cin.ignore();
                getline(cin, findName);

                q.removePatient(findName);

                bool correct=false;
                string name,  notes, u;
                int urgency;
                while(!correct){

                    cout << "Please enter the name of the patient. " << endl;
                    getline(cin, name);
                    cout << "Please enter the urgency as a number. The higher the number, the more urgency and the earlier in the queue." << endl;
                    getline(cin, u);
                    urgency=stoi(u);
                    //cout << "Please enter the specialist for the patient. If none, enter 'none'" << endl;
                    //getline(cin, special);
                    cout << "Please enter any special notes about the patient. If none, enter 'none'" << endl;
                    getline(cin, notes);
                    cout << "Is this information correct? (Y) or (N)" << endl;
                    cout << "Name: " << name << ", Urgency: " << urgency << ", notes: " << notes << endl;
                    string check;
                    getline(cin, check);
                    if(check=="no"||check=="n"||check=="NO"||check=="N"){
                        cout << "Please re-enter the information." << endl;
                    }
                    else
                        correct=true;

                }
                cout << "Inserting" << endl;
                cout << "***********" << endl;
                q.insertNewPatient(name, urgency, notes);
                break;

            }
        }
    }
    while(i!=7);
    cout << "Goodbye!" << endl;

    return 0;
}
