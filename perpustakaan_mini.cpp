#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Buku {
    string id;    
    string judul;    
    string pengarang;
    string penerbit;
    int tahunTerbit;
    string genre;    
    int stok;
};

// Prototype Fungsi
void loadData(Buku buku[], int &jumlah);
void simpanDataOtomatis(Buku buku[], int jumlah);

void tampildata(Buku buku[], int jumlahdata);
void tambahbuku(Buku *buku, int &jumlahdata);
void cariNamaBuku(Buku buku[], int &jumlah);



int main() {

    Buku buku[100];
    int jumlahData = 0;

    loadData(buku, jumlahData);

    int pilihan = 0;
    
    cout << "Perpustakaan Mini" << endl;
    cout << "1. Pinjaman" << endl;
    cout << "2. Tambah buku" << endl;
    cout << "4. Test" << endl;
    
    do {
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            tampildata(buku, jumlahData);
            
        } else if(pilihan == 2) {
            tambahbuku(&buku[jumlahData], jumlahData);
            
        } else if(pilihan == 3) {
            cout << "Edit Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 4) {
            cout << "Hapus Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 5){
            cariNamaBuku(buku, jumlahData);
            
        } else if(pilihan == 6){
            cout << "Pinjam Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 7){
            cout << "Kembalikan Buku" << endl; // hapus ini jika kalian mengisi kondisi ini 

        } else if(pilihan == 8){
            cout << "Simpan Data" << endl; // hapus ini jika kalian mengisi kondisi ini
        
        } else if(pilihan == 9){
            cout << "Keluar" << endl; // hapus ini jika kalian mengisi kondisi ini

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 9);

    simpanDataOtomatis(buku, jumlahData);
    
    return 0;
}

// Inisialisasi Fungsi -------------------------

void loadData(Buku buku[], int &jumlah) {
    ifstream file("data_buku.txt");    

    if (!file.is_open()){
        cout << "File tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }
    while (!file.eof()) {        
        string tahunStr, stokStr;
        getline(file, buku[jumlah].id, '|');
        if (buku[jumlah].id == "") break;

        getline(file, buku[jumlah].judul, '|');
        getline(file, buku[jumlah].pengarang, '|');
        getline(file, buku[jumlah].penerbit, '|');
        getline(file, tahunStr, '|');        
        getline(file, buku[jumlah].genre, '|');
        getline(file, stokStr);                        

        buku[jumlah].tahunTerbit = stoi(tahunStr);
        buku[jumlah].stok = stoi(stokStr);

        jumlah++;
    }
    file.close();
}

// fungsi simpan otomatis
void simpanDataOtomatis(Buku buku[], int jumlah) {
    ofstream file("data_buku.txt");

    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data otomatis!" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        file << buku[i].id << "|"
             << buku[i].judul << "|"
             << buku[i].pengarang << "|"
             << buku[i].penerbit << "|"
             << buku[i].tahunTerbit << "|"
             << buku[i].genre << "|"
             << buku[i].stok << endl;
    }

    file.close();
    cout << "\n(✓) Data otomatis disimpan sebelum program keluar.\n";
}

void tampildata(Buku buku[], int jumlahdata) {
    if(jumlahdata == 0){
        cout << "tidak ada data buku!" << endl;
        return;

    }

    cout << "\nDaftar Buku:" << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "judul"
         << setw(20) << "pengarang"
         << setw(20) << "penerbit"
         << setw(10) << "tahun"
         << setw(15) << "genre"
         << setw(5) << "stok" << endl;

    for(int i=0; i<jumlahdata; i++){
        cout << setw(10) << buku[i].id
             << setw(20) << buku[i].judul
             << setw(20) << buku[i].pengarang
             << setw(20) << buku[i].penerbit
             << setw(10) << buku[i].tahunTerbit
             << setw(15) << buku[i].genre
             << setw(5) << buku[i].stok << endl;
    }
}

void tambahbuku(Buku *buku, int &jumlahdata) {
    cout << "\nMasukan ID Buku: ";
    getline(cin, buku[jumlahdata].id);

    cout << "Masukkan Judul Buku: ";
    getline(cin, buku[jumlahdata].judul);

    cout << "Masukkan Pengarang: ";
    getline(cin, buku[jumlahdata].pengarang);

    cout << "Masukkan Penerbit: ";
    getline(cin, buku[jumlahdata].penerbit);

    cout << "Masukkan Tahun Terbit: ";
    cin >> buku[jumlahdata].tahunTerbit;
    cin.ignore();

    cout << "Masukkan Genre: ";
    getline(cin, buku[jumlahdata].genre);

    cout << "Masukkan Stok Buku: ";
    cin >> buku[jumlahdata].stok;
    cin.ignore();

    jumlahdata++;
    cout << "Buku berhasil ditambahkan!" << endl;
}


void cariNamaBuku(Buku buku[], int &jumlah) {    
    string cariNama;
    cout << "Masukkan Nama Buku yang dicari: ";
    getline(cin, cariNama);

    bool ditemukan = false;

    cout << "Hasil Pencarian: " << endl;

    for (int i = 0; i < jumlah; i++) {
       
        if (buku[i].judul.find(cariNama) != string::npos) {
            cout << "ID                : " << buku[i].id << endl;
            cout << "Judul             : " << buku[i].judul << endl;
            cout << "Pengarang         : " << buku[i].pengarang << endl;
            cout << "Penerbit          : " << buku[i].penerbit << endl;
            cout << "Tahun Terbit      : " << buku[i].tahunTerbit << endl;
            cout << "Genre             : " << buku[i].genre << endl;
            cout << "Stok              : " << buku[i].stok << endl;
            
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada Buku yang mengandung nama '" << cariNama << endl;
    }
}

