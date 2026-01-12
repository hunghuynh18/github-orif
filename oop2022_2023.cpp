#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// ================= GIAO DICH =================
class GiaoDich {
protected:
    string maGD, ngayGD;
    double soTien;

public:
    virtual void Nhap() {
        cin.ignore();
        cout << "Ma giao dich: ";
        getline(cin, maGD);
        cout << "Ngay giao dich: ";
        getline(cin, ngayGD);
        cout << "So tien: ";
        cin >> soTien;
    }

    virtual void Xuat() {
        cout << left << setw(12) << maGD
             << setw(15) << ngayGD
             << setw(15) << soTien;
    }

    virtual double thanhTien() = 0;

    double getSoTien() {
        return soTien;
    }

    virtual ~GiaoDich() {}
};

// ================= NGOAI TE =================
class NgoaiTe : public GiaoDich {
private:
    string loaiTien;
    double soLuong, tyGia;

public:
    void Nhap() override {
        GiaoDich::Nhap();
        cout << "Loai tien (USD/EURO/YEN): ";
        cin >> loaiTien;
        cout << "So luong: ";
        cin >> soLuong;
        cout << "Ty gia: ";
        cin >> tyGia;
    }

    double thanhTien() override {
        return soLuong * tyGia;
    }

    bool operator==(const NgoaiTe& other) {
        return loaiTien == other.loaiTien;
    }

    string getLoaiTien() {
        return loaiTien;
    }

    void Xuat() override {
        GiaoDich::Xuat();
        cout << setw(10) << loaiTien
             << setw(12) << soLuong
             << setw(12) << tyGia
             << setw(15) << thanhTien() << endl;
    }
};

// ================= MAIN =================
int main() {
    vector<NgoaiTe*> ds;
    int n;

    cout << "Nhap so giao dich ngoai te: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nNhap giao dich thu " << i + 1 << endl;
        NgoaiTe* gd = new NgoaiTe();
        gd->Nhap();
        ds.push_back(gd);
    }

    // T?ng ti?n theo t?ng lo?i ti?n
    cout << "\n===== TONG TIEN THEO LOAI TIEN =====\n";
    for (int i = 0; i < ds.size(); i++) {
        double tong = 0;
        for (int j = 0; j < ds.size(); j++)
            if (ds[i]->getLoaiTien() == ds[j]->getLoaiTien())
                tong += ds[j]->thanhTien();

        cout << ds[i]->getLoaiTien() << " : " << tong << endl;
    }

    // Giao d?ch >= 1 t?
    cout << "\n===== GIAO DICH >= 1 TY =====\n";
    for (auto x : ds)
        if (x->thanhTien() >= 1000000000)
            x->Xuat();

    // S?p x?p gi?m d?n theo s? ti?n
    sort(ds.begin(), ds.end(), [](NgoaiTe* a, NgoaiTe* b) {
        return a->thanhTien() > b->thanhTien();
    });

    cout << "\n===== DANH SACH SAU SAP XEP =====\n";
    for (auto x : ds)
        x->Xuat();

    for (auto x : ds)
        delete x;

    return 0;
}
