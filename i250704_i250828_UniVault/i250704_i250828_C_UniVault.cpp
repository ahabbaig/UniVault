//Hassan Abbas 25i-0828 Section C
//Ahab Baig    25i-0704 Section C

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;

//M1
int*** campusgrid(int d,int f,int r){
    if (d <= 0 || f <= 0 || r <= 0) return nullptr;
    int*** grid = new int**[d];
    for(int i=0;i<d;i++){
        *(grid + i) = new int*[f];
        for(int j=0;j<f;j++){
            *(*(grid + i)+ j) = new int[r];
            for(int k=0;k<r;k++){
                *(*(*(grid + i)+j)+k) = 0;
            }
        }
    }
    return grid;
}

//M2hassan
void enrolledstudent(char*** names,int** ids,float** gpas,int** statuses,int** depts,int** floors,int** rooms,int currentsize){
    int nsize = currentsize + 1;
    char** newname = new char*[nsize];
    int* newid = new int[nsize];
    float* newgpa = new float[nsize];
    int* newstatuses = new int[nsize];
    int* newdepts = new int[nsize];
    int* newfloors = new int[nsize];
    int* newrooms = new int[nsize];
    for(int i=0;i<currentsize;i++){
        *(newname + i) = *(*names + i);
        *(newid + i) = *(*ids + i);
        *(newgpa + i) = *(*gpas + i);
        *(newstatuses + i) = *(*statuses + i);
        *(newdepts + i) = *(*depts + i);
        *(newfloors + i) = *(*floors + i);
        *(newrooms + i) = *(*rooms + i);
    }
    if(currentsize>0){
        delete [] *names;
        delete [] *ids;
        delete [] *gpas;
        delete [] *statuses;
        delete [] *depts;
        delete [] *floors;
        delete [] *rooms;
    }
    *names = newname;
    *ids = newid;
    *gpas = newgpa;
    *statuses = newstatuses;
    *depts = newdepts;
    *floors = newfloors;
    *rooms = newrooms;
}

//m2ahab
bool enrollStudent(int*** grid, char** names, int* ids, float* gpas, int* statuses, int* depts, int* floors, int* rooms, int currentSize, int d, int f, int r, int nextid) {
    char tempBuffer[100];
    float inputGPA;
    int inputID = nextid;
    cout << "--- Student Enrollment ---" << endl;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(tempBuffer, 100);
    cout << "Enter GPA: ";
    cin >> inputGPA;
    int nameLen = 0;
    while (*(tempBuffer + nameLen) != '\0') {
        nameLen++;
    }
    nameLen++;
    *(names + currentSize) = new char[nameLen];
    for (int i = 0; i < nameLen; i++) {
        *(*(names + currentSize) + i) = *(tempBuffer + i);
    }
    *(ids + currentSize) = inputID;
    *(gpas + currentSize) = inputGPA;
    *(statuses + currentSize) = 0;
    int dept = rand()%d;
    int fl = rand()%f;
    int room = rand()%r;
    if(*(*(*(grid+dept)+fl)+room) != 0){
        bool found = false;
        int skipped = 0;
        for(int di=0; di<d && !found; di++){
            for(int fi=0; fi<f && !found; fi++){
                for(int ri=0; ri<r&&!found; ri++){
                    if(*(*(*(grid+di)+fi)+ri)==0){
                        dept=di; fl=fi; 
                        room=ri;
                        found=true;
                    } else {
                        skipped++;
                    }
                }
            }
        }
        if(!found){
            cout<<"Campus is full! Cannot enroll student."<<endl;
            delete[] *(names+currentSize);
            return false;
        }
        cout<<"Skipped "<<skipped<<" occupied slots."<<endl;
    }
    *(*(*(grid+dept)+fl)+room) = inputID;
    *(depts  + currentSize) = dept;
    *(floors + currentSize) = fl;
    *(rooms  + currentSize) = room;
    cout << "Student successfully placed in memory at [" << dept << "][" << fl << "][" << room << "]" << endl;
    return true;
}

//m3hassan
int updategpa(int* ids,float* gpas,int currentsize, int targetid,float ngpa){
    int resultposition = -1;
    for(int i=0;i<currentsize;i++){
        if(*(ids + i) == targetid){
            resultposition = i;
            break;
        }
    }
    if(resultposition != -1){
        *(gpas + resultposition) = ngpa;
        cout<<"Student found at ID "<<targetid<<". GPA is updated to "<<ngpa<<endl;
    }
    else{
        cout<<targetid<<" not found in registry"<<endl;
    }
    return resultposition;
}

