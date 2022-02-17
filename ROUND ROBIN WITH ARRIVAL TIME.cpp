#include <iostream>
#include <vector>

using namespace std;

static int timer = 0;
int timequanta = 0;
static int pno = 0;
int n;

class Process {
public:
    int p_no = 0;
    int arrival_time = 0;
    int burst_time = 0;
    int completion_time = 0;
    int turn_around_time = 0;
    int waiting_time = 0;
    int exit_time = 0;
    int OG_burst_time = 0;

    bool add = 0;

    Process(){
        p_no = pno + 1;
        pno++;
    }

    void execute(){
        if (burst_time > timequanta){
            timer = timer + timequanta;
            burst_time = burst_time - timequanta;
        }

        else if (burst_time <= timequanta){
            timer = timer + burst_time;
            burst_time = 0;
        }
    }
};

    vector <Process> allprocess;
    vector <Process*>que;


void exchange(Process * p1, Process * p2);
void checkifque0();
void sortqueBT();
void shuffleque();
bool anyleft();
void addavailabletoque();
void sortqueBT();
void printer(Process pro);
void printerheader();
void sortAP_P_NO();

int main()
{

    cout << "Enter Total Number Of Processes\n";
    cin >> n;

    cout << "Enter Time Quanta -> ";
    cin >> timequanta;

    vector <Process> fallprocess (n);

    for (int i = 0; i < fallprocess.size(); i++){
        allprocess.push_back(fallprocess[i]);
    }

    for (int i = 0; i < n; i++){                        //take arrival time
        cout << "Enter Arrival Time Of Process " << allprocess[i].p_no << endl;
        cin >> allprocess[i].arrival_time;
    }

    cout << endl;

    for (int i = 0; i < n; i++){                        //take burst time
        cout << "Enter Burst Time Of Process " << allprocess[i].p_no << endl;
        cin >> allprocess[i].burst_time;
        allprocess[i].OG_burst_time = allprocess[i].burst_time;
    }

while (anyleft()){

    if (que.size())
        addavailabletoque();
    else
        checkifque0();

    cout << timer << " ";
    que[0]->execute();
    cout << "|P" << que[0]->p_no << "| ";
    cout << timer << "   ";
    addavailabletoque();
    shuffleque();

    if ( que[que.size() - 1]->burst_time == 0 ){
         que[que.size() - 1]->completion_time = timer;
         que[que.size() - 1]->exit_time = timer;
         que[que.size() - 1]->turn_around_time = que[que.size() - 1]->exit_time - que[que.size() - 1]->arrival_time;
         que[que.size() - 1]->waiting_time = que[que.size() - 1]->turn_around_time -que[que.size() - 1]->OG_burst_time;
         que.pop_back();
    }
}
    sortAP_P_NO();
    printerheader();
    for (int i = 0; i < allprocess.size(); i++){
        printer(allprocess[i]);
    }
return 0;
}

void printerheader(){
    cout << "\n\n\nPROCESS NO.\t" << "ARRIVAL TIME\t" << "BURST TIME\t" << "COMPLETION TIME\t   " << "EXIT TIME\t" << "TURN AROUND TIME     " << "WAITING TIME\n";
}

void printer (Process pro){
    cout << "P" << pro.p_no << "\t\t" << pro.arrival_time  << "\t\t" << pro.OG_burst_time  << "\t\t" << pro.completion_time  << "\t\t   " << pro.exit_time  << "\t\t" << pro.turn_around_time << "\t\t     " << pro.waiting_time << "\n";
}

void addavailabletoque(){
        for(int i = 0; i < allprocess.size(); i++){
            if ( allprocess[i].arrival_time <= timer && allprocess[i].add != 1 ){
                que.push_back(&allprocess[i]);
                allprocess[i].add = 1;
        }
    }
}

bool anyleft(){

        for (int i = 0; i < allprocess.size(); i++){
            if(allprocess[i].burst_time != 0)
                return 1;
        }
        return 0;
    }

void sortqueBT(){
        for (int i = 0; i < que.size(); i++){
            int g = i;
            for (int j = i + 1; j < que.size(); j++){
                if (que[j]->burst_time < que[i]->burst_time){
                    exchange(que[i],que[j]);
                    i = g;
            }
        }
    }
}

void exchange(Process * p1, Process * p2){
        Process temp;
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

void checkifque0(){
    if(que.size() != 0){
        return;
    }

    Process* best = &allprocess[0];

    for (int i = 0; i < allprocess.size(); i++){
            if ( allprocess[i].arrival_time < best->arrival_time && allprocess[i].add != 1 ){
                best = &allprocess[i];
            }
        }

    timer = best->arrival_time;
    que.push_back(best);
    best->add = 1;

    addavailabletoque();
    sortqueBT();
}

void shuffleque(){
    for (int i = 0; i < que.size() - 1; i++){
        if(i == 0)
            exchange(que[i],que[que.size() - 1]);
        if (i > 0)
            exchange(que[i],que[i-1]);
    }
}

void sortAP_P_NO(){
    for (int i = 0; i < allprocess.size(); i++){
        int g = i;
        for (int j = i+1; j < allprocess.size(); j++){
            if (allprocess[j].p_no < allprocess[i].p_no){
                exchange(&allprocess[i], &allprocess[j]);
                i = g;
            }
        }
    }
}
