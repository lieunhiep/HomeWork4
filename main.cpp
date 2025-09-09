#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Appointments {
private:
    string date;
    string time;
    int IDDoctor;
    string namePatien;
    string reason;
    string status; //scheduled, completed, or canceled
public:
    Appointments(string d, string t, int ID, string n, string r, string s) {
        date = d;
        time = t;
        IDDoctor = ID;
        namePatien = n;
        reason = r;
        status = s;
    }
    void displayInfo() {
        cout<<"Bệnh nhân "<< namePatien << " có cuộc hẹn vào ngày: " << date <<", lúc: "<<time<<" với nguyên nhân: "<<reason<<'\n';
        cout<<"Status: "<<status<<'\n';
    }
    int getIDDoctor() {
        return IDDoctor;
    }
    void setStatus(string s) {
        status = s;
    }
};
//danh sách tổng
vector<Appointments> appointments;

class Patients {
protected:
    string name;
    int ID;
    int age;
    vector<string> medicalHistory;
public:
    //Hàm khởi tạo
    Patients(string n, int id, int a, vector<string> mh) {
        name = n;
        ID = id;
        age = a;
        medicalHistory = mh;
    }
    //hàm in thông tin
    void displayInfo() {
        cout<<"Tên: "<<name<<'\n';
        cout<<"ID: "<<ID<<'\n';
        cout<<"Tuổi: "<<age<<'\n';
    }
    
    //hàm cập nhật lịch sử bệnh nhân
    void updateMH(string newMedicalHistory) {
        medicalHistory.push_back(newMedicalHistory);
        cout<<"Đã cập nhật lịch sử bệnh của "<<name<<": "<<newMedicalHistory<<'\n';
    }
    //hàm lên lịch hẹn
    void scheduleAppointment(string date, string time, int IDDoctor, string reason, string status)
    {
        Appointments Apm(date, time, IDDoctor, name, reason, status);
        appointments.push_back(Apm);
        
        cout << "Đã lên lịch hẹn cho " << name <<" vào ngày: "<<date<<", lúc: "<<time<<'\n';
    }
    //Hàm in lịch sử bệnh nhân
    void showMH() {
        cout<<"Danh sách các bệnh tiền sử của "<<name<<": \n";
        for(int i=0;i<medicalHistory.size();i++) {
            cout<<medicalHistory[i]<<'\n';
        }
    }
};

class Doctor {
private:
    string name;
    int ID;
    string specialty;
    vector<Appointments> apm;
    void loadAppointment() {
        apm.clear();
        for(int i=0;i<appointments.size();i++) {
            if(appointments[i].getIDDoctor() == ID) {
                apm.push_back(appointments[i]);
            }
        }
    }
public:
    Doctor(string n, int id, string s)
    {
        name = n;
        ID = id;
        specialty = s;
        loadAppointment();
    }
    void showAppointments() {
        loadAppointment();
        cout << "Danh sách lịch hẹn của bác sĩ " << name << " (ID: " << ID << "):\n";
        for(int i=0;i<apm.size();i++)
        {
            cout<<i+1<<". ";
            apm[i].displayInfo();
        }
    }
    void updateStatus(string status) {
        int order;
        do {
            cout<<"Bạn muốn cập nhật trạng thái của cuộc hẹn thứ: ";
            cin>>order;
        }
        while(order< 1 && order>apm.size());
        
        apm[order-1].setStatus(status);
        
        for (int i = 0; i < appointments.size(); i++) {
            if (appointments[i].getIDDoctor() == ID) {
                order--;
                if (order == 0) {
                    appointments[i].setStatus(status);
                    break;
                }
            }
        }
        cout << "Đã cập nhật trạng thái cho lịch hẹn thứ: " << order - 1 <<'\n';
        showAppointments();
    }
    void displayInfo() {
        cout<<"Bác sĩ: "<<name<<'\n';
        cout<<"ID: "<<ID<<'\n';
        cout<<"CHuyên khoa: "<<specialty<<'\n';
    }
};
int main() {
    Doctor d1("Nhi", 3, "Ngoại khoa");
    d1.displayInfo();
    d1.showAppointments();
    Patients p1("Nhiep", 1, 18, {});
    p1.scheduleAppointment("10/02/2025", "9.am", 3, "Khám trĩ", "scheduled");
//    d1.updateStatus("Cancled");
    d1.showAppointments();
    
}