// AHAB M3
void updateStatus(int* statuses, int index) {
    int sChoice;
    cout << "--- Bitwise Status Manager ---" << endl;
    cout << "1. Assign Scholarship (Set Bit 2)" << endl;
    cout << "2. Revoke Scholarship (Clear Bit 2)" << endl;
    cout << "3. Set Warning Flag (Set Bit 3)" << endl;
    cout << "Selection: ";
    cin >> sChoice;
    if (sChoice == 1) {
        *(statuses + index) = *(statuses + index) | (1 << 2);
        cout << "Bitwise Update: Scholarship Bit is now 1." << endl;
    }
    else if (sChoice == 2) {
        *(statuses + index) = *(statuses + index) & ~(1 << 2);
        cout << "Bitwise Update: Scholarship Bit is now 0." << endl;
    }
    else if (sChoice == 3) {
        *(statuses + index) = *(statuses + index) | (1 << 3);
        cout << "Bitwise Update: Warning Bit is now 1." << endl;
    }
}

//M3 hassan 
void runtimestep(int*** grid, char** &studentnames, int* &studentids, float* &studentgpas, int* &studentstatuses, int* &studentdepts, int* &studentfloors, int* &studentrooms, int &currentstudentcount, int d, int f, int r, int step){
    cout<<"\n--- Time Step "<<step<<" ---"<<endl;
    for(int i=0; i<currentstudentcount; ){
        unsigned char flags = 0;
        int event = rand()%10 + 1;
        if(event<=5){
            //academic progress
            flags = flags | (1<<0);
            *(studentgpas+i) += 0.1f;
            if(*(studentgpas+i) > 4.0f) *(studentgpas+i) = 4.0f;
            cout<<"ID "<<*(studentids+i)<<" progress. GPA="<<*(studentgpas+i)<<endl;
            i++;
        }
        else if(event <= 8){
            //steady
            cout<<"ID "<<*(studentids+i)<<" steady."<<endl;
            i++;
        }
        else if(event == 9){
            //warning
            flags = flags | (1<<1);
            *(studentstatuses+i) = 1;
            *(studentgpas+i) -= 0.2f;
            if(*(studentgpas+i) < 0.0f) *(studentgpas+i) = 0.0f;
            cout<<"ID "<<*(studentids+i)<<" WARNING. GPA="<<*(studentgpas+i)<<endl;
            i++;
        }
        else{
            //graduation
            flags = flags | (1<<2);
            cout<<"ID "<<*(studentids+i)<<" GRADUATED (graduated flag bit 2 set: "<<((flags>>2)&1)<<")"<<endl;
            *(*(*(grid+*(studentdepts+i))+*(studentfloors+i))+*(studentrooms+i)) = 0;
            delete[] *(studentnames+i);
            for(int j=i; j<currentstudentcount-1; j++){
                *(studentnames+j) = *(studentnames+j+1);
                *(studentids+j) = *(studentids+j+1);
                *(studentgpas+j) = *(studentgpas+j+1);
                *(studentstatuses+j)= *(studentstatuses+j+1);
                *(studentdepts+j) = *(studentdepts+j+1);
                *(studentfloors+j) = *(studentfloors+j+1);
                *(studentrooms+j) = *(studentrooms+j+1);
            }
            currentstudentcount--;
            if(currentstudentcount == 0) break;
            char** nn = new char*[currentstudentcount];
            int* ni = new int[currentstudentcount];
            float* ng = new float[currentstudentcount];
            int* ns = new int[currentstudentcount];
            int* nd = new int[currentstudentcount];
            int* nf = new int[currentstudentcount];
            int* nr = new int[currentstudentcount];
            for(int j=0;j<currentstudentcount;j++){
                *(nn+j) = *(studentnames+j);
                *(ni+j) = *(studentids+j);
                *(ng+j) = *(studentgpas+j);
                *(ns+j) = *(studentstatuses+j);
                *(nd+j) = *(studentdepts+j);
                *(nf+j) = *(studentfloors+j);
                *(nr+j) = *(studentrooms+j);  
            }
            delete[] studentnames;    
            delete[] studentids;
            delete[] studentgpas;     
            delete[] studentstatuses;
            delete[] studentdepts;    
            delete[] studentfloors;
            delete[] studentrooms;
            studentnames=nn; 
            studentids=ni; 
            studentgpas=ng;
            studentstatuses=ns; 
            studentdepts=nd; 
            studentfloors=nf; 
            studentrooms=nr;
        }
    }
}

