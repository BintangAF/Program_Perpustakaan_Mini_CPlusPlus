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

struct Pinjaman {
    string id;
    string idBuku;    
    string namaPeminjam;    
    string tanggalPinjam;
    string tanggalKembali;
};

// Prototype Fungsi
void loadData(Buku buku[], int &jumlah, Pinjaman pinjaman[], int &jumlahPinjaman);
void simpanDataBuku(Buku buku[], int &jumlahBuku);

void tampildata(Buku buku[], int jumlahdata);
void tambahbuku(Buku *buku, int &jumlahdata);
void editBuku(Buku buku[], int &jumlahData);
void hapusBuku(Buku buku[], int &jumlahData);
void cariNamaBuku(Buku buku[], int &jumlah);

void pinjamBuku(Buku buku[], int &jumlahData, Pinjaman pinjaman[], int &jumlahPinjam);

string generateId(int &jumlahData);
string generateIdPinjam(int &jumlahPinjaman);



int main() {

    Buku buku[100];
    Pinjaman pinjaman[100];
    int jumlahData = 0;
    int jumlahPinjaman = 0;

    loadData(buku, jumlahData, pinjaman, jumlahPinjaman);

    int pilihan = 0;
    
    cout << "Perpustakaan Mini" << endl;
    cout << "1. Tampilkan Buku" << endl;
    cout << "2. Tambahkan Buku" << endl;
    cout << "4. Edit Buku" << endl;
    cout << "5. Cari Nama Buku" << endl;
    cout << "6. Pinjam Buku" << endl;
    cout << "7. Kembalikan Buku" << endl;
    cout << "8. Simpan Data" << endl;
    cout << "9. Keluar Program" << endl;
    
    do {
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            tampildata(buku, jumlahData);
            
        } else if(pilihan == 2) {
            tambahbuku(&buku[jumlahData], jumlahData);
            
        } else if(pilihan == 3) {
            editBuku(buku, jumlahData);
            
        } else if(pilihan == 4) {
            hapusBuku(buku, jumlahData);
            
        } else if(pilihan == 5){
            cariNamaBuku(buku, jumlahData);
            
        } else if(pilihan == 6){
            pinjamBuku(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 7){
            cout << "Kembalikan Buku" << endl; // hapus ini jika kalian mengisi kondisi ini 

        } else if(pilihan == 8){
            // simpan data manual
            simpanDataBuku(buku, jumlahData);
        
        } else if(pilihan == 9){
            // Simpan data otomatis ketika program berakhir
            simpanDataBuku(buku, jumlahData);            
            cout << "Terima kasih!" << endl;

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 9);    
    
    return 0;
}

// Inisialisasi Fungsi -------------------------

void loadData(Buku buku[], int &jumlah, Pinjaman pinjaman[], int &jumlahPinjaman) {
    ifstream fileBuku("data_buku.txt");    
    ifstream filePinjaman("data_pinjaman.txt");    

    if (!fileBuku.is_open()){
        cout << "File data_buku.txt tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }

    if (!filePinjaman.is_open()){
        cout << "File data_pinjaman.txt tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }

    while (!fileBuku.eof()) {        
        string tahunStr, stokStr;
        getline(fileBuku, buku[jumlah].id, '|');
        if (buku[jumlah].id == "") break;

        getline(fileBuku, buku[jumlah].judul, '|');
        getline(fileBuku, buku[jumlah].pengarang, '|');
        getline(fileBuku, buku[jumlah].penerbit, '|');
        getline(fileBuku, tahunStr, '|');        
        getline(fileBuku, buku[jumlah].genre, '|');
        getline(fileBuku, stokStr);                        

        buku[jumlah].tahunTerbit = stoi(tahunStr);
        buku[jumlah].stok = stoi(stokStr);

        jumlah++;
    }

    fileBuku.close();

    while (!filePinjaman.eof()) {                
        getline(filePinjaman, pinjaman[jumlahPinjaman].id, '|');
        if (pinjaman[jumlahPinjaman].id == "") break;

        getline(filePinjaman, pinjaman[jumlahPinjaman].idBuku, '|');
        getline(filePinjaman, pinjaman[jumlahPinjaman].tanggalPinjam, '|');
        getline(filePinjaman, pinjaman[jumlahPinjaman].tanggalKembali, '|');

        jumlahPinjaman++;
    }
    
    filePinjaman.close();
}

// fungsi simpan data
void simpanDataBuku(Buku buku[], int &jumlahBuku) {
    ofstream file("data_buku.txt");

    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        file << buku[i].id << "|"
             << buku[i].judul << "|"
             << buku[i].pengarang << "|"
             << buku[i].penerbit << "|"
             << buku[i].tahunTerbit << "|"
             << buku[i].genre << "|"
             << buku[i].stok << endl;
    }

    file.close();    
    cout << "\nData telah tersimpan.\n";
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
    buku->id = generateId(jumlahdata);

    cout << "Masukkan Judul Buku: ";
    getline(cin, buku->judul);

    cout << "Masukkan Pengarang: ";
    getline(cin, buku->pengarang);

    cout << "Masukkan Penerbit: ";
    getline(cin, buku->penerbit);

    cout << "Masukkan Tahun Terbit: ";
    cin >> buku->tahunTerbit;
    cin.ignore();

    cout << "Masukkan Genre: ";
    getline(cin, buku->genre);

    cout << "Masukkan Stok Buku: ";
    cin >> buku->stok;
    cin.ignore();

    jumlahdata++;
    cout << "Buku berhasil ditambahkan!" << endl;
}

void editBuku(Buku buku[], int &jumlahData) {
    string cariNama;
    cout << "Masukkan Nama Buku yang dicari: ";
    getline(cin, cariNama);    
    
    int index = -1;
    
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].judul.find(cariNama) != string::npos) {
            index = i;
            break;
        }        
    }

    if(index == -1){
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }

    cout << "Buku ditemukan!" << endl;
    cout << "Data Buku saat ini" << endl;
    cout << "ID                : " << buku[index].id << endl;
    cout << "Judul             : " << buku[index].judul << endl;
    cout << "Pengarang         : " << buku[index].pengarang << endl;
    cout << "Penerbit          : " << buku[index].penerbit << endl;
    cout << "Tahun Terbit      : " << buku[index].tahunTerbit << endl;
    cout << "Genre             : " << buku[index].genre << endl;
    cout << "Stok              : " << buku[index].stok << endl;

    string inputBaru;

    cout << "Masukkan judul baru: ";
    getline(cin, inputBaru);
    buku[index].judul = (inputBaru.empty()) ? buku[index].judul : inputBaru;
    
    cout << "Masukkan pengarang baru: ";
    getline(cin, inputBaru);
    buku[index].pengarang = (inputBaru.empty()) ? buku[index].pengarang : inputBaru;
    
    cout << "Masukkan penerbit baru: ";
    getline(cin, inputBaru);
    buku[index].penerbit = (inputBaru.empty()) ? buku[index].penerbit : inputBaru;
    
    cout << "Masukkan tahun terbit baru: ";
    getline(cin, inputBaru);
    buku[index].tahunTerbit = (inputBaru.empty()) ? buku[index].tahunTerbit : stoi(inputBaru);
    
    cout << "Masukkan genre baru: ";
    getline(cin, inputBaru);
    buku[index].genre = (inputBaru.empty()) ? buku[index].genre : inputBaru;
    
    cout << "Masukkan stok baru: ";
    getline(cin, inputBaru);
    buku[index].stok = (inputBaru.empty()) ? buku[index].stok : stoi(inputBaru);

    cout << "Data Buku telah diperbarui!" << endl;
}

