#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Appointments {
private:
    string date;
    string time;
    string IDDoctor;
    string namePatien;
    string reason;
    string status; //scheduled, completed, or canceled
public:
    Appointments(string d, string t, string ID, string n, string r, string s) {
        date = d;
        time = t;
        IDDoctor = ID;
        namePatien = n;
        reason = r;
        status = s;
    }
    void displayInfo() {
        cout<<"Bệnh nhân "<< namePatien << " có cuộc hẹn vào ngày: " << date <<", lúc: "<<time<<" với nguyên nhân: "<<reason<<'\n';
        cout<<"Trạng thái: "<<status<<'\n';
    }
    string getIDDoctor() {
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
    string ID;
    int age;
    vector<string> medicalHistory;
public:
    //Hàm khởi tạo
    Patients(string n, string id, int a, vector<string> mh) {
        name = n;
        ID = id;
        age = a;
        medicalHistory = mh;
    }
    //hàm huỷ
    Patients() {
        name = "";
        ID = "";
        age = 0;
        medicalHistory = {};
    }
    //hàm in thông tin
    void displayInfo() {
        cout<<"Bệnh nhân: \n";
        cout<<"Tên: "<<name<<'\n';
        cout<<"ID: "<<ID<<'\n';
        cout<<"Tuổi: "<<age<<'\n';
    }
    //hàm lấy tên bệnh nhân
    string getname() {
        return name;
    }
    //hàm lấy tuổi của bệnh nhân
    int getAge() {
        return age;
    }
    //hàm lấy ID của bệnh nhân
    string getID() {
        return ID;
    }
    //hàm cập nhật lịch sử bệnh nhân
    void updateMH(string newHM) {
        medicalHistory.push_back(newHM);
        cout<<"Đã cập nhật lịch sử bệnh của "<<name<<": "<<newHM<<'\n';
    }
    //hàm lên lịch hẹn
    void scheduleAppointment(string date, string time, string IDDoctor, string reason, string status)
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
    string ID;
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
    Doctor(string n, string id, string s)
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
        while(order< 1 || order>apm.size());
        
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
        cout << "Đã cập nhật trạng thái cho lịch hẹn thứ: \n";
        showAppointments();
    }
    void displayInfo() {
        cout<<"Bác sĩ: "<<name<<'\n';
        cout<<"ID: "<<ID<<'\n';
        cout<<"CHuyên khoa: "<<specialty<<'\n';
    }
};
class ChronicPatient : public Patients {
private:
protected:
public:
    ChronicPatient(string n, string id, int a, vector<string> mh) :
    Patients(n, id, a, mh) {}
    
    ChronicPatient() :
    Patients("", "", 0, {}) {}
    
    void displayIF() {
        cout<<"Bệnh nhân mãng tính: \n";
        displayInfo();
    }
    
};

class AcutePatient : public Patients {
private:
    string symptom;
public:
    AcutePatient(string n, string id, int a, vector<string> mh, string s)
        : Patients(n, id, a, mh) {
        symptom = s;
    }
    
    AcutePatient() :
    Patients("", "", 0, {}), symptom("") {}
    
    void displayIF() {
        cout<<"Bệnh nhân cấp tính: \n";
        displayInfo();
        cout<<"Triệu chứng: "<<symptom<<'\n';
    }
   
    
};
int main() {
    // 1. Tạo bệnh nhân thường
    Patients p1("Nhiep", "BN001", 20, {"Sốt","Nôn"});
    p1.displayInfo();
    p1.updateMH("Đau đầu");
    p1.showMH();
    cout << "--------------------------\n";

    // 2. Tạo bệnh nhân mãn tính
    ChronicPatient c1("Phat", "BN002", 45, {"Tiểu đường"});
    c1.displayIF();
    c1.updateMH("Huyết áp cao");
    c1.showMH();
    cout << "--------------------------\n";

    // 3. Tạo bệnh nhân cấp tính
    AcutePatient a1("Trang", "BN003", 30, {}, "Sốt cao");
    a1.displayIF();
    a1.updateMH("Viêm họng");
    a1.showMH();
    cout << "--------------------------\n";

    // 4. Đặt lịch hẹn cho bệnh nhân
    p1.scheduleAppointment("12/09/2025", "09:00", "BS01", "Khám định kỳ", "đã lên lịch");
    c1.scheduleAppointment("13/09/2025", "10:00", "BS01", "Khám tiểu đường", "đã lên lịch");
    a1.scheduleAppointment("14/09/2025", "14:00", "BS02", "Khám sốt", "đã lên lịch");
    cout << "--------------------------\n";

    // 5. Tạo bác sĩ và xem lịch hẹn
    Doctor d1("Nguyen Van A", "BS01", "Nội khoa");
    d1.displayInfo();
    d1.showAppointments();
    cout << "--------------------------\n";

    Doctor d2("Le Thi B", "BS02", "Nhi khoa");
    d2.displayInfo();
    d2.showAppointments();
    cout << "--------------------------\n";

    // 6. Cập nhật trạng thái lịch hẹn của bác sĩ
    cout << ">>> Bác sĩ 1 cập nhật trạng thái hẹn:\n";
    d1.updateStatus("hoàn thành");  // nhập số thứ tự để chọn hẹn
    cout << "--------------------------\n";

    cout << ">>> Bác sĩ 2 cập nhật trạng thái hẹn:\n";
    d2.updateStatus("đã huỷ");   // nhập số thứ tự để chọn hẹn
    cout << "--------------------------\n";

    return 0;
}