//AHAB M4 
void printAhabStatus(int statusValue) {
    cout<<"Status Flags: ";
    bool anyStatus = false;
    if ((statusValue & (1 << 2)) != 0) {
        cout<<"[SCHOLARSHIP] ";
        anyStatus = true;
    }
    if ((statusValue & (1 << 3)) != 0) {
        cout << "[WARNING] ";
        anyStatus = true;
    }
    if (!anyStatus) {
        cout<<"Normal";
    }
    cout<<endl;
}

//M4 hassan
void displayDashboard(int*** grid, char** names, int* ids,float* gpas, int* statuses, int numStudents,int nd, int nf, int nr,int currentDept, int currentFloor, int step){

    cout<<"==========================================================================="<<endl;
    cout<<"                 UniVault LIVE RESOURCE DASHBOARD"<<endl;
    cout<<"==========================================================================="<<endl;
    cout<<right<<"[DEPT: "<<setfill('0')<<setw(2)<<currentDept<<setfill(' ')<<"] [FLOOR: "<<setfill('0')<<setw(2)<<currentFloor<<setfill(' ')<<"] [ROOMS: "<<nr<<"] [STEP: "<<setfill('0')<<setw(3)<<step<<setfill(' ')<<"]"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cout<<left<<setw(14)<<"ROOM ADDR"<<setw(8) <<"ID"<<setw(20)<<"NAME"<<setw(7) <<"GPA"<<"STATUS"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;

    for(int ri=0; ri<nr; ri++){
        int* cell = &(*(*(*(grid+currentDept)+currentFloor)+ri));
        int occupant = *cell;
        cout<<left<<setw(14)<<(void*)cell;
        if(occupant == 0){
            cout<<setw(8)<<"----"<<setw(20)<<"----------"<<setw(7) <<"0.00"<<"EMPTY"<<endl;
        } 
        else {
            int idx = -1;
            for(int k=0; k<numStudents; k++){
                if(*(ids+k)==occupant){ idx=k; break; }
            }
            if(idx == -1){ 
                cout<<endl; 
                continue; 
            }
            const char* statusStr = "STUDYING";
            if(*(statuses+idx)==1) statusStr = "WARNING";
            if(*(statuses+idx)==2) statusStr = "GRADUATING";
            cout<<setw(8) <<occupant<<setw(20)<<*(names+idx)<<setw(7) <<fixed<<setprecision(2)<<*(gpas+idx)<<statusStr<<endl;
        }
    }
    cout<<"---------------------------------------------------------------------------"<<endl;
    cout<<"COMMANDS: [1] Step | [2] Count | [3] Update | [4] Search | [5] Jump | [6] Filter | [S] Save | [X] Exit"<<endl;
    cout<<"==========================================================================="<<endl;
}

//m4hassan
void searchstudent(int*** grid, int* ids, char** names, float* gpas, int* statuses, int currentsize, int d, int f, int r) {
    int idat = *(*(*(grid + d)+f)+r);
    if(idat == 0){
        cout<<"This room is currently empty"<<endl;
        return;
    }
    int foundindex = -1;
    for(int i=0;i<currentsize;i++){
        if(*(ids + i)== idat){
            foundindex = i;
            break;
        }
    }
    if(foundindex !=-1){
        cout<<"========== STUDENT REPORT (M-4) =========="<<endl;
        cout<<"Location: Dept "<<d<<", Floor "<<f<<", Room "<<r<<endl;
        cout<<left<<setw(15)<<"Student Name:"<<*(names + foundindex)<<endl;
        cout<<"ID:   "<<idat<<endl;
        cout<<"GPA:  "<<*(gpas + foundindex)<<endl;
        cout<<"Memory Address of ID in Grid: "<<&(*(*(*(grid + d) + f) + r))<<endl;
        printAhabStatus(*(statuses + foundindex));
        cout<<"==========================================="<<endl;
    }
    else
        cout<<"Error: student not found in registry"<<endl;
}

