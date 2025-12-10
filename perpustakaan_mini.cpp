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
    bool bolehDipinjam;
    bool dihapus;
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
void tampilDataBuku(Buku buku[], int jumlahdata);
void tampilDataBukuYangDihapus(Buku buku[], int jumlahBuku);
void tambahbuku(Buku *buku, int &jumlahdata);
void editBuku(Buku buku[], int &jumlahData);
void hapusBuku(Buku buku[], int &jumlahData, Pinjaman pinjaman[], int &jumlahPinjaman);
void setDilarangPinjam(Buku buku[], int &jumlahData);
void cariNamaBuku(Buku buku[], int &jumlah);
void pulihkanDataBuku(Buku buku[], int &jumlahBuku);

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
    cout << "5. Tampilkan Buku Yang Dihapus" << endl;
    cout << "6. Atur Buku Dilarang Pinjam" << endl;
    cout << "7. Pulihkan Data Buku" << endl;
    cout << "8. Cari Nama Buku" << endl;
    cout << "9. Tampilkan Data Pinjaman" << endl;
    cout << "10. Pinjam Buku" << endl;
    cout << "11. Kembalikan Buku" << endl;
    cout << "12. Simpan Data Buku" << endl;
    cout << "13. Simpan Data Pinjaman" << endl;
    cout << "14. Keluar Program" << endl;
    
    do {
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            tampilDataBuku(buku, jumlahData);
            
        } else if(pilihan == 2) {
            tambahbuku(&buku[jumlahData], jumlahData);
            
        } else if(pilihan == 3) {
            editBuku(buku, jumlahData);
            
        } else if(pilihan == 4) {
            hapusBuku(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 5){
            tampilDataBukuYangDihapus(buku, jumlahData);
            
        } else if(pilihan == 6){
            setDilarangPinjam(buku, jumlahData);
            
        } else if(pilihan == 7){
            pulihkanDataBuku(buku, jumlahData);
            
        } else if(pilihan == 8){
            cariNamaBuku(buku, jumlahData);
            
        } else if(pilihan == 9){
            tampilkanDataPinjaman(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 10){
            pinjamBuku(buku, jumlahData, pinjaman, jumlahPinjaman);
            
        } else if(pilihan == 11){
            kembalikanBuku(buku, jumlahData, pinjaman, jumlahPinjaman);

        } else if(pilihan == 12){
            simpanDataBuku(buku, jumlahData);
            
        } else if(pilihan == 13){
            simpanDataPinjaman(pinjaman, jumlahPinjaman);            
            
        } else if(pilihan == 14){
            cout << "\nTerima kasih!" << endl;

        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
        
    } while (pilihan != 14);    
    
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
        string tahunStr, stokStr, bolehDipinjamStr, diHapusStr;
        getline(file, buku[jumlah].id, '|');
        if (buku[jumlah].id == "") break;

        getline(file, buku[jumlah].judul, '|');
        getline(file, buku[jumlah].pengarang, '|');
        getline(file, buku[jumlah].penerbit, '|');
        getline(file, tahunStr, '|');        
        getline(file, buku[jumlah].genre, '|');
        getline(file, stokStr, '|');                        
        getline(file, bolehDipinjamStr, '|');        
        getline(file, diHapusStr);        

        buku[jumlah].tahunTerbit = stoi(tahunStr);
        buku[jumlah].stok = stoi(stokStr);
        buku[jumlah].bolehDipinjam = stoi(bolehDipinjamStr);
        buku[jumlah].dihapus = stoi(diHapusStr);                

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
             << buku[i].stok << "|"
             << buku[i].bolehDipinjam
             << buku[i].dihapus << endl;
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

void tampilDataBuku(Buku buku[], int jumlahdata) {
    if(jumlahdata == 0){
        cout << "tidak ada data buku!" << endl;
        return;

    }

    cout << "\nDaftar Buku:" << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "Judul"
         << setw(20) << "Pengarang"
         << setw(20) << "Penerbit"
         << setw(10) << "Tahun"
         << setw(15) << "Genre"
         << setw(10) << "Stok"
         << setw(15) << "Status" << endl;

    for(int i = 0; i < jumlahdata; i++){
        if(buku[i].dihapus == false) {
            cout << setw(10) << buku[i].id
                << setw(20) << buku[i].judul
                << setw(20) << buku[i].pengarang
                << setw(20) << buku[i].penerbit
                << setw(10) << buku[i].tahunTerbit
                << setw(15) << buku[i].genre
                << setw(10) << buku[i].stok;
                string status = (buku[i].bolehDipinjam == 1) ? "Boleh dipinjam" : "Tidak Boleh";
                cout << setw(15) << status << endl;
        }
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
    
    char status;
    cout << "Apakah buku ini boleh dipinjam (y/n): ";
    cin >> status;
    cin.ignore();

    if(status == 'y' || status == 'Y') {
        buku->bolehDipinjam = false;
    } else {
        buku->bolehDipinjam = true;
    }

    buku->dihapus = false;
    
    jumlahdata++;
    cout << "Buku berhasil ditambahkan!" << endl;
}

void editBuku(Buku buku[], int &jumlahData) {
    string idBuku;
    cout << "Masukkan ID Buku yang ingin diedit: ";
    getline(cin, idBuku);    
    
    int index = -1;
    
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].id == idBuku && buku[i].dihapus == false) {
            index = i;
            break;
        }        
    }

    if(index == -1){
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }

    cout << "Buku ditemukan!" << endl;
    cout << "Data Buku saat ini: " << endl;
    cout << left << setw(10) << "ID"
        << setw(20) << "Judul" 
        << setw(20) << "Pengarang"
        << setw(20) << "Penerbit"
        << setw(20) << "Tahun Terbit"
        << setw(20) << "Genre"
        << setw(5) << "Stok" << endl;
    
    cout << setw(10) << buku[index].id
        << setw(20) << buku[index].judul
        << setw(20) << buku[index].pengarang
        << setw(20) << buku[index].penerbit
        << setw(20) << buku[index].tahunTerbit
        << setw(20) << buku[index].genre
        << setw(5) << buku[index].stok << endl;

    string inputBaru;

    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan judul baru: ";
    getline(cin, inputBaru);
    buku[index].judul = (inputBaru.empty()) ? buku[index].judul : inputBaru;
    
    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan pengarang baru: ";
    getline(cin, inputBaru);
    buku[index].pengarang = (inputBaru.empty()) ? buku[index].pengarang : inputBaru;
    
    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan penerbit baru: ";
    getline(cin, inputBaru);
    buku[index].penerbit = (inputBaru.empty()) ? buku[index].penerbit : inputBaru;
    
    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan tahun terbit baru: ";
    getline(cin, inputBaru);
    buku[index].tahunTerbit = (inputBaru.empty()) ? buku[index].tahunTerbit : stoi(inputBaru);
    
    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan genre baru: ";
    getline(cin, inputBaru);
    buku[index].genre = (inputBaru.empty()) ? buku[index].genre : inputBaru;
    
    cout << "\nKosongkan jika tidak ingin dirubah" << endl;
    cout << "Masukkan stok baru: ";
    getline(cin, inputBaru);
    buku[index].stok = (inputBaru.empty()) ? buku[index].stok : stoi(inputBaru);

    cout << "Data Buku telah diperbarui!" << endl;
}

