#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

const std::string FILE_PATH = "data/main.txt";

void randomWriteInFile(int count, int min, int max) { // рандомно пишет циферки в файле 
    srand(time(nullptr));
    std::ofstream file(FILE_PATH);
    for (int i = 0; i < count; ++i) {
        file << std::to_string(rand() % (max - min + 1) + min) << "\n";
    }
    file.close();
}

class PolyphaseMergeSort {
private:
    std::string filePath; //путь к файлу, в котором лежат несортированные числа
    bool fileFlag; 
    int numberIndex;
    int partCount; //вспомагательная переменная, счётчик
    const int s{4}; 
    int mainSize;
    std::vector<int> part;

public:
    explicit PolyphaseMergeSort(const std::string &filePath) : fileFlag(false), // конструктор
                                                               numberIndex(0), partCount(0),
                                                               mainSize(0),
                                                               filePath(filePath) {
        createTempFiles(); 
        sort(); 
        writeOutFile(); 
    }

private:
    void createTempFiles() { //создаём вспомагательные файлы, которые будут помогать с сортировкой
        for (int i = 0; i < 4; ++i) {
            std::ofstream("data/temp/" + std::to_string(i)).close();
        }
    }

    void sort() { // сортировка 
        fileToSortPart();
        bool tempFlag = true;
        int tempSize = s / 2;
        while (tempSize < mainSize) {
            inFilesSort(tempFlag, tempSize);
            tempSize *= 2;
            tempFlag = !tempFlag;
        }
        fileFlag = tempFlag;
    }

    void writeOutFile() { // копирует сортированные числа в выходной файлик
        std::ifstream reader(std::string("data/temp/") + (fileFlag ? "0" : "2")); // открываем файлик нулевой или второй
        std::string result;
        for (std::string line; getline(reader, line);) { 
            result += line + "\n"; 
        }
        reader.close();
        std::ofstream("data/out.txt") << result;
        for (int i = 0; i < 4; ++i) {
            remove(("data/temp/" + std::to_string(i)).c_str());
        }
    }

    void fileToSortPart() { // запись числе из исходного файла в файлы 0 и 1
        try { 
            std::ifstream inputFile(filePath);
            std::string line;
            while (getline(inputFile, line)) { 
                if (numberIndex % s == 0 && numberIndex != 0) { //если оно кратно s 
                    std::sort(part.begin(), part.end()); //сортируем
                    mainSize += part.size(); //размер части
                    partWrite(partCount++ % 2); //просто записывает 
                }
                part.push_back(std::stoi(line));
                ++numberIndex;
            }
            std::sort(part.begin(), part.end()); //сортировка опять.....
            mainSize += part.size();
            partWrite(partCount++ % 2);
            inputFile.close();
        } catch (const std::ios_base::failure &e) {
            std::cerr << "Exception opening/reading file";
        }
    }

    void inFilesSort(bool firstFiles, int currentSize) { // сортировка слиянием (рассматриваем два кусочка и сортируем их, куски разных размеров каждый раз)
        int fileName = firstFiles ? 0 : 2;
        std::string temp = "data/temp/";
        std::string FR = std::to_string(fileName);
        std::string SR = std::to_string(fileName + 1);
        std::string FW = std::to_string((fileName + 2) % 4);
        std::string SW = std::to_string((fileName + 2) % 4 + 1);
        std::ifstream firstReader(temp + FR);
        std::ifstream secondReader(temp + SR);
        std::ofstream firstWriter(temp + FW);
        std::ofstream secondWriter(temp + SW);

        bool writerFlag = true;
        std::string result;

        int i = 0, j = 0;
        std::string firstValue, secondValue;
        firstReader >> firstValue;
        secondReader >> secondValue;
        while (!firstReader.eof() || !secondReader.eof()) {
            if (j == i && i == currentSize) {
                if (writerFlag) {
                    firstWriter << result;
                } else {
                    secondWriter << result;
                }
                writerFlag = !writerFlag;
                result = "";
                i = 0;
                j = 0;
            }

            if (!firstReader.eof() && !secondReader.eof()) {
                if (i < currentSize && j < currentSize) {
                    if (std::stoi(firstValue) < std::stoi(secondValue)) {
                        result += firstValue + "\n";
                        firstReader >> firstValue;
                        ++i;
                    } else {
                        result += secondValue + "\n";
                        secondReader >> secondValue;
                        ++j;
                    }
                } else if (i < currentSize) {
                    result += firstValue + "\n";
                    firstReader >> firstValue;
                    ++i;
                } else {
                    result += secondValue + "\n";
                    secondReader >> secondValue;
                    ++j;
                }
            }
            else if (firstReader.eof()) {
                if (j < currentSize) {
                    result += secondValue + "\n";
                    secondReader >> secondValue;
                    ++j;
                } else {
                    ++j;
                }
            } else if (secondReader.eof()) {
                if (i < currentSize) {
                    result += firstValue + "\n";
                    firstReader >> firstValue;
                    ++i;
                } else {
                    ++i;

                }
            } else if (!firstReader.eof() && i < currentSize) {
                result += firstValue + "\n";
                firstReader >> firstValue;
                ++i;
            } else if (!secondReader.eof() && j < currentSize) {
                result += secondValue + "\n";
                secondReader >> secondValue;
                ++j;
            }
        }

        if (writerFlag) {
            firstWriter << result;
        } else {
            secondWriter << result;
        }

        firstReader.close();
        secondReader.close();
        firstWriter.close();
        secondWriter.close();
        remove(("data/temp/" + std::to_string(fileName)).c_str());
        remove(("data/temp/" + std::to_string(fileName + 1)).c_str());
    }

    void partWrite(int fileName) { // записывает все числа из массива part внутрь темп файла
        std::ofstream tempFile("data/temp/" + std::to_string(fileName), std::ios_base::app);
        for (const auto &value: part) {
            tempFile << value << "\n";
        }
        tempFile.close();
        part.clear();
    }
};

int main() {
    randomWriteInFile(16, -1000, 1000);
    PolyphaseMergeSort testSort(FILE_PATH);
}