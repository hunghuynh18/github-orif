#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
// ================= CAN BO =================
class CanBo {
protected:
    string maCB, hoTen, donVi;
    double heSoLuong;
public:
    virtual void Nhap() {
        cin.ignore();
        cout << "Ma CB: ";
        getline(cin, maCB);
        cout << "Ho ten: ";
        getline(cin, hoTen);
        cout << "Don vi: ";
        getline(cin, donVi);
        cout << "He so luong: ";
        cin >> heSoLuong;
    }
    virtual double tinhLuong() = 0;
    string getTen() {
        int pos = hoTen.find_last_of(' ');
        return hoTen.substr(pos + 1);
    }
    string getDonVi() {
        return donVi;
    }
    virtual void Xuat() {
        cout << left << setw(10) << maCB
             << setw(25) << hoTen
             << setw(15) << donVi
             << setw(10) << tinhLuong() << endl;
    }
    virtual ~CanBo() {}
};
// ============== CAN BO GIANG DAY =============
class CanBoGiangDay : public CanBo {
private:
    int soNamCongTac;
public:
    void Nhap() override {
        CanBo::Nhap();
        cout << "So nam cong tac: ";
        cin >> soNamCongTac;
    }
    double tinhLuong() override {
        double phuCap = 0;
        if (soNamCongTac >= 25) phuCap = 0.3;
        else if (soNamCongTac >= 15) phuCap = 0.2;
        else if (soNamCongTac >= 5)  phuCap = 0.1;

        return 1800000 * heSoLuong * (1 + phuCap);
    }
    int getSoNamCongTac() {
        return soNamCongTac;
    }
};
// ================== MAIN ==================
int main() {
    vector<CanBoGiangDay*> ds;
    int n;
    cout << "Nhap so can bo: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nNhap can bo thu " << i + 1 << endl;
        CanBoGiangDay* cb = new CanBoGiangDay();
        cb->Nhap();
        ds.push_back(cb);
    }

    // S?p x?p theo tên
    sort(ds.begin(), ds.end(), [](CanBoGiangDay* a, CanBoGiangDay* b) {
        return a->getTen() < b->getTen();
    });

    cout << "\n===== DANH SACH SAU SAP XEP =====\n";
    for (auto x : ds)
        x->Xuat();

    // S? nam công tác ít nh?t
    int minNam = ds[0]->getSoNamCongTac();
    for (auto x : ds)
        minNam = min(minNam, x->getSoNamCongTac());

    cout << "\n===== CAN BO CO SO NAM CONG TAC IT NHAT =====\n";
    for (auto x : ds)
        if (x->getSoNamCongTac() == minNam)
            x->Xuat();

    // Luong cao nh?t theo t?ng don v?
    cout << "\n===== CAN BO CO LUONG CAO NHAT THEO DON VI =====\n";
    for (int i = 0; i < ds.size(); i++) {
        bool printed = false;
        double maxLuong = 0;

        for (auto x : ds)
            if (x->getDonVi() == ds[i]->getDonVi())
                maxLuong = max(maxLuong, x->tinhLuong());

        for (auto x : ds)
            if (!printed && x->getDonVi() == ds[i]->getDonVi() &&
                x->tinhLuong() == maxLuong) {
                x->Xuat();
                printed = true;
            }
    }

    for (auto x : ds)
        delete x;

    return 0;
}

