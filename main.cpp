#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Linked List To Store Whats Been Readed From The input.txt File
struct Node {
	int procID;
    int burstTime;
    int arrivalTime;
    int priority;
    Node* next;

    Node(int ID, int b, int a, int p) : procID(ID), burstTime(b), arrivalTime(a), priority(p), next(NULL) {}
};

//store 
struct Result {
	int resultID;
	int waitingTime;
    Result* resultNext;

    Result(int rID, int w) : resultID(rID), waitingTime(w), resultNext(NULL) {}
};


//Global Variables
bool preemptiveMode = false;
int schedulingMethodNum;
string schedulingMethod;
int timeQuantum = 0;
int procNumber = 0;
Node* head = NULL;
Result* resultHead = NULL;
double averageWaitingTime;
int cTime;
int totalWaitingTime = 0;
int waitingTime = 0;

//Functions Declarations
void cpuSchedulerSimulator();
void insertNode(int procID, int burstTime, int arrivalTime, int priority);
void readFromFileAndStore();
void selectWhichMethod();
void insertResult(int resultID, int waitingTime);
void pritnResults();
void emptyList();
void fcfsFunc();
void removeNode( Node* target);
void emptyLinkedList();
void nonPreSJFLogic();
void nonPreSJF();
void nonPrePriorityLogic();
void nonPrePriority();


int main() {
	readFromFileAndStore();
    cpuSchedulerSimulator();
    
    return 0;
}

void cpuSchedulerSimulator() {

    while (true) {
        cout<<"\nCPU Scheduler Simulator\n";
        cout<<"-----------------------------\n";
        cout<<"1) Scheduling Method ";
        cout<<"( "<< schedulingMethod<<" )"<<"\n";
        cout<<"2) Preemptive Mode ";
        cout<<"( " << (preemptiveMode ? "ON" : "OFF") << " )\n";
        cout<<"3) Show Result\n";
        cout<<"4) End Program\n";
        cout<<"-----------------------------\n";
        cout<<"Option > ";

        int userChoice;
        cin>>userChoice;

        switch (userChoice) {
            case 1:
                cout<<"Choose a scheduling method:\n";
                cout<<"-----------------------------\n";
                cout<<"1) NONE\n";
                cout<<"2) FCFS\n";
                cout<<"3) SJF\n";
                cout<<"4) Priority\n";
                cout<<"5) RR (Round Robin)\n";
                cout<<"-----------------------------\n";
                cout<<"Enter your choice number: ";
                cin>>schedulingMethodNum;
                
                if (schedulingMethodNum == 5) {
                    cout << "Enter time quantum value: ";
                    cin >> timeQuantum;
                }
				                
                if (schedulingMethodNum == 1){
                	schedulingMethod = "NONE";
				}else if(schedulingMethodNum == 2){
					schedulingMethod = "FCFS";
				}else if(schedulingMethodNum == 3){
					schedulingMethod = "SJF";
				}else if(schedulingMethodNum == 4){
					schedulingMethod = "Priority";
				}else if(schedulingMethodNum == 5){
					schedulingMethod = "RR";
				}else{
					cout << "Invalid choice. Please try again.\n";
				}
                break;
            case 2:
                preemptiveMode = !preemptiveMode;
                break;
            case 3:
            	selectWhichMethod();
                break;
            case 4:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

//Insert From The Input File (Insert Back)
void insertNode(int procID, int burstTime, int arrivalTime, int priority) {
    Node* newNode = new Node(procID, burstTime, arrivalTime, priority);
    if (head == NULL) {
        head = newNode;
        procNumber++;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        procNumber++;
    }
}

//Insert The Output Of Scheduling Methods (Insert Back)
void insertResult(int resultID, int waitingTime) {
    Result* newResult = new Result(resultID, waitingTime);
    if (resultHead == NULL) {
        resultHead = newResult;
    } else {
        Result* resultCurrent = resultHead;
        while (resultCurrent->resultNext != NULL) {
            resultCurrent = resultCurrent->resultNext;
        }
        resultCurrent->resultNext = newResult;
    }
}

void readFromFileAndStore() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr<<"Error opening input.txt file."<<endl;
        return;
    }
    
    int procID = 1;
    int burstTime, arrivalTime, priority;
    char colon;

    while (inputFile >> burstTime >> colon >> arrivalTime >> colon >> priority) {
        insertNode(procID, burstTime, arrivalTime, priority);
        procID++;
    }
    inputFile.close();

}

void selectWhichMethod(){
	if(schedulingMethodNum==1){
		cout<<"None Of the Method Were Chosen";
	}else if(!preemptiveMode && schedulingMethodNum==2){
		fcfsFunc();
	}else if(preemptiveMode && schedulingMethodNum==2){
		cout<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is ON\n";
	}else if(!preemptiveMode && schedulingMethodNum==3){
        nonPreSJF();
	}else if(preemptiveMode && schedulingMethodNum==3){
		
	}else if(!preemptiveMode && schedulingMethodNum==4){
		nonPrePriority();
	}else if(preemptiveMode && schedulingMethodNum==4){
		
	}else if(!preemptiveMode && schedulingMethodNum==5){
		cout<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is OFF\n";
	}else if(preemptiveMode && schedulingMethodNum==5){
		
	}
}


void pritnResults(){
	Result* resultCurrent = resultHead;
	
	ofstream outputFile("output.txt", ios::app);
    cout<<"Scheduling Method:"<< (preemptiveMode ? "preemptive" : "non-preemptive ")<< schedulingMethod<<"\n";
    outputFile<<"Scheduling Method:"<< (preemptiveMode ? "preemptive" : "non-preemptive ")<< schedulingMethod<<"\n";
    cout<<"Process Waiting Times:\n";
    outputFile<<"Process Waiting Times:\n";
    
    while(resultCurrent){
    	cout<<"P"<<resultCurrent->resultID<<": "<<resultCurrent->waitingTime<<" ms\n";
        outputFile<<"P"<<resultCurrent->resultID<<": "<<resultCurrent->waitingTime<<" ms\n";
        
        resultCurrent = resultCurrent->resultNext;
	}
	cout<<"Average Waiting Time: "<<averageWaitingTime<<" ms\n";
    outputFile<<"Average Waiting Time: "<<averageWaitingTime<<" ms\n";
    
    averageWaitingTime = 0;
    cTime = 0;
    waitingTime = 0;
    totalWaitingTime = 0;
    outputFile.close();
    emptyList();
}
//For The Result LL
void emptyList() {
    while (resultHead != NULL) {
        Result* temp = resultHead;
        resultHead = resultHead->resultNext;
        delete temp;
    }
}
//For The Main LL
void emptyLinkedList() {
    Node* current = head;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    
    head = NULL;
    procNumber = 0;
}

void nonPreSJFLogic() {
    if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }

    Node* current = head;
    Node* selectedProcess = NULL;

    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || current->burstTime < selectedProcess->burstTime ||
                (current->burstTime == selectedProcess->burstTime && current->priority < selectedProcess->priority) ||
                (current->burstTime == selectedProcess->burstTime && current->priority == selectedProcess->priority && current->arrivalTime < selectedProcess->arrivalTime)) {
                selectedProcess = current;
            }
        }
        current = current->next;
    }


    	waitingTime = cTime - selectedProcess->arrivalTime;
    	insertResult(selectedProcess->procID, waitingTime);
    	totalWaitingTime +=waitingTime;
        cTime += selectedProcess->burstTime;
        removeNode(selectedProcess);

}