//M5 Hassan 
void filesaving(char** names, int* ids, float* gpas, int* statuses,int* depts, int* floors, int* rooms,int currentsize, int*** grid, int d, int f, int r){
    ofstream outFile("database.txt");
    if(!outFile.is_open()){
        cout<<"Error opening database.txt!"<<endl;
        return;
    }
    outFile<<currentsize<<"\n";
    for(int i=0; i<currentsize; i++){
        char* nm = *(names+i);
        for(int c=0; *(nm+c)!='\0'; c++){
            outFile << (*(nm+c)==' ' ? '_' : *(nm+c));
        }
        outFile<<" "<<*(ids+i)<<" "<<*(gpas+i)<<" "<<*(statuses+i)<<" "<<*(depts+i)<<" "<<*(floors+i)<<" "<<*(rooms+i)<<"\n";
    }
    for(int di=0;di<d;di++){
        for(int fi=0;fi<f;fi++){
            for(int ri=0;ri<r;ri++){
                int occ = *(*(*(grid+di)+fi)+ri);
                if(occ != 0)
                    outFile<<di<<" "<<fi<<" "<<ri<<" "<<occ<<"\n";
            }
        }
    }
    outFile.close();
    cout<<"Registry saved to database.txt"<<endl;
}

//M6 hassan
void loaddatabase(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int* &depts, int* &floors, int* &rooms, int &numStudents){
    ifstream inFile("database.txt");
    if(!inFile.is_open()){
        cout<<"No database.txt found. Starting fresh."<<endl;
        return;
    }
    inFile>>numStudents;
    names = new char*[numStudents];
    ids = new int[numStudents];
    gpas = new float[numStudents];
    statuses = new int[numStudents];
    depts = new int[numStudents];
    floors = new int[numStudents];
    rooms = new int[numStudents];
    char nameBuf[100];
    for(int i=0; i<numStudents; i++){
        int id,st,dep,fl,rm; 
        float gpa;
        inFile>>nameBuf>>id>>gpa>>st>>dep>>fl>>rm;
        *(ids+i) = id;
        *(gpas+i) = gpa;
        *(statuses+i) = st;
        *(depts+i) = dep;
        *(floors+i) = fl;
        *(rooms+i) = rm;   
        for(int c=0; *(nameBuf+c)!='\0'; c++){
            if(*(nameBuf+c)=='_') *(nameBuf+c)=' ';
        }
        int len = 0;
        while(*(nameBuf+len)!='\0') len++;
        len++;
        *(names+i) = new char[len];
        for(int k=0;k<len;k++) {
            *(*(names+i)+k) = *(nameBuf+k);
        }
    }
    int di,fi,ri,occ;
    while(inFile>>di>>fi>>ri>>occ){
        *(*(*(grid+di)+fi)+ri) = occ;
    }
    inFile.close();
    cout<<"Loaded "<<numStudents<<" students from database.txt"<<endl;
}

//heapwork
void savingmemory(int*** grid,int d,int f,int r,char** names,int* ids,float* gpas,int* statuses,int* depts,int* floors,int* rooms,int currentsize){
    for (int i=0; i<d; i++) {
        for (int j=0; j<f; j++) {
            delete[] *(*(grid+i)+j);
        }
        delete[] *(grid+i);
    }
    delete[] grid;
    for (int i=0; i<currentsize; i++){
        delete[] *(names+i);
    }
    delete[] names;
    delete[] ids;
    delete[] gpas;
    delete[] statuses;
    delete[] depts;
    delete[] floors;
    delete[] rooms;
    cout<<"All dynamic memory cleared. System shutdown clean."<<endl;
}

//AHAB M5 
bool verifyingdata(int* ids, int currentsize) {
    if (currentsize==0) {
        return true;
    }
    for (int i=0; i<currentsize; i++) {
        if (*(ids + i) <= 0) {
            return false;
        }
    }
    return true;
}

//AHAB M5 
void sessionsummary(int currentsize, float* gpas) {
    if (currentsize==0) {
        cout<<"No data processed this session."<<endl;
        return;
    }
    float totalgpa = 0;
    for (int i=0; i<currentsize; i++) {
        totalgpa = totalgpa + *(gpas + i);
    }
    cout<<"SESSION SUMMARY"<<endl;
    cout<<"Total Students in Registry: "<<currentsize<<endl;
    cout<<"Average Campus GPA: "<<(totalgpa/currentsize)<<endl;
    cout<<"Integrity Status: VERIFIED"<<endl;
}

