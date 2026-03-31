#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void binaryRadixSort(vector<unsigned char>& arr) {
    vector<unsigned char> tmp(arr.size());
    for (int bit = 0; bit < 8; ++bit) {
        int count0 = 0;
        for (unsigned char x : arr) {
            if (((x >> bit) & 1) == 0) count0++;
        }
        int i0 = 0;
        int i1 = count0;
        for (unsigned char x : arr) {
            if (((x >> bit) & 1) == 0) tmp[i0++] = x;
            else tmp[i1++] = x;
        }
        for (size_t i = 0; i < arr.size(); ++i) {
            arr[i] = tmp[i];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "potrebno je zagnati program kot: vaja <vhodna_datoteka>";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cout << "ne morem odpreti datoteke";
        return 1;
    }

    vector<unsigned char> arr;
    string line;
    if (getline(in, line)) {
        istringstream ss(line);
        int value;
        while (ss >> value) {
            if (value < 0 || value > 255) continue;
            arr.push_back(static_cast<unsigned char>(value));
        }
    }
    in.close();

    binaryRadixSort(arr);

    ofstream out("out.txt");
    for (size_t i = 0; i < arr.size(); ++i) {
        out << static_cast<int>(arr[i]);
        if (i + 1 < arr.size()) out << ",";
    }
    out.close();

    cout << "Sortirano v out.txt";
    return 0;
}