void hapusBuku(Buku buku[], int &jumlahData) {
    string judulBuku;
    cout << "Masukkan judul buku yang ingin dihapus: ";
    getline(cin, judulBuku);

    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].judul == judulBuku) {
            for(int j = i; j < jumlahData - 1; j++) {
                buku[j] = buku[j + 1];
            }
            jumlahData--;
            cout << "Buku " << judulBuku << " berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Buku " << judulBuku << " yang dicari tidak ditemukan!" << endl;
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

void pinjamBuku(Buku buku[], int &jumlahData, Pinjaman pinjam[], int &jumlahPinjam) {
    string idBuku;
    cout << "Masukkan id buku yang ingin dipinjam: ";
    getline(cin, idBuku);

    int index = -1;
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].id == idBuku) {            
            index = i;
            if(buku[i].stok < 1){
                cout << "Buku " << buku[i].judul << " tidak tersedia!" << endl;
                return;
            } else {
                buku[i].stok--;
            }
            break;
        }
    }    

    if(index == -1) {
        cout << "Buku dengan id " << idBuku << " tidak ditemukan!" << endl;
        return;
    }

    pinjam[jumlahPinjam].id = generateIdPinjaman(jumlahPinjam);
    pinjam[jumlahPinjam].idBuku = idBuku;
    getline(cin, pinjam[jumlahPinjam].tanggalPinjam);
    getline(cin, pinjam[jumlahPinjam].tanggalKembali);
    jumlahPinjam++;
    cout << "Buku " << buku[index].judul << " berhasil dipinjam!" << endl;
}

string generateId(int &jumlahData) {
    stringstream ss;
    ss << "B" << setw(3) << setfill('0') << jumlahData + 1;
    return ss.str();
}

string generateIdPinjaman(int &jumlahPinjaman) {
    stringstream ss;
    ss << "P" << setw(3) << setfill('0') << jumlahPinjaman + 1;
    return ss.str();
}
