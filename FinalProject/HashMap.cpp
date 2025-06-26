#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <functional>
#include <iomanip>
#include <climits>

using namespace std;

const int TABLE_SIZE = 100;

struct HashNode {
    string key;
    string value;
};

class HashMap {
private:
    vector<list<HashNode>> table;

    unsigned int u32(const string& str) {
        unsigned int hash = 0;
        for (char c : str) {
            hash = hash * 31 + c;
        }
        return hash;
    }

    int hashFunction(const string& key) {
        return u32(key) % TABLE_SIZE;
    }

public:
    HashMap() {
        table.resize(TABLE_SIZE);
    }

    void insert(const string& value) {
        string key = to_string(u32(value));
        int idx = hashFunction(key);

        for (auto& node : table[idx]) {
            if (node.key == key) {
                cout << "Data sudah ada!\n";
                return;
            }
        }
        table[idx].push_back({ key, value });
    }

    bool search(const string& value) {
        string key = to_string(u32(value));
        int idx = hashFunction(key);

        for (const auto& node : table[idx]) {
            if (node.key == key && node.value == value) {
                return true;
            }
        }
        return false;
    }

    void remove(const string& value) {
        string key = to_string(u32(value));
        int idx = hashFunction(key);

        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (it->key == key && it->value == value) {
                table[idx].erase(it);
                cout << "Data berhasil dihapus.\n";
                return;
            }
        }
        cout << "Data tidak ditemukan.\n";
    }

    void update(const string& oldValue, const string& newValue) {
        string key = to_string(u32(oldValue));
        int idx = hashFunction(key);

        for (auto& node : table[idx]) {
            if (node.key == key && node.value == oldValue) {
                node.value = newValue;
                node.key = to_string(u32(newValue));
                cout << "Data berhasil diupdate menjadi: " << newValue << endl;
                return;
            }
        }
        cout << "Data tidak ditemukan.\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (const auto& node : table[i]) {
                cout << "[" << node.key << "] " << node.value << endl;
            }
        }
    }

    void loadFromFile(const string& path) {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Gagal membuka file!\n";
            return;
        }

        string line;
        int count = 0;

        auto start = chrono::high_resolution_clock::now();
        while (getline(file, line)) {
            insert(line);
            count++;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::duration<double, micro>>(end - start).count();

        cout << count << " data berhasil dimasukkan dari " << path << " dalam " << fixed << setprecision(4) << duration << " mikrodetik.\n";
    }

    void searchWithPreciseTime(const string& value) {
        const int repeat = 100000;
        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < repeat; ++i) {
            search(value);
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::duration<double, micro>>(end - start).count();

        bool found = search(value);
        if (found)
            cout << "Data ditemukan. Waktu rata-rata pencarian: " << fixed << setprecision(4) << duration / repeat << " mikrodetik\n";
        else
            cout << "Data tidak ditemukan. Waktu rata-rata pencarian: " << fixed << setprecision(4) << duration / repeat << " mikrodetik\n";
    }

    int totalData() {
        int total = 0;
        for (const auto& bucket : table)
            total += bucket.size();
        return total;
    }

    void analyzeCases() {
        string bestCaseValue = "";
        string worstCaseValue = "";
        int minSize = INT_MAX;
        int maxSize = INT_MIN;

        for (int i = 0; i < TABLE_SIZE; ++i) {
            int bucketSize = table[i].size();
            if (bucketSize == 0) continue;

            if (bucketSize < minSize) {
                minSize = bucketSize;
                bestCaseValue = table[i].front().value;
            }
            if (bucketSize > maxSize) {
                maxSize = bucketSize;
                worstCaseValue = table[i].back().value;
            }
        }

        cout << "\n=== Analisis Kasus Realistis ===\n";
        cout << "Best Case: Cari '" << bestCaseValue << "' di bucket tersempit (" << minSize << " elemen)\n";
        cout << "Worst Case: Cari '" << worstCaseValue << "' di bucket terpadat (" << maxSize << " elemen)\n";
        cout << "Average Case: Rata-rata elemen per bucket: " << fixed << setprecision(2) << (float)totalData() / TABLE_SIZE << endl;

        cout << "\nPengujian Waktu:\n";
        searchWithPreciseTime(bestCaseValue);
        searchWithPreciseTime(worstCaseValue);
    }
    size_t estimateMemory() const {
    size_t total = 0;

    // Estimasi memori struktur vector
    total += sizeof(table);
    total += table.capacity() * sizeof(list<HashNode>);

    // Estimasi memori untuk setiap elemen list di setiap bucket
    for (const auto& bucket : table) {
        total += sizeof(bucket);
        for (const auto& node : bucket) {
            total += sizeof(HashNode);
            total += sizeof(char) * (node.key.capacity() + 1);
            total += sizeof(char) * (node.value.capacity() + 1);
        }
    }
    return total;
}

};

int main() {
    HashMap map;
    int pilihan;
    string value, newValue;

    do {
        cout << "\n===== Menu HashMap =====\n";
        cout << "1. Load Data nama_100_orang.txt\n";
        cout << "2. Load Data nama_500_orang.txt\n";
        cout << "3. Load Data nama_1000_orang.txt\n";
        cout << "4. Tambah Data Manual\n";
        cout << "5. Cari Data\n";
        cout << "6. Update Data\n";
        cout << "7. Hapus Data\n";
        cout << "8. Tampilkan Semua Data\n";
        cout << "9. Exit\n";
        cout << "10. Analisis Best/Worst Case\n";
        cout << "11. Analisis Memory\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            map.loadFromFile("Data/nama_100_orang.txt");
            break;
        case 2:
            map.loadFromFile("Data/nama_500_orang.txt");
            break;
        case 3:
            map.loadFromFile("Data/nama_1000_orang.txt");
            break;
        case 4:
            cout << "Masukkan data: ";
            getline(cin, value);
            map.insert(value);
            break;
        case 5:
            cout << "Masukkan data yang ingin dicari: ";
            getline(cin, value);
            map.searchWithPreciseTime(value);
            break;
        case 6:
            cout << "Masukkan data lama yang ingin diupdate: ";
            getline(cin, value);
            cout << "Masukkan data baru: ";
            getline(cin, newValue);
            map.update(value, newValue);
            break;
        case 7:
            cout << "Masukkan data yang ingin dihapus: ";
            getline(cin, value);
            map.remove(value);
            break;
        case 8:
            map.display();
            break;
        case 9:
            cout << "Keluar program...\n";
            break;
        case 10:
            map.analyzeCases();
            break;
        case 11:
            cout << "Total estimasi memori HashMap: " << map.estimateMemory() << " byte\n";
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 9);

    return 0;
}
