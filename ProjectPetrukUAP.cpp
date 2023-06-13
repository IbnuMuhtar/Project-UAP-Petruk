#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

/*
Program Pengelola Data Mahasiswa
Nurwahid Muslim 2217051163
Ibnu Muhtar 2217051163
Muhamad Rofiq 2217051098
*/

class Mahasiswa {
private:
    string nama;
    string npm;
    double nilai;

public:
    Mahasiswa(const string& _nama, const string& _npm, double _nilai)
        : nama(_nama), npm(_npm), nilai(_nilai) {}

    string getNama() const {
        return nama;
    }

    string getNpm() const {
        return npm;
    }

    double getNilai() const {
        return nilai;
    }
};

void tambahMahasiswa(vector<Mahasiswa>& dataMahasiswa, stack<Mahasiswa>& stackMahasiswa) {
    string nama, npm;
    double nilai;
    cout << "Masukkan Nama Mahasiswa     : ";
    getline(cin >> ws, nama);
    cout << "Masukkan NPM                : ";
    cin >> npm;
    cout << "Masukkan Nilai Mahasiswa    : ";
    cin >> nilai;
    Mahasiswa mhs(nama, npm, nilai);
    dataMahasiswa.push_back(mhs);
    stackMahasiswa.push(mhs);
    cout << "Data mahasiswa berhasil ditambahkan\n";
}

void cariMahasiswa(const vector<Mahasiswa>& dataMahasiswa) {
    string keyword;
    cout << "Masukkan Nama atau NPM Mahasiswa : ";
    cin >> keyword;
    bool ditemukan = false;
    for (const Mahasiswa& mhs : dataMahasiswa) {
        if (mhs.getNama() == keyword || mhs.getNpm() == keyword) {
            cout << "Nama    : " << mhs.getNama() << endl;
            cout << "NPM     : " << mhs.getNpm() << endl;
            cout << "Nilai   : " << mhs.getNilai() << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Mahasiswa dengan nama atau npm tersebut tidak ditemukan\n";
    }
}

double hitungRataRata(const vector<Mahasiswa>& dataMahasiswa) {
    double totalNilai = 0.0;
    int jumlahMahasiswa = dataMahasiswa.size();
    for (const Mahasiswa& mhs : dataMahasiswa) {
        totalNilai += mhs.getNilai();
    }
    return totalNilai / jumlahMahasiswa;
}

void tampilkanDaftarMahasiswa(const vector<Mahasiswa>& dataMahasiswa) {
    if (dataMahasiswa.empty()) {
        cout << "Belum ada data mahasiswa yang ditambahkan\n";
    } else {
        cout << setw(5) << left << "No";
        cout << setw(20) << left << "Nama";
        cout << setw(20) << left << "NPM";
        cout << setw(10) << right << "Nilai" << endl;
        cout << setfill('-') << setw(57) << "-" << setfill(' ') << endl;
        
        int nomor = 1;
        for (const Mahasiswa& mhs : dataMahasiswa) {
            cout << setw(5) << left << nomor++;
            cout << setw(20) << left << mhs.getNama();
            cout << setw(20) << left << mhs.getNpm();
            cout << setw(10) << right << mhs.getNilai() << endl;
        }
    }
}

void simpanDataMahasiswa(const vector<Mahasiswa>& dataMahasiswa, const string& namaFile) {
    ofstream file(namaFile);
    if (file.is_open()) {
        for (const Mahasiswa& mhs : dataMahasiswa) {
            file << mhs.getNama() << "," << mhs.getNpm() << "," << mhs.getNilai() << endl;
        }
        file.close();
        cout << "Data mahasiswa berhasil disimpan ke dalam file.\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
}

void muatDataMahasiswa(vector<Mahasiswa>& dataMahasiswa, const string& namaFile, stack<Mahasiswa>& stackMahasiswa) {
    ifstream file(namaFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                string nama = line.substr(0, pos1);
                string npm = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string nilaiStr = line.substr(pos2 + 1);
                double nilai = stod(nilaiStr);
                Mahasiswa mhs(nama, npm, nilai);
                dataMahasiswa.push_back(mhs);
                stackMahasiswa.push(mhs);
            }
        }
        file.close();
        cout << "Data mahasiswa berhasil dimuat dari file.\n";
    } else {
        cout << "Gagal membuka file untuk memuat data.\n";
    }
}

void hapusMahasiswa(vector<Mahasiswa>& dataMahasiswa, stack<Mahasiswa>& stackMahasiswa) {
    string keyword;
    cout << "Masukkan Nama atau NPM yang akan dihapus : ";
    cin >> keyword;
    bool ditemukan = false;
    vector<Mahasiswa> DataMahasiswa;
    stack<Mahasiswa> StackMahasiswa;
    while (!stackMahasiswa.empty()) {
        Mahasiswa mhs = stackMahasiswa.top();
        stackMahasiswa.pop();
        if (mhs.getNama() == keyword || mhs.getNpm() == keyword) {
            ditemukan = true;
        } else {
            StackMahasiswa.push(mhs);
        }
    }
    while (!StackMahasiswa.empty()) {
        Mahasiswa mhs = StackMahasiswa.top();
        StackMahasiswa.pop();
        stackMahasiswa.push(mhs);
        DataMahasiswa.push_back(mhs);
    }
    if (ditemukan) {
        dataMahasiswa = DataMahasiswa;
        cout << "Data mahasiswa berhasil dihapus!\n";
    } else {
        cout << "Mahasiswa dengan nama atau nomor pokok tersebut tidak ditemukan.\n";
    }
}

int main() {
    vector<Mahasiswa> dataMahasiswa;
    stack<Mahasiswa> stackMahasiswa;
    string namaFile = "data_mahasiswa.txt";
    muatDataMahasiswa(dataMahasiswa, namaFile, stackMahasiswa);

    int pilihan;
    do {
        cout << "\nProgram Pengelola Data Mahasiswa" << endl;
        cout << "1. Tambah Data Mahasiswa" << endl;
        cout << "2. Cari Mahasiswa" << endl;
        cout << "3. Hitung Rata-rata Nilai Mahasiswa" << endl;
        cout << "4. Tampilkan Daftar Mahasiswa" << endl;
        cout << "5. Hapus Data Mahasiswa" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda : ";
        cin >> pilihan;
        cout<<endl;

        switch (pilihan) {
            case 1:
                tambahMahasiswa(dataMahasiswa, stackMahasiswa);
                break;
            case 2:
                cariMahasiswa(dataMahasiswa);
                break;
            case 3:
                if (!dataMahasiswa.empty()) {
                    double ratarata = hitungRataRata(dataMahasiswa);
                    cout << "Rata-rata nilai mahasiswa: " << ratarata << endl;
                } else {
                    cout << "Belum ada data mahasiswa yang ditambahkan\n";
                }
                break;
            case 4:
                tampilkanDaftarMahasiswa(dataMahasiswa);
                break;
            case 5:
                hapusMahasiswa(dataMahasiswa, stackMahasiswa);
                break;
            case 0:
                simpanDataMahasiswa(dataMahasiswa, namaFile);
                cout << "Terima kasih telah menggunakan program ini";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih opsi yang sesuai\n";
        }
    } while (pilihan != 0);

    return 0;
}


