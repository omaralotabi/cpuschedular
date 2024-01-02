#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Linked List To Store Whats Been Readed From The input.txt File
struct Node {
    int burstTime;
    int arrivalTime;
    int priority;
    Node* next;

    Node(int b, int a, int p) : burstTime(b), arrivalTime(a), priority(p), next(NULL) {}
};


//Global Variables
bool preemptiveMode = false;
int schedulingMethodNum;
int timeQuantum = 0;
int procNumber = 0;
Node* head = NULL;


//Functions Declarations
void cpuSchedulerSimulator();
void insertNode(int burstTime, int arrivalTime, int priority);
void readFromFileAndStore();
void selectWhichMethod();
void fcfsFunc();


int main() {
	readFromFileAndStore();
    cpuSchedulerSimulator();
    
    return 0;
}

void cpuSchedulerSimulator() {
    string schedulingMethod;

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

//Performing Insert Back
void insertNode(int burstTime, int arrivalTime, int priority) {
    Node* newNode = new Node(burstTime, arrivalTime, priority);
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

void readFromFileAndStore() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr<<"Error opening input.txt file."<<endl;
        return;
    }


    int burstTime, arrivalTime, priority;
    char colon;

    while (inputFile >> burstTime >> colon >> arrivalTime >> colon >> priority) {
        insertNode(burstTime, arrivalTime, priority);
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
		
	}else if(preemptiveMode && schedulingMethodNum==3){
		
	}else if(!preemptiveMode && schedulingMethodNum==4){
		
	}else if(preemptiveMode && schedulingMethodNum==4){
		
	}else if(!preemptiveMode && schedulingMethodNum==5){
		cout<<"This Metod Can Not Be Ipmlemented While The Preemptive Mode Is OFF\n";
	}else if(preemptiveMode && schedulingMethodNum==5){
		
	}
}


void fcfsFunc() {
	
    Node* current = head;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int count=1;
    ofstream outputFile("output.txt", ios::app);
    cout<<"Scheduling Method: First Come First Served\n";
    outputFile<<"Scheduling Method: First Come First Served\n";
    cout<<"Process Waiting Times:\n";
    outputFile<<"Process Waiting Times:\n";
    
    while (current) {
        if (current->arrivalTime > currentTime) {
            currentTime = current->arrivalTime;
        }

        int waitingTime = currentTime - current->arrivalTime;
        totalWaitingTime += waitingTime;
        
        cout<<"P"<<count<<": "<<waitingTime<<" ms\n";
        outputFile<<"P"<<count<<": "<<waitingTime<<" ms\n";
        
        currentTime += current->burstTime;
        current = current->next;
        count++;
    }

    if (procNumber > 0) {
        double averageWaitingTime = static_cast<double>(totalWaitingTime) / procNumber;
        cout<<"Average Waiting Time: "<<averageWaitingTime<<" ms\n";
        outputFile<<"Average Waiting Time: "<<averageWaitingTime<<" ms\n";
    }
    outputFile.close();
}