#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    int value;
    int fileIndex;
};

// Компаратор для min-heap
struct Compare {
    bool operator()(const Node &a, const Node &b) const {
        return a.key > b.key;
    }
};

class PriorityMerge {
public:
    static void mergeFiles(
        const vector<string> &inputFiles,
        const string &outputFile
    ) {
        int R = inputFiles.size();

        vector<ifstream> files(R);
        for (int i = 0; i < R; ++i) {
            files[i].open(inputFiles[i]);
            if (!files[i])
                throw runtime_error("Ошибка открытия входного файла");
        }

        ofstream out(outputFile);
        if (!out)
            throw runtime_error("Ошибка открытия выходного файла");

        priority_queue<Node, vector<Node>, Compare> pq;

        // Читаем первые элементы
        for (int i = 0; i < R; ++i) {
            Node n;
            if (files[i] >> n.key >> n.value) {
                n.fileIndex = i;
                pq.push(n);
            }
        }

        // Основной цикл слияния
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            out << current.key << " " << current.value << "\n";

            Node next;
            if (files[current.fileIndex] >> next.key >> next.value) {
                next.fileIndex = current.fileIndex;
                pq.push(next);
            }
        }

        for (auto &f: files)
            f.close();
        out.close();
    }
};

class Task5_5 {
public:
    int run() {
        cout << "\n\nЗадание 5.5 Очередь с приоритетами\n\n";


        vector<string> inputFiles = {
            "5_5_block1.txt",
            "5_5_block2.txt",
            "5_5_block3.txt"
        };

        PriorityMerge::mergeFiles(inputFiles, "result.txt");

        cout << "Слияние завершено\n";
        return 0;
    }
};
