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

// Prototipe Fungsi ---------------------------------
void simpanDataOtomatis(Buku buku[], int jumlah);
// Contoh int namaFungsi(int x, string y);

// Masukkan kode nya dibawah ini


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



// fungsi nyari buku



int main() {

    Buku buku[100];
    int jumlahData = 0;

    loaddata (buku, jumlahData);

    int pilihan = 0;
    
    cout << "Perpustakaan Mini" << endl;
    cout << "1. Pinjaman" << endl;
    cout << "2. Tambah buku" << endl;
    cout << "4. Test" << endl;
    
    do
    {
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            cout << "Tampilkan Daftar Buku" << endl; // hapus ini jika kalian mengisi kondisi ini 
            
        } else if(pilihan == 2) {
            cout << "Tambah Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 3) {
            cout << "Edit Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 4) {
            cout << "Hapus Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
        } else if(pilihan == 5){
            cout << "Cari Buku" << endl; // hapus ini jika kalian mengisi kondisi ini
            
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
// Contoh
// int total(int a, int b) {
//     return a + b;
// }
// void tambahBuku() {
//     cout << "Tambah Buku" << endl;
// }

// Masukkan kodenya dibawah ini

void loaddata(Buku buku[], int&jumlah) {
    ifstream file("data_buku.txt");
    jumlah = 0;

    if (!file.is_open()){
        return;
    }
    while (!file.eof()) {
        Buku b;
        getline(file, b.id);
        if (b.id == "") break;

        getline(file, b.judul);
        getline(file, b.pengarang);
        getline(file, b.penerbit);
        file>> b.tahunTerbit;
        getline(file, b.genre);
        file>> b.stok;
        file.ignore();

        buku[jumlah] = b;
        jumlah++;
    }

}
