//
// Created by bartek on 11.03.2026.
//

#ifndef LAB01_TSP_H
#define LAB01_TSP_H
#include <vector>
#include <string>

struct Node {
    int currentCity;          // W którym mieście obecnie jesteśmy
    int cost;                 // Koszt dojścia do tego miasta
    int level;                // Głębokość w drzewie (ile miast odwiedziliśmy)
    unsigned int visitedMask; // Maska bitowa reprezentująca odwiedzone miasta
    std::vector<int> path;    // Historia trasy (do ostatecznego zapisu)

    // Konstruktor
    Node(int city, int c, int l, unsigned int mask, std::vector<int> p)
        : currentCity(city), cost(c), level(l), visitedMask(mask), path(p) {
        path.push_back(city); // Od razu dodajemy miasto do trasy
    }

    // Przeciążenie operatora dla kolejki priorytetowej (Best-First Search)
    // Chcemy, żeby węzeł z najmniejszym kosztem był wyciągany jako pierwszy
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

class TSP {
private:
    std::vector<std::vector<int>> matrix; // Macierz wag
    int size;                             // Liczba miast
    int optimalValue; // Wartość sum_min z pliku
    std::vector<int> bestPath;            // Najlepsza znaleziona trasa

public:
    TSP();

    // Algorytm RAND
    int solveRAND(long long iterations);

    //Algorytmy Zachłanne
    int solveNN(int startNode);
    int solveRNN();

    // Funkcja rekurencyjna obsługująca rozgałęzienia
    void nnRecursive(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int startNode, int& bestCost);

    // Przegląd Zupełny (Brute Force)
    int solveBnB_DFS(int upperBound);
    int solveBnB_BFS(int upperBound);
    int solveBnB_BestFirstSearch(int upperBound);
    void bruteForceRecursive(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int& bestCost);
    void bruteForceRecursiveImproved(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int& bestCost);

    // Pomocnicze
    void manualShuffle(std::vector<int>& path);
    int calculateCost(const std::vector<int>& path);

    int getSize() { return size; }
    int getOptimalValue() { return optimalValue; }

    bool loadFromFile(std::string filename);
    void generateRandom(int n);

    void generateRandomAsymetric(int n, std::string filename);
    void generateRandomSymmetric(int n, std::string filename);

};

#endif //LAB01_TSP_H