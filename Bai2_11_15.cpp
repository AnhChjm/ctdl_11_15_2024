#include <iostream>
#include <string>

struct File {
    std::string ten;
    int kichThuoc;
    std::string ngay;
    File* tiep;

    File(std::string t, int k, std::string n) : ten(t), kichThuoc(k), ngay(n), tiep(nullptr) {}
};

class Folder {
private:
    File* dau;

public:
    Folder() : dau(nullptr) {}

    void themFile(const std::string& ten, int kichThuoc, const std::string& ngay) {
        File* fileMoi = new File(ten, kichThuoc, ngay);
        fileMoi->tiep = dau;
        dau = fileMoi;
    }

    void nhapThongTinFile() {
        int soFile;
        std::cout << "Nhap so luong file: ";
        std::cin >> soFile;
        for (int i = 0; i < soFile; ++i) {
            std::string ten;
            int kichThuoc;
            std::string ngay;
            std::cout << "Nhap ten file: ";
            std::cin >> ten;
            std::cout << "Nhap kich thuoc file (MB): ";
            std::cin >> kichThuoc;
            std::cout << "Nhap ngay tao file (YYYYMMDD): ";
            std::cin >> ngay;
            themFile(ten, kichThuoc, ngay);
        }
    }

    void sapXepTangDanKichThuoc() {
        if (dau == nullptr || dau->tiep == nullptr) return;
        for (File* i = dau; i != nullptr; i = i->tiep) {
            for (File* j = i->tiep; j != nullptr; j = j->tiep) {
                if (i->kichThuoc > j->kichThuoc || (i->kichThuoc == j->kichThuoc && i->ngay > j->ngay)) {
                    std::swap(i->ten, j->ten);
                    std::swap(i->kichThuoc, j->kichThuoc);
                    std::swap(i->ngay, j->ngay);
                }
            }
        }
    }

    void xoaFileBeNhatVaLauNhat() {
        while (dau && (dau->tiep || (dau->kichThuoc == dau->tiep->kichThuoc && dau->ngay > dau->tiep->ngay))) {
            File* fileNhoNhat = dau;
            File* truocFileNhoNhat = nullptr;
            File* hienTai = dau;
            File* truoc = nullptr;

            while (hienTai) {
                if (hienTai->kichThuoc < fileNhoNhat->kichThuoc ||
                    (hienTai->kichThuoc == fileNhoNhat->kichThuoc && hienTai->ngay > fileNhoNhat->ngay)) {
                    fileNhoNhat = hienTai;
                    truocFileNhoNhat = truoc;
                }
                truoc = hienTai;
                hienTai = hienTai->tiep;
            }

            if (truocFileNhoNhat) truocFileNhoNhat->tiep = fileNhoNhat->tiep;
            else dau = dau->tiep;

            delete fileNhoNhat;
        }
    }

    void inDanhSachFile() const {
        File* hienTai = dau;
        while (hienTai) {
            std::cout << "File: " << hienTai->ten 
                      << ", Kich thuoc: " << hienTai->kichThuoc 
                      << "MB, Ngay: " << hienTai->ngay << '\n';
            hienTai = hienTai->tiep;
        }
    }

    ~Folder() {
        while (dau != nullptr) {
            File* temp = dau;
            dau = dau->tiep;
            delete temp;
        }
    }
};

int main() {
    Folder thuMuc;

    thuMuc.nhapThongTinFile();

    std::cout << "Danh sach file ban dau:\n";
    thuMuc.inDanhSachFile();

    thuMuc.sapXepTangDanKichThuoc();
    std::cout << "\nDanh sach file sau khi sap xep theo dung luong tang dan:\n";
    thuMuc.inDanhSachFile();

    thuMuc.xoaFileBeNhatVaLauNhat();
    std::cout << "\nDanh sach file sau khi xoa cac file nho nhat va thoi gian luu lau nhat:\n";
    thuMuc.inDanhSachFile();

    return 0;
}
