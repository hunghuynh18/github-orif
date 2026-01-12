#include <bits/stdc++.h>
using namespace std;
// ================= L?P CO S? =================
class Employee {
protected:
    string maNV, hoTen;
    int ngay, thang, nam;
public:
    Employee() {}
    Employee(string ma, string ten, int d, int m, int y) {
        maNV = ma;
        hoTen = ten;
        ngay = d;
        thang = m;
        nam = y;
    }
    virtual double tinhLuong() = 0;
    int tinhTuoi() {
        return 2025 - nam;
    }
    string getTen() {
        int pos = hoTen.find_last_of(' ');
        return hoTen.substr(pos + 1);
    }
    string getHoDem() {
        int pos = hoTen.find_last_of(' ');
        return hoTen.substr(0, pos);
    }
    virtual void nhap() {
        cin.ignore();
        cout << "Ma NV: ";
        getline(cin, maNV);
        cout << "Ho ten: ";
        getline(cin, hoTen);
        cout << "Ngay sinh (dd mm yyyy): ";
        cin >> ngay >> thang >> nam;
    }
    virtual void xuat() {
        cout << left << setw(10) << maNV
             << setw(25) << hoTen
             << setw(12) << tinhLuong() << endl;
    }
    virtual ~Employee() {}
};

// ================= FULL TIME =================
class FullTimeEmployee : public Employee {
private:
    double heSoLuong, phuCap;

public:
    void nhap() override {
        Employee::nhap();
        cout << "He so luong: ";
        cin >> heSoLuong;
        cout << "Phu cap: ";
        cin >> phuCap;
    }

    double tinhLuong() override {
        return heSoLuong * 2340000 + phuCap;
    }
};

// ================= PART TIME =================
class PartTimeEmployee : public Employee {
private:
    int soGio;
    double luongGio;

public:
    void nhap() override {
        Employee::nhap();
        cout << "So gio lam viec: ";
        cin >> soGio;
        cout << "Luong theo gio: ";
        cin >> luongGio;
    }

    double tinhLuong() override {
        return soGio * luongGio;
    }
};

// ================= HÀM SO SÁNH =================
bool cmp(Employee* a, Employee* b) {
    if (a->getTen() != b->getTen())
        return a->getTen() < b->getTen();
    return a->getHoDem() < b->getHoDem();
}

// ================= MAIN =================
int main() {
    vector<Employee*> ds;
    int n;
    cout << "Nhap so nhan vien: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int loai;
        cout << "\n1. FullTime  2. PartTime\nChon loai: ";
        cin >> loai;

        Employee* nv;
        if (loai == 1)
            nv = new FullTimeEmployee();
        else
            nv = new PartTimeEmployee();

        nv->nhap();
        ds.push_back(nv);
    }

    cout << "\n===== DANH SACH NHAN VIEN =====\n";
    cout << left << setw(10) << "MaNV"
         << setw(25) << "Ho Ten"
         << setw(12) << "Luong\n";
    for (auto x : ds)
        x->xuat();

    sort(ds.begin(), ds.end(), cmp);

    cout << "\n===== SAU KHI SAP XEP =====\n";
    for (auto x : ds)
        x->xuat();

    cout << "\n===== NHAN VIEN TREN 65 TUOI =====\n";
    for (auto x : ds)
        if (x->tinhTuoi() > 65)
            x->xuat();

    for (auto x : ds)
        delete x;

    return 0;
}






