void hapusBuku(Buku buku[], int &jumlahData, Pinjaman pinjaman[], int &jumlahPinjaman) {
    string idBuku;
    cout << "Masukkan ID buku yang ingin dihapus: ";
    getline(cin, idBuku);

    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].id == idBuku) {
            
            for(int j = 0; j < jumlahPinjaman; j++) {
                if(pinjaman[j].idBuku == idBuku) {
                    cout << "Tidak bisa menghapus! Masih ada pinjaman aktif untuk buku ini." << endl;
                    cout << "Kembalikan semua pinjaman buku ini terlebih dahulu." << endl;
                    return;
                }
            }

            char konfirmasi;
            cout << "Anda yakin? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();

            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                buku[i].dihapus = true;                
                jumlahData--;
                cout << "Buku dengan ID " << idBuku << " berhasil dihapus!" << endl;
                return;
            } else {
                cout << "Operasi dibatalkan!" << endl;
                return;
            }
        }
    }
    cout << "Buku dengan ID " << idBuku << " yang dicari tidak ditemukan!" << endl;
}

void tampilDataBukuYangDihapus(Buku buku[], int jumlahBuku) {
    if(jumlahBuku == 0){
        cout << "tidak ada data buku!" << endl;
        return;

    }

    cout << "\nDaftar Buku:" << endl;
    cout << left << setw(10) << "ID"
         << setw(20) << "Judul"
         << setw(20) << "Pengarang"
         << setw(20) << "Penerbit"
         << setw(10) << "Tahun"
         << setw(15) << "Genre"
         << setw(10) << "Stok"
         << setw(10) << "Status" << endl;

    for(int i=0; i < jumlahBuku; i++){
        if(buku[i].dihapus == true){
            cout << setw(10) << buku[i].id
             << setw(20) << buku[i].judul
             << setw(20) << buku[i].pengarang
             << setw(20) << buku[i].penerbit
             << setw(10) << buku[i].tahunTerbit
             << setw(15) << buku[i].genre
             << setw(10) << buku[i].stok;
             string status = (buku[i].bolehDipinjam == 1) ? "Boleh" : "Tidak Boleh";
             cout << setw(10) << status << endl;
        }
    }
}

