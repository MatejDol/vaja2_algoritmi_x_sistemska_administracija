#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void binaryRadixSort(std::vector<unsigned char>& arr) {
    std::vector<unsigned char> tmp(arr.size());
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
        std::cout << "Uporaba: vaja <vhodna_datoteka>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cout << "Ne morem odpreti datoteke\n";
        return 1;
    }

    std::vector<unsigned char> arr;
    std::string line;
    if (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (token.empty()) continue;
            int value = std::stoi(token);
            if (value < 0 || value > 255) continue;
            arr.push_back(static_cast<unsigned char>(value));
        }
    }
    in.close();

    binaryRadixSort(arr);

    std::ofstream out("out.txt");
    for (size_t i = 0; i < arr.size(); ++i) {
        out << static_cast<int>(arr[i]);
        if (i + 1 < arr.size()) out << ",";
    }
    out.close();

    std::cout << "Sortirano v out.txt\n";
    return 0;
}