//M6 hassan 
float validation(){
    float gpa;
    while(true){
        cout<<"Enter gpa"<<endl;
        cin>>gpa;
        if(gpa>=0 && gpa<=4){
            return gpa;
        }
        else{
            cout<<"Invalid Input. Try again and enter the value again"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
        }
    }
}

void searching(int* ids,char** names,int* depts,int* floors,int* rooms,int currentsize,int targetid){
    bool found = false;
    for(int i=0;i<currentsize;i++){
        if(*(ids + i)==targetid){
            cout<<"Found in registry. Name: "<<*(names + i)<<"   index: "<<i<<endl;
            cout<<"Location: Dept "<<*(depts+i)<<", Floor "<<*(floors+i)<<", Room "<<*(rooms+i)<<endl;
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"ID "<<targetid<<" was not found in registry"<<endl;
    }
}

//AHAB M6
void filterbystatus(int* statuses, char** names, int* ids, int currentsize) {
    int fchoice;
    cout<<"1. List all Scholarship Students (Bit 2)"<<endl;
    cout<<"2. List all Warning Flag Students (Bit 3)"<<endl;
    cout<<"Selection: ";
    cin>>fchoice;
    int mask = 0;
    if (fchoice==1) {
        mask = (1<<2);
    }
    else if (fchoice == 2) {
        mask = (1<<3);
    }
    bool found = false;
    for (int i = 0; i < currentsize; i++) {
        if ((*(statuses + i) & mask) != 0) {
            cout<<"ID: "<<*(ids + i)<<" | Name: "<<*(names + i)<<endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with that status flag." << endl;
    }
}

int main(){
    srand(time(0));

    //M1
    int d,f,r;
    bool loadedFromFile = false;
    cout<<"--- UniVault Initialization ---"<<endl;
    ifstream inFile("config.txt");
    if (inFile.is_open()) {
        if (inFile>>d>>f>>r && d>0 && f>0 && r>0) {
            cout<<"Configuration loaded from config.txt: "<<d<<" Depts, "<<f<<" Floors, "<<r<<" Rooms."<<endl;
            loadedFromFile = true;
        } else {
            cout<<"config.txt contains invalid values. Re-entering manually."<<endl;
        }
        inFile.close();
    }
    if (!loadedFromFile) {
        cout<<"Configuration file not found. Please enter details manually."<<endl;
        cout<<"Enter the number of departments: ";
        cin>>d;
        cout<<"Enter number of floors: ";
        cin>>f;
        cout<<"Enter number of rooms: ";
        cin>>r;
        ofstream outFile("config.txt");
        if (outFile.is_open()) {
            outFile<<d<<" "<<f<<" "<<r;
            outFile.close();
            cout << "Values saved to config.txt for future use." << endl;
        }
    }

    int*** gridcampus = campusgrid(d,f,r);
    //M2hassan
    char** studentnames = nullptr;
    int* studentids = nullptr;
    float* studentgpas = nullptr;
    int* studentstatuses= nullptr;
    int* studentdepts = nullptr;
    int* studentfloors = nullptr;
    int* studentrooms = nullptr;
    int currentstudentcount = 0;
    int nextid = 1001;

    // M6 
    loaddatabase(gridcampus, studentnames, studentids, studentgpas, studentstatuses, studentdepts, studentfloors, studentrooms, currentstudentcount);
    for(int i=0;i<currentstudentcount;i++){
        if(*(studentids+i) >= nextid) {
            nextid = *(studentids+i)+1;
        }
    }
    int currentDept  = 0;
    int currentFloor = 0;
    int step = 0;
    displayDashboard(gridcampus, studentnames, studentids, studentgpas, studentstatuses, currentstudentcount, d, f, r, currentDept, currentFloor, step);
    int choice;
    do {
        cout<<endl;
        cout<<"========== UNIVAULT MENU =========="<<endl;
        cout<<"1. Run Time Step"<<endl;
        cout<<"2. Enroll New Student"<<endl;
        cout<<"3. Total Student Count"<<endl;
        cout<<"4. Update Student Record"<<endl;
        cout<<"5. Search Student"<<endl;
        cout<<"6. Jump to Dept/Floor"<<endl;
        cout<<"7. Filter by Status"<<endl;
        cout<<"8. Save & Exit"<<endl;
        cout<<"9. Exit Without Save"<<endl;
        cout<<"Selection: ";
        cin>>choice;
        if(choice == 1){
            step++;
            runtimestep(gridcampus, studentnames, studentids, studentgpas, studentstatuses, studentdepts, studentfloors, studentrooms, currentstudentcount, d, f, r, step);
            displayDashboard(gridcampus, studentnames, studentids, studentgpas, studentstatuses, currentstudentcount, d, f, r, currentDept, currentFloor, step);
        }
        else if (choice == 2) {
            enrolledstudent(&studentnames, &studentids, &studentgpas, &studentstatuses, &studentdepts, &studentfloors, &studentrooms, currentstudentcount);
            bool enrolled = enrollStudent(gridcampus, studentnames, studentids, studentgpas, studentstatuses, studentdepts, studentfloors, studentrooms, currentstudentcount, d, f, r, nextid);
            if(enrolled){
                nextid++;
                currentstudentcount++;
                cout<<"SUCCESS: Registry expanded and student stored."<<endl;
                displayDashboard(gridcampus, studentnames, studentids, studentgpas, studentstatuses,currentstudentcount, d, f, r, currentDept, currentFloor, step);
            }
        }
        else if (choice == 3) {
            cout<<"Current Registry Size: "<<currentstudentcount<<" students."<<endl;
        }
        //m3hassan main
        else if(choice == 4){
            int sid;
            float wantedgpa;
            cout<<"Enter the id of student you want to update"<<endl;
            cin>>sid;
            cout<<"Enter the gpa you want to give to that student"<<endl;
            cin>>wantedgpa;
            int positionfound = updategpa(studentids,studentgpas,currentstudentcount,sid,wantedgpa);
            if (positionfound != -1){
                updateStatus(studentstatuses, positionfound);
            }
        }
        else if(choice == 5){
            int subchoice;
            cout<<"1. Search by Room"<<endl;
            cout<<"2. Search by ID"<<endl;
            cin>>subchoice;
            if(subchoice == 1){
                int qd,qf,qr;
                cout<<"Enter Dept, Floor, and Room to query: ";
                cin>>qd>>qf>>qr;
                if (qd>= 0 && qd < d && qf >= 0 && qf < f && qr >= 0 && qr < r) {
                    searchstudent(gridcampus, studentids, studentnames, studentgpas, studentstatuses, currentstudentcount, qd, qf, qr);
                }
                else
                    cout<<"Error. Location is not inside the bounds"<<endl;
            }
            else if(subchoice==2){
                int target;
                cout<<"Enter the id of student you want to find"<<endl;
                cin>>target;
                searching(studentids,studentnames,studentdepts,studentfloors,studentrooms,currentstudentcount,target);
            }
        }
        // M5 jump
        else if(choice == 6){
            int jd,jf;
            cout<<"Enter Department index (0 to "<<d-1<<"): ";
            cin>>jd;
            cout<<"Enter Floor index (0 to "<<f-1<<"): ";
            cin>>jf;
            if(jd>=0 && jd<d && jf>=0 && jf<f){
                currentDept  = jd;
                currentFloor = jf;
                
                displayDashboard(gridcampus, studentnames, studentids, studentgpas, studentstatuses, currentstudentcount, d, f, r, currentDept, currentFloor, step);
            } 
            else {
                cout<<"Error: Invalid coordinates."<<endl;
            }
        }
        else if(choice == 7){
            filterbystatus(studentstatuses, studentnames, studentids, currentstudentcount);
        }
        else if(choice == 8){
            if (verifyingdata(studentids, currentstudentcount)) {
                sessionsummary(currentstudentcount, studentgpas);
                if (currentstudentcount > 0) {
                    filesaving(studentnames, studentids, studentgpas, studentstatuses, studentdepts, studentfloors, studentrooms, currentstudentcount, gridcampus, d, f, r);
                }
            } else {
                cout << "CRITICAL ERROR: Data corruption detected. Save aborted to protect files." << endl;
            }
            choice = 9; 
        }
    } while (choice != 9);
    savingmemory(gridcampus, d, f, r, studentnames, studentids, studentgpas, studentstatuses, studentdepts, studentfloors, studentrooms, currentstudentcount);
    cout << "Finalizing records and shutting down UniVault..." << endl;
    return 0;
}