#include <iostream>
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
// Contoh int namaFungsi(int x, string y);

// Masukkan kode nya dibawah ini



int main() {

    Buku buku[100];
    int jumlahData = 0;
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