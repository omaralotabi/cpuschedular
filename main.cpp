#include <iostream>
#include <string>

using namespace std;
//Universal Variables Will Be Here
bool preemptiveMode = false;
int schedulingMethodNum;
int timeQuantum = 0;
//End Of Universal Variables

//Functions Declarations
void cpuSchedulerSimulator();
//End Of Functions Declarations

int main() {
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
				}
                break;
            case 2:
                preemptiveMode = !preemptiveMode;
                break;
            case 3:
                // will do 
                break;
            case 4:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}