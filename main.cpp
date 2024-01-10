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
    int nWT;
    int start;
    int end;
    Node* next;

    Node(int ID, int b, int a, int p, int n, int s, int e) : procID(ID), burstTime(b), arrivalTime(a), priority(p), nWT(n), start(s), end(e), next(NULL) {}
};

//Store Results
struct Result {
	int resultID;
	int waitingTime;
    Result* resultNext;

    Result(int rID, int w) : resultID(rID), waitingTime(w), resultNext(NULL) {}
};

//circular LL
struct cNode {
    int cProcID;
    int cBurstTime;
    int cArrivalTime;
    int cPriority;
    int start;
    int end;
    int waitingT;
    int prevAT;
    cNode* cNext;

    cNode(int cID, int cB, int cA, int cP, int cS, int cE, int cW, int cPAT) : cProcID(cID), cBurstTime(cB), cArrivalTime(cA), cPriority(cP), start(cS), end(cE), waitingT(cW), prevAT(cPAT), cNext(NULL) {}
};


//Global Variables
bool preemptiveMode = false;
int schedulingMethodNum;
string schedulingMethod;
int timeQuantum = 0;
int procNumber = 0;
Node* head = NULL;
Result* resultHead = NULL;
cNode* cHead = NULL;
double averageWaitingTime;
int cTime;
int totalWaitingTime = 0;
int waitingTime = 0;
int tempNumber;

