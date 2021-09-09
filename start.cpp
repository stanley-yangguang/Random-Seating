#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<chrono>
#include<random>
using namespace std;
#define MAXN 100
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
bool mp[MAXN][MAXN];
int opt,len,dep,len2,dep2,num,stunum,numCancel,numStudent,numNotTgt,filled,randm;
string newname;
vector<string> names;
vector<string> namesNotTgt;
vector<string> seats;
map<string,int> book;
void OptErr() {
    cout<<"Error! Wrong option!\n";
}
int main() {
    cout<<"Hi user, welcome to the Random Seating Program\n    designed by Stanley\n";
    cout<<"Options: \n1: Init\n2: Start Assigning Seat\n3: Clear all settings\n";
    cin>>opt;
    if(opt==1) {
        ofstream outputStream;
        outputStream.open("LenDepConfigure.txt");
        cout<<"Input length: ";
        cin>>len;
        cout<<"Input depth: ";
        cin>>dep;
        outputStream<<len<<endl<<dep<<endl;
        for(int i=1;i<=len;i++)
            for(int j=1;j<=dep;j++) 
                mp[i][j]=1;
        cout<<"How many blocks to cancel: ";
        cin>>num;
        outputStream<<num<<endl;
        for(int i=1;i<=num;i++) {
            cout<<"For the "<<i<<"th block, input length and depth: ";
            cin>>len2>>dep2;
            outputStream<<len2<<" "<<dep2<<endl;
            mp[len2][dep2]=0;
        }
        cout<<"Display current map: \n";
        for(int i=1;i<=len;i++) {
            for(int j=1;j<=dep;j++) {
                cout<<mp[i][j]<<" ";
            }
            cout<<endl;
        }
        outputStream.close();
        cout<<"Map updated successfully.\n";
        cout<<"Next: input students' names. You can either input names manually or provide an external file containing all students' names.\n";
        cout<<"1. Input students' names\n2. Import students' names\n";
        cin>>opt;
        outputStream.open("StudentNameList.txt");
        if(opt==1) {
            stunum=len*dep-num;
            cout<<"Total: "<<stunum<<" students\n";
            outputStream<<stunum<<endl;
            for(int i=1;i<=stunum;i++) {
                cout<<i<<": ";
                cin>>newname;
                names.push_back(newname);
                outputStream<<newname<<endl;
            }
            outputStream.close();
            cout<<"End. The list of students is in \"StudentNameList.txt\".\n";
        }
        else if(opt==2) {
            cout<<"Please make sure that a file named \"StudentNameList.txt\" is in the correct path.\nInput format: a number \"num\" in the first line representing the number of students, followed by num lines, each line is the name of that student. Any order of names is ok.\n";
            ifstream inputStream;
            inputStream.open("StudentNameList.txt");
            inputStream>>stunum;
            if(stunum!=len*dep-num) {
                cout<<"Error found in the number of students in \"StudentNameList.txt\"\n";
                return 1;
            }
            outputStream<<stunum<<endl;
            for(int i=1;i<=stunum;i++) {
                inputStream>>newname;
                names.push_back(newname);
                outputStream<<newname<<endl;
            }
            outputStream.close();
            cout<<"End. The list of students is in \"StudentNameList.txt\".\n";
        }
        else OptErr();
        cout<<"Next: input those students that should not sit together: \n";
        outputStream.open("StudentNotTogetherList.txt");
        cout<<"Number of students that should not sit together: ";
        cin>>num;
        outputStream<<num<<endl;
        for(int i=1;i<=num;i++) {
            cout<<i<<": ";
            cin>>newname;
            namesNotTgt.push_back(newname);
            outputStream<<newname<<endl;
        }
        outputStream.close();
        cout<<"End. The list of students is in \"StudentNotTogetherList.txt\".\n";
    }
    else if(opt==2) {
        ifstream inConfigure("LenDepConfigure.txt");
        ifstream inStuName("StudentNameList.txt");
        ifstream inNotTgt("StudentNotTogetherList.txt");
        inConfigure>>len>>dep>>numCancel;
        for(int i=1;i<=len;i++)
            for(int j=1;j<=dep;j++) 
                mp[i][j]=1;
        for(int i=1;i<=numCancel;i++) {
            inConfigure>>len2>>dep2;
            mp[len2][dep2]=0;
        }
        cout<<"Display current map: \n";
        for(int i=1;i<=len;i++) {
            for(int j=1;j<=dep;j++) {
                cout<<mp[i][j]<<" ";
            }
            cout<<endl;
        }
        inConfigure.close();
        inStuName>>numStudent;
        for(int i=1;i<=numStudent;i++) {
            inStuName>>newname;
            names.push_back(newname);
        }
        inStuName.close();
        inNotTgt>>numNotTgt;
        for(int i=1;i<=numStudent;i++) {
            inNotTgt>>newname;
            namesNotTgt.push_back(newname);
        }
        inNotTgt.close();

        cout<<endl;
        while(filled<numStudent) {
            randm=rng()%numStudent;
            if(!book[names[randm]]) {
                book[names[randm]]=1;
                seats.push_back(names[randm]);
                filled++;
            }
        }
        ofstream outSeating("seating.csv", ios::out | ios::trunc);
        int tempnum=0;
        for(int i=1;i<=len;i++) {
            for(int j=1;j<=dep;j++) {
                if(mp[i][j]) {
                    outSeating<<seats[tempnum]<<",";
                    printf("%10s",seats[tempnum].c_str());
                    tempnum++;
                }
                else {
                    outSeating<<",";
                    printf("%8s","");
                }
            }
            outSeating<<endl;
            printf("\n");
        }
        outSeating.close();


    }
    else if(opt==3) {
        cout<<"Are you sure to clear all the settings? This process is irrecoverable. Press 1 to confirm and 2 to cancel.\n";
        cin>>opt;
        if(opt==1) {
            remove("StudentNameList.txt");
            remove("LenDepConfigure.txt");
            cout<<"Settings cleared.\n";
        }
        else if(opt==2) {
            cout<<"Cancelled.\n";
        }
        else OptErr();
    }
    else OptErr();

    cout<<"This is the end of the program. If you want to use other functions, please restart the program. Thank you for using.\n";
    return 0;
}