#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

class Word { 
private:
    int *Index;
public:

    int *getIndex() const { 
        return Index;
    }

    void setIndex(int *index) { //сеттер
        Index = index;
    }

    Word *nextWord = nullptr; // следующее слово

    explicit Word(int *index) : Index(index), nextWord(nullptr) {} //конструктор

    void addWord(int *index) { //метод добавления слова
        if (nextWord == nullptr) {
            nextWord = new Word(index);
        } else {
            nextWord->addWord(index);
        }
    }
};

class HashTable {
private:
    std::string textFromFile;
    std::vector<Word *> array;

public:
    explicit HashTable(const std::string &filePath) { //конструктор
        array.resize(120, nullptr);
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line)) { //проходимся по файлу
            textFromFile += line + "\n";
        }
        file.close();
        textIndexing();
        outTable();
    }

    ~HashTable() {// диструктор
        for (Word *symbol: array) {
            delete symbol;
        }
    }

private:
    void outTable() { // метод вывод таблицы
        std::ofstream outFile("data/out.txt");
        outFile << "Table:\n";
        std::string result(50, '-');
        outFile << result << '\n';
        for (int i = 0; i <= 119; ++i) { //проверяет каждый хэш
            if (array[i] != nullptr) { //проверяет, не пустой ли
                outFile << i << ": ";
                Word *currentWord = array[i];
                for (int j = *currentWord->getIndex(); j < textFromFile.length(); j++) { //проходится по тек слову и выводит его
                    if (textFromFile[j] != ' ') {
                        outFile << textFromFile[j];
                    } else {
                        break;
                    }
                }
                outFile << "(" << *currentWord->getIndex() << ")";
                while (currentWord->nextWord != nullptr) { // тоже самое, но для слов в цепочке
                    currentWord = currentWord->nextWord;
                    outFile << " - ";
                    for (int j = *currentWord->getIndex(); j < textFromFile.length(); j++) {
                        if (textFromFile[j] != ' ' && textFromFile[j] != '\n') {
                            outFile << textFromFile[j];
                        } else {
                            break;
                        }
                    }
                    outFile << "(" << *currentWord->getIndex() << ")";
                }
                outFile << '\n';
            }
        }
        outFile << std::string(50, '-');
        outFile << "\n\nText:\n" << textFromFile;
        outFile.close();
    }

    void textIndexing() { //индексируем текст
        std::vector<std::string> words{};
        std::istringstream iss(textFromFile);
        std::string word{};

        while (iss >> word) {// Читаем слова из строки и добавляем в вектор
            words.push_back(word);
        }
        int len = 0;
        for (const auto &elem: words) {
            int currentHash = hash(elem);
            if (array[currentHash] == nullptr) {
                array[currentHash] = new Word(new int(len));
            } else {
                array[currentHash]->addWord(new int(len));
            }
            len += 1 + elem.length();
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