void setDilarangPinjam(Buku buku[], int &jumlahData) {
    string idBuku;
    cout << "Masukkan ID buku yang ingin di set tidak boleh dipinjam: ";
    getline(cin, idBuku);

    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].id == idBuku && buku[i].dihapus == false) {
            char konfirmasi;
            cout << "Apakah Anda yakin? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                buku[i].bolehDipinjam = false;
                cout << "Buku dengan ID " << idBuku << " berhasil di set tidak boleh dipinjam!" << endl;
                return;
            } else {
                cout << "Operasi dibatalkan!" << endl;
                return;
            }
        }
    }
    cout << "Buku dengan ID " << idBuku << " yang dicari tidak ditemukan!" << endl;
}

void cariNamaBuku(Buku buku[], int &jumlah) {    
    string cariNama;
    cout << "Masukkan Nama Buku yang dicari: ";
    getline(cin, cariNama);

    bool ditemukan = false;

    cout << "Hasil Pencarian: " << endl;
    cout << left << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(20) << "Pengarang"
         << setw(20) << "Penerbit"
         << setw(20) << "Tahun Terbit"
         << setw(20) << "Genre"
         << setw(5) << "Stok" << endl;
    
    for (int i = 0; i < jumlah; i++) {       
        if (buku[i].judul.find(cariNama) != string::npos) {
            cout << setw(10) << buku[i].id
                << setw(25) << buku[i].judul
                << setw(20) << buku[i].pengarang
                << setw(20) << buku[i].penerbit
                << setw(20) << buku[i].tahunTerbit
                << setw(20) << buku[i].genre
                << setw(5) << buku[i].stok << endl;
            
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada Buku yang mengandung nama '" << cariNama << endl;
    }
}

void pulihkanDataBuku(Buku buku[], int &jumlahBuku) {
    string idBuku;
    cout << "Masukkan ID buku ingin dipulihkan: ";
    getline(cin, idBuku);

    int index = -1;
    for(int i = 0; i < jumlahBuku; i++) {
        if(buku[i].id == idBuku) {
            index = i;
            buku[i].dihapus = false;
            cout << "Buku dengan ID " << idBuku << " berhasil dipulihkan!" << endl;
            break;
        }
    }

    if(index == -1) {
        cout << "Buku dengan ID " << idBuku << " yang dicari tidak ditemukan!" << endl;
        return;
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
         << setw(25) << "Judul Buku"
         << setw(20) << "Nama Peminjam"
         << setw(20) << "Tanggal Pinjam"
         << setw(10) << "Tanggal Kembali" << endl;

         
    for(int i = 0; i < jumlahPinjaman; i++) {
        int index = -1;
        for(int j = 0; j < jumlahBuku; j++) {
            if(buku[j].id == pinjaman[i].idBuku) {
                index = j;
                cout << setw(10) << pinjaman[i].id
                << setw(10) << pinjaman[i].idBuku 
                << setw(25) << buku[j].judul 
                << setw(20) << pinjaman[i].namaPeminjam 
                << setw(20) << pinjaman[i].tanggalPinjam 
                << setw(10) << pinjaman[i].tanggalKembali << endl;
                break;
            }
        }       

        if(index == -1) {
            cout << setw(10) << pinjaman[i].id
                << setw(10) << pinjaman[i].idBuku 
                << setw(25) << "Buku tidak ditemukan" 
                << setw(20) << pinjaman[i].namaPeminjam 
                << setw(20) << pinjaman[i].tanggalPinjam 
                << setw(10) << pinjaman[i].tanggalKembali << endl;
        }
    }
    
    
}

void pinjamBuku(Buku buku[], int &jumlahData, Pinjaman pinjam[], int &jumlahPinjam) {
    string idBuku;
    cout << "Masukkan id buku yang ingin dipinjam: ";
    getline(cin, idBuku);

    int index = -1;
    for(int i = 0; i < jumlahData; i++) {
        if(buku[i].bolehDipinjam == false) {
            cout << "Buku " << buku[i].judul << " tidak boleh dipinjam!" << endl;
            return;
        }

        if(buku[i].stok < 1) {
            cout << "Buku " << buku[i].judul << " tidak tersedia!" << endl;
            return;
        }
        
        if(buku[i].id == idBuku && buku[i].dihapus == false ) {            
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
