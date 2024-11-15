#include <iostream>

struct Node {
    int giaTri;
    Node* keTiep;

    Node(int gt) : giaTri(gt), keTiep(nullptr) {}
};

class DanhSachLienKet {
private:
    Node* goc;

public:
    DanhSachLienKet() : goc(nullptr) {}

    void themPhanTu(int giaTri) {
        Node* moiNode = new Node(giaTri);
        moiNode->keTiep = goc;
        goc = moiNode;
    }

    void nhapDanhSach() {
        int soPhanTu;
        std::cout << "Nhap so phan tu cua danh sach: ";
        std::cin >> soPhanTu;

        for (int i = 0; i < soPhanTu; i++) {
            int giaTri;
            std::cout << "Nhap gia tri cua phan tu thu " << i + 1 << ": ";
            std::cin >> giaTri;
            themPhanTu(giaTri);
        }
    }

    void xoaPhanTuDau() {
        if (!goc) return;
        Node* tam = goc;
        goc = goc->keTiep;
        delete tam;
    }

    void xoaPhanTuCuoi() {
        if (!goc) return;
        if (!goc->keTiep) {
            delete goc;
            goc = nullptr;
            return;
        }
        Node* hienTai = goc;
        while (hienTai->keTiep->keTiep) {
            hienTai = hienTai->keTiep;
        }
        delete hienTai->keTiep;
        hienTai->keTiep = nullptr;
    }

    void xoaPhanTuSau(Node* truoc) {
        if (!truoc || !truoc->keTiep) return;
        Node* canXoa = truoc->keTiep;
        truoc->keTiep = canXoa->keTiep;
        delete canXoa;
    }

    void hienThiDanhSach() const {
        Node* hienTai = goc;
        while (hienTai) {
            std::cout << hienTai->giaTri << " ";
            hienTai = hienTai->keTiep;
        }
        std::cout << "\n";
    }

    Node* layNodeDau() {
        return goc;
    }

    ~DanhSachLienKet() {
        while (goc) {
            Node* tam = goc;
            goc = goc->keTiep;
            delete tam;
        }
    }
};

int main() {
    DanhSachLienKet danhSach;

    danhSach.nhapDanhSach();

    std::cout << "Danh sach da nhap: ";
    danhSach.hienThiDanhSach();

    danhSach.xoaPhanTuDau();
    std::cout << "Danh sach sau khi xoa phan tu dau: ";
    danhSach.hienThiDanhSach();

    danhSach.xoaPhanTuCuoi();
    std::cout << "Danh sach sau khi xoa phan tu cuoi: ";
    danhSach.hienThiDanhSach();

    Node* dau = danhSach.layNodeDau();
    if (dau) danhSach.xoaPhanTuSau(dau);
    std::cout << "Danh sach sau khi xoa phan tu sau node dau: ";
    danhSach.hienThiDanhSach();

    return 0;
}
