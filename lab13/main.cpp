#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <functional> // ��� std::hash
#include <fstream>
#include <string>
#include <sstream>

class HashTable {
private:
    std::string textFromFile;
    std::vector<std::vector<int>> array;

public:
    explicit HashTable(const std::string &filePath) { // �����������, ����������� ���� � �����
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "������ �������� �����!" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) { // ������ ���� � ��������� �����
            textFromFile += line + "\n";
        }
        
        array.resize(120);// �������������� ������ �������

        textIndexing();// ����������� �����

        outTable();// ������� �������
    }

private:
    void outTable() const { //������� �������
        std::ofstream outFile("data/out.txt"); //��������� ��� ������

        if (!outFile.is_open()) {
            std::cerr << "������ �������� ����� ��� ������!" << std::endl;
            return;
        }

        outFile << "Table:\n"; //���������� Table 
        for (int i = 0; i < 81; ++i) {
            outFile << "-";
        }
        outFile << "\n";

        for (int i = 0; i < array.size(); i++) { // ���������� �� ������� ���-���� � ���������, �������� �� �� ��� ��� ���
            if (!array[i].empty()) {
                outFile << i << ": ";
                for (int j = array[i][0]; j < textFromFile.length(); j++) {
                    if (textFromFile[j] != ' ') {
                        outFile << textFromFile[j];
                    } else {
                        break;
                    }
                }
                outFile << '\n';
            }
        }

        for (int i = 0; i < 81; ++i) {
            outFile << "-";
        }

        outFile << "\n\nText:\n" << textFromFile;

        outFile.close();
    }

    bool check(const std::vector<std::string> &words, int i, int len) { //��������� ��������� �� ����� � ������ �������
        bool flag = true;
        for (int j = 0; j < words[i].length(); j++) {
            if (words[i][j] != textFromFile[len + j]) {
                flag = false;
                break;
            }
        }
        return flag;
    }

    void textIndexing() { // ����������� �����
        std::vector<std::string> words{};
        std::istringstream iss(textFromFile);
        std::string word{};
        
        while (iss >> word) { // ������ ����� �� ������ � ��������� � ������
            words.push_back(word);
        }
        int len = 0;
        for (int i = 0; i < words.size(); i++) { //���� �� ������
            int currentHash = hash(words[i]);
            while (!array[currentHash].empty() && !check(words, i, len)) {//�������� ����������� ��������� (�������� - ��� ����� ��������� ������������� ���-����)
                currentHash = hash(std::to_string(currentHash));
            }
            array[currentHash].push_back(len);
            len += 1 + words[i].length();
        }
    }

    int hash(const std::string &str) const {
        return std::hash<std::string>{}(str) % 120;
    }
};

int main() {
    HashTable hashTable("data/input.txt");

    return 0;
}
