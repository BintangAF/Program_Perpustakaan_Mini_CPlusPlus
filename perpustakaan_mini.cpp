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
void loadDataBuku(Buku buku[], int &jumlah);
void loadDataPinjaman(Pinjaman pinjaman[], int &jumlahPinjaman);
void simpanDataBuku(Buku buku[], int &jumlahBuku);
void simpanDataPinjaman(Pinjaman pinjaman[], int &jumlah);

void tampilkanDataPinjaman(Buku buku[], int &jumlahBuku, Pinjaman pinjaman[], int &jumlahPinjaman);
void tampildata(Buku buku[], int jumlahdata);
void tambahbuku(Buku *buku, int &jumlahdata);
void editBuku(Buku buku[], int &jumlahData);
void hapusBuku(Buku buku[], int &jumlahData);
void cariNamaBuku(Buku buku[], int &jumlah);

void pinjamBuku(Buku buku[], int &jumlahData, Pinjaman pinjaman[], int &jumlahPinjam);
void kembalikanBuku(Buku buku[], int &jumlahData, Pinjaman pinjaman[], int &jumlahPinjam);

string generateId(int &jumlahData);
string generateIdPinjaman(int &jumlahPinjaman);



int main() {

    Buku buku[100];
    Pinjaman pinjaman[100];
    int jumlahData = 0;
    int jumlahPinjaman = 0;

    loadDataBuku(buku, jumlahData);
    loadDataPinjaman(pinjaman, jumlahPinjaman);

    int pilihan = 0;
    
    cout << "------Perpustakaan Mini------" << endl;
    cout << "1. Tampilkan Buku" << endl;
    cout << "2. Tambahkan Buku" << endl;
    cout << "3. Edit Buku" << endl;
    cout << "4. Hapus Buku" << endl;
    cout << "5. Cari Nama Buku" << endl;
    cout << "6. Tampilkan Data Pinjaman" << endl;
    cout << "7. Pinjam Buku" << endl;
    cout << "8. Kembalikan Buku" << endl;
    cout << "9. Simpan Data Buku" << endl;
    cout << "10. Simpan Data Pinjaman" << endl;
    cout << "11. Keluar Program" << endl;
    
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
            tampilkanDataPinjaman(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 7){
            pinjamBuku(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 8){
            kembalikanBuku(buku, jumlahData, pinjaman, jumlahPinjaman);

        } else if(pilihan == 9){
            simpanDataBuku(buku, jumlahData);
            
        } else if(pilihan == 10){
            simpanDataPinjaman(pinjaman, jumlahPinjaman);            
            
        } else if(pilihan == 11){
            cout << "\nTerima kasih!" << endl;

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 11);    
    
    simpanDataBuku(buku, jumlahData);
    simpanDataPinjaman(pinjaman, jumlahPinjaman);                

    return 0;
}

// Inisialisasi Fungsi -------------------------

// Load Data Buku
void loadDataBuku(Buku buku[], int &jumlah) {
    ifstream file("data_buku.txt");        

    if (!file.is_open()){
        cout << "File data_buku.txt tidak ditemukan atau gagal dibuka!" << endl;
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

// Load Data Pinjaman
void loadDataPinjaman(Pinjaman pinjaman[], int &jumlahPinjaman) {
    ifstream file("data_pinjaman.txt");    

    if (!file.is_open()){
        cout << "File data_pinjaman.txt tidak ditemukan atau gagal dibuka!" << endl;
        return;
    }

    while (!file.eof()) {                
        getline(file, pinjaman[jumlahPinjaman].id, '|');
        if (pinjaman[jumlahPinjaman].id == "") break;

        getline(file, pinjaman[jumlahPinjaman].idBuku, '|');
        getline(file, pinjaman[jumlahPinjaman].namaPeminjam, '|');
        getline(file, pinjaman[jumlahPinjaman].tanggalPinjam, '|');
        getline(file, pinjaman[jumlahPinjaman].tanggalKembali);

        jumlahPinjaman++;
    }
    
    file.close();
}

// fungsi simpan data
void simpanDataBuku(Buku buku[], int &jumlahBuku) {
    ofstream file("data_buku.txt");

    if (!file) {
        cout << "Gagal membuka file data_buku.txt untuk menyimpan data buku!" << endl;
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
    cout << "Data buku telah tersimpan.\n";
}

void simpanDataPinjaman(Pinjaman pinjaman[], int &jumlah) {
     ofstream file("data_pinjaman.txt");

    if (!file) {
        cout << "Gagal membuka file data_pinjaman.txt untuk menyimpan data pinjaman!" << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        file << pinjaman[i].id << "|"
             << pinjaman[i].idBuku << "|"
             << pinjaman[i].namaPeminjam << "|"
             << pinjaman[i].tanggalPinjam << "|"
             << pinjaman[i].tanggalKembali << endl;
    }

    file.close();    
    cout << "Data pinjaman telah tersimpan.\n";
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

void tampilkanDataPinjaman(Buku buku[], int &jumlahBuku, Pinjaman pinjaman[], int &jumlahPinjaman) {
    if(jumlahPinjaman == 0){
        cout << "tidak ada data pinjaman!" << endl;
        return;
    }

    cout << "\nDaftar Pinjaman:" << endl;
    cout << left << setw(10) << "ID"
         << setw(10) << "ID Buku"
         << setw(20) << "Judul Buku"
         << setw(20) << "Nama Peminjam"
         << setw(20) << "Tanggal Pinjam"
         << setw(10) << "Tanggal Kembali" << endl;

    for(int i = 0; i < jumlahBuku; i++) {
        for(int j = 0; j < jumlahPinjaman; j++) {
            if(buku[i].id == pinjaman[j].idBuku) {
                cout << setw(10) << pinjaman[j].id
                << setw(10) << pinjaman[j].idBuku 
                << setw(20) << buku[i].judul 
                << setw(20) << pinjaman[j].namaPeminjam 
                << setw(20) << pinjaman[j].tanggalPinjam 
                << setw(10) << pinjaman[j].tanggalKembali << endl;
            }
        }
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
    
    cout << "Masukkan nama peminjam: ";
    getline(cin, pinjam[jumlahPinjam].namaPeminjam);
    
    cout << "Masukkan tanggal pinjam (DD/MM/YYYY): ";
    getline(cin, pinjam[jumlahPinjam].tanggalPinjam);
    
    cout << "Masukkan tanggal kembali (DD/MM/YYYY): ";
    getline(cin, pinjam[jumlahPinjam].tanggalKembali);
    
    jumlahPinjam++;
    cout << "Buku " << buku[index].judul << " berhasil dipinjam!" << endl;
}

void kembalikanBuku(Buku buku[], int &jumlahData, Pinjaman pinjam[], int &jumlahPinjam) {
    string idBuku, namaPengembali;
    cout << "Masukkan id buku yang ingin dikembalikan: ";
    getline(cin, idBuku);
    cout << "Masukkan nama peminjam: ";
    getline(cin, namaPengembali);

    int index = -1;
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].id == idBuku) {            
            index = i;                              
            break;
        }
    }    

    if(index == -1) {
        cout << "Buku dengan id " << idBuku << " tidak ditemukan!" << endl;
        return;
    }

    int indexPinjam = -1;
    
    for(int i = 0; i < jumlahPinjam; i++) {
        if(pinjam[i].idBuku == idBuku && pinjam[i].namaPeminjam == namaPengembali) {
            indexPinjam = i;
            break;
        }
    }

    if(indexPinjam == -1) {
        cout << "Pinjaman dengan id buku " << idBuku << " dan nama peminjam " << namaPengembali << " tidak ditemukan!" << endl;
        return;
    }
    
    for(int i = indexPinjam; i < jumlahPinjam - 1; i++) {
        pinjam[i] = pinjam[i + 1];
    }
    
    buku[index].stok++;
    jumlahPinjam--;
    cout << "Buku " << buku[index].judul << " berhasil dikembalikan!" << endl;
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