void removeNode( Node* target) {
    if (head == target) {
        head = target->next;
        delete target;
        return;
    }

    Node* current = head;
    while (current != NULL && current->next != target) {
        current = current->next;
    }

    if (current != NULL) {
        current->next = target->next;
        delete target;
    }
    procNumber--;
}

void nonPrePriorityLogic() {
    if (head == NULL) {
        std::cout << "Linked list is empty." << endl;
        return;
    }

    Node* current = head;
    Node* selectedProcess = NULL;

    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || (current->priority < selectedProcess->priority) ||
                (current->priority == selectedProcess->priority && current->arrivalTime < selectedProcess->arrivalTime)) {
                selectedProcess = current;
            }
        }
        current = current->next;
    }


    	waitingTime = cTime - selectedProcess->arrivalTime;
    	insertResult(selectedProcess->procID, waitingTime);
    	totalWaitingTime +=waitingTime;
        cTime += selectedProcess->burstTime;
        removeNode(selectedProcess);

}

void fcfsFunc() {
	if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    Node* current = head;
    
    while (current) {
        if (current->arrivalTime > cTime) {
            cTime = current->arrivalTime;
        }

        waitingTime = cTime - current->arrivalTime;
        totalWaitingTime += waitingTime;
        insertResult(current->procID, waitingTime);
        
        cTime += current->burstTime;
        current = current->next;
    }
    

    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
}

void nonPreSJF(){
	while (head != NULL) {
        nonPreSJFLogic();
    }
    
    emptyLinkedList();
    readFromFileAndStore();
    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
    cout<<procNumber;
}

void nonPrePriority(){
	while (head != NULL) {
        nonPrePriorityLogic();
    }
    
    emptyLinkedList();
    readFromFileAndStore();
    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
    cout<<procNumber;
}

