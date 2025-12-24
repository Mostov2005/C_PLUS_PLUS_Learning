#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> size;
    int setsCount;

public:
    DSU(int n) : parent(n), size(n, 1), setsCount(n) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // сжатие пути
        return parent[x];
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return; // уже в одной сети

        // объединяем по размеру
        if (size[rx] < size[ry]) swap(rx, ry);

        parent[ry] = rx;
        size[rx] += size[ry];
        setsCount--; // уменьшили количество сетей

        cout << "Parent: ";
        for (size_t i = 0; i < parent.size(); ++i)
            cout << parent[i] << " ";
        cout << "\n";
        cout << "Sizes: ";
        for (size_t i = 0; i < size.size(); ++i)
            cout << size[i] << " ";
        cout << "\n";
    }

    int count() const {
        return setsCount;
    }
};

class Task5_6 {
public:
    int run() {
        cout << "\n\nЗадание 5.6* Система непересекающихся множеств\n\n";


        int N = 5; // количество компьютеров
        DSU dsu(N);

        vector<pair<int, int> > queries = {
            {0, 1},
            {2, 3},
            {1, 2},
            {1, 2},
            {3, 4}
        };

        for (auto [u, v]: queries) {
            dsu.unite(u, v);
            cout << "Осталось изолированных сетей: " << dsu.count() << "\n";
        }

        return 0;
    }
};