//Functions Declarations
void cpuSchedulerSimulator();
void insertNode(int procID, int burstTime, int arrivalTime, int priority, int nWT, int start, int end);
void insertcNode(int cProcID, int cBurstTime, int cArrivalTime, int cPriority, int start, int end, int waitingT);
void readFromFileAndStore();
void selectWhichMethod();
void insertResult(int resultID, int waitingTime);
void sortResults();
void pritnResults();
void emptyList();
void fcfsFunc();
void fcfsLogic();
void removeNode( Node* target);
void emptyLinkedList();
void emptyCircular();
void nonPreSJFLogic();
void nonPreSJF();
void nonPrePriorityLogic();
void nonPrePriority();
void roundRobin();
void preSJF();
void preSJFLogic();
void prePriority();
void prePriorityLogic();


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
void insertNode(int procID, int burstTime, int arrivalTime, int priority, int nWT, int start, int end) {
    Node* newNode = new Node(procID, burstTime, arrivalTime, priority, 0, 0, 0);
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

//Insert To The Circular Linked List
void insertcNode(int cProcID, int cBurstTime, int cArrivalTime, int cPriority, int start, int end, int waitingT, int prevAT) {
    cNode* newcNode = new cNode(cProcID, cBurstTime, cArrivalTime, cPriority, 0, 0, 0, 0);
    
    if (cHead == NULL) {
        cHead = newcNode;
        cHead->cNext = cHead;
    } else {
        cNode* ctemp = cHead;
        while (ctemp->cNext != cHead) {
            ctemp = ctemp->cNext;
        }
        
        ctemp->cNext = newcNode;
        newcNode->cNext = cHead;
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
        insertNode(procID, burstTime, arrivalTime, priority, 0, 0, 0);
        insertcNode(procID, burstTime, arrivalTime, priority, 0, 0, 0, 0);
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
		fcfsFunc();
	}else if(!preemptiveMode && schedulingMethodNum==3){
        nonPreSJF();
	}else if(preemptiveMode && schedulingMethodNum==3){
		preSJF();
	}else if(!preemptiveMode && schedulingMethodNum==4){
		nonPrePriority();
	}else if(preemptiveMode && schedulingMethodNum==4){
		prePriority();
	}else if(!preemptiveMode && schedulingMethodNum==5){
		roundRobin();
	}else if(preemptiveMode && schedulingMethodNum==5){
		roundRobin();
	}
}

// Sort The Results Ascending Using BubbleSort Which We Learned In The Algorthim Course
void sortResults() {
    if (!resultHead || !resultHead->resultNext) {
        return;
    }

    bool swapped;
    Result* current;
    Result* lastSorted = NULL;

    do {
        swapped = false;
        current = resultHead;

        while (current->resultNext != lastSorted) {
            if (current->resultID > current->resultNext->resultID) {
                std::swap(current->resultID, current->resultNext->resultID);
                std::swap(current->waitingTime, current->resultNext->waitingTime);
                swapped = true;
            }

            current = current->resultNext;
        }

        lastSorted = current;
    } while (swapped);
}

void pritnResults(){
	sortResults();
	
	Result* resultCurrent = resultHead;
	
	ofstream outputFile("output.txt", ios::app);
	if (preemptiveMode && schedulingMethodNum==2){
		cout<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is ON\nBut Here Is The Non-Preemptive FCFS instade: \n";
		outputFile<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is ON\nBut Here Is The Non-Preemptive FCFS instade: \n";
	}else if(!preemptiveMode && schedulingMethodNum==2){
		cout<<"Scheduling Method:"<< schedulingMethod<<endl;
        outputFile<<"Scheduling Method:"<< schedulingMethod<<endl;
	}else if(!preemptiveMode && schedulingMethodNum==5){
		cout<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is OFF\nBut Here Is The Preemptive RR instade: time_quantum = "<<timeQuantum<<endl;
		outputFile<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is OFF\nBut Here Is The Preemptive RR instade: time_quantum = "<<timeQuantum<<endl;
	}else if(preemptiveMode && schedulingMethodNum==5){
		cout<<"Scheduling Method:"<< schedulingMethod<<" time_quantum = "<<timeQuantum<<endl;
        outputFile<<"Scheduling Method:"<< schedulingMethod<<" time_quantum = "<<timeQuantum<<endl;
	}else{
		cout<<"Scheduling Method:"<< (preemptiveMode ? "preemptive " : "non-preemptive ")<< schedulingMethod<<endl;
        outputFile<<"Scheduling Method:"<< (preemptiveMode ? "preemptive " : "non-preemptive ")<< schedulingMethod<<endl;
	}
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
    emptyLinkedList();
    emptyCircular();
    readFromFileAndStore();
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
// For The Circular LL
void emptyCircular() {
    cNode* current = cHead;
    cNode* nextNode;

    do {
        nextNode = current->cNext;
        delete current;
        current = nextNode;
    } while (current != cHead);

    cHead = NULL;
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

void fcfsFunc(){
	while (head != NULL) {
        fcfsLogic();
    }
    
    emptyLinkedList();
    readFromFileAndStore();
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
}

void preSJF(){
	while(head != NULL){
	    preSJFLogic();
	}
	
	emptyLinkedList();
    readFromFileAndStore();
    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
}

void nonPrePriority(){
	while (head != NULL) {
        nonPrePriorityLogic();
    }
    
    emptyLinkedList();
    readFromFileAndStore();
    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
}

void prePriority(){
	while(head != NULL){
	    prePriorityLogic();
	}
	
	emptyLinkedList();
    readFromFileAndStore();
    averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
    pritnResults();
}

void roundRobin() {
    if (cHead == NULL) {
        cout << "Circular linked list is empty." << endl;
        return;
    }
    cNode* cCurrent = cHead;
    
    while (cCurrent->cBurstTime > 0 && cCurrent->cArrivalTime != -1){
        if (cCurrent->cArrivalTime <= cTime) {
        	
        	cCurrent->start = cTime;
            if (cCurrent->cBurstTime <= timeQuantum) {
                cTime += cCurrent->cBurstTime;
                cCurrent->prevAT = cCurrent->cArrivalTime;
                cCurrent->cArrivalTime = -1;
            } else {
                cTime += timeQuantum;
                cCurrent->cBurstTime -= timeQuantum;
            }
        }
        
		cCurrent->waitingT += cCurrent->start - cCurrent->end;
		cCurrent->end = cTime;
        cCurrent = cCurrent->cNext;

    }
    tempNumber = procNumber;
    
    while(tempNumber>0){
    	cCurrent->waitingT -= cCurrent->prevAT;
    	insertResult(cCurrent->cProcID, cCurrent->waitingT);
    	totalWaitingTime += cCurrent->waitingT;
    	cCurrent = cCurrent->cNext;
    	tempNumber--;
	}
	averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
	pritnResults();
}

//Logics 
void fcfsLogic() {
    if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    Node* current = head;
    Node* selectedProcess = NULL;

    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || current->arrivalTime < selectedProcess->arrivalTime ||
                (current->arrivalTime == selectedProcess->arrivalTime && current->procID < selectedProcess->procID)) {
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
                (current->burstTime == selectedProcess->burstTime && current->arrivalTime < selectedProcess->arrivalTime) ||
                (current->burstTime == selectedProcess->burstTime && current->arrivalTime == selectedProcess->arrivalTime && current->priority < selectedProcess->priority) ||
				(current->burstTime == selectedProcess->burstTime && current->arrivalTime == selectedProcess->arrivalTime && current->priority == selectedProcess->priority && current->procID < selectedProcess->procID)) {
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

void nonPrePriorityLogic() {
    if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    Node* current = head;
    Node* selectedProcess = NULL;

    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || (current->priority < selectedProcess->priority) ||
                (current->priority == selectedProcess->priority && current->arrivalTime < selectedProcess->arrivalTime) ||
				(current->priority == selectedProcess->priority && current->arrivalTime == selectedProcess->arrivalTime && current->procID < selectedProcess->procID)) {
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

void preSJFLogic() {
    if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    Node* current = head;
    Node* selectedProcess = NULL;
    int prevID = -1;
    
    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || current->burstTime < selectedProcess->burstTime ||
                (current->burstTime == selectedProcess->burstTime && current->arrivalTime < selectedProcess->arrivalTime) ||
                (current->burstTime == selectedProcess->burstTime && current->arrivalTime == selectedProcess->arrivalTime && current->priority < selectedProcess->priority) ||
				(current->burstTime == selectedProcess->burstTime && current->arrivalTime == selectedProcess->arrivalTime && current->priority == selectedProcess->priority && current->procID < selectedProcess->procID)) {
                selectedProcess = current;
            }
        }
        current = current->next;
    }
    
    if (selectedProcess->procID == prevID){
    	selectedProcess->burstTime--;
    	cTime++;
    	selectedProcess->end++;
    	if(selectedProcess->burstTime == 0){
    		selectedProcess->nWT -= selectedProcess->arrivalTime;
    		totalWaitingTime += selectedProcess->nWT;
    		insertResult(selectedProcess->procID, selectedProcess->nWT);
    		removeNode(selectedProcess);
		}
	}else{
		selectedProcess->start = cTime;
		selectedProcess->burstTime--;
		cTime++;
		if(selectedProcess->burstTime == 0){
    		selectedProcess->nWT -= selectedProcess->arrivalTime;
    		totalWaitingTime += selectedProcess->nWT;
    		insertResult(selectedProcess->procID, selectedProcess->nWT);
    		removeNode(selectedProcess);
		}
	}
	selectedProcess->nWT += selectedProcess->start - selectedProcess->end;
    selectedProcess->end = cTime;
    prevID = selectedProcess->procID;
}

void prePriorityLogic() {
    if (head == NULL) {
        cout << "Linked list is empty." << endl;
        return;
    }
    Node* current = head;
    Node* selectedProcess = NULL;
    int prevID = -1;
    while (current != NULL) {
        if (current->arrivalTime <= cTime) {
            if (selectedProcess == NULL || (current->priority < selectedProcess->priority) ||
                (current->priority == selectedProcess->priority && current->arrivalTime < selectedProcess->arrivalTime) ||
				(current->priority == selectedProcess->priority && current->arrivalTime == selectedProcess->arrivalTime && current->procID < selectedProcess->procID)) {
                selectedProcess = current;
            }
        }
        current = current->next;
    }
    
    if (selectedProcess->procID == prevID){
    	selectedProcess->burstTime--;
    	cTime++;
    	selectedProcess->end++;
    	if(selectedProcess->burstTime == 0){
    		selectedProcess->nWT -= selectedProcess->arrivalTime;
    		totalWaitingTime += selectedProcess->nWT;
    		insertResult(selectedProcess->procID, selectedProcess->nWT);
    		removeNode(selectedProcess);
		}
	}else{
		selectedProcess->start = cTime;
		selectedProcess->burstTime--;
		cTime++;
		if(selectedProcess->burstTime == 0){
    		selectedProcess->nWT -= selectedProcess->arrivalTime;
    		totalWaitingTime += selectedProcess->nWT;
    		insertResult(selectedProcess->procID, selectedProcess->nWT);
    		removeNode(selectedProcess);
		}
	}
	selectedProcess->nWT += selectedProcess->start - selectedProcess->end;
    selectedProcess->end = cTime;
    prevID = selectedProcess->procID;
}
