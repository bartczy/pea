#include "TSP.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <queue>
#include <random>

TSP::TSP() : size(0) {
    srand(time(NULL));
}

// Wczytywanie macierzy z pliku tekstowego
bool TSP::loadFromFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    // Odczyt rozmiaru (pierwsza linia)
    if (!(file >> size)) return false;

    matrix.assign(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
        }
    }

    // Odczyt sum_min z pliku (ostatnia linia)
    std::string line;
    while (file >> line) {
        size_t pos = line.find("sum_min=");
        if (pos != std::string::npos) {
            optimalValue = std::stoi(line.substr(pos + 8));
            break;
        }
    }

    file.close();
    return true;
}

// Algorytm shuffle
void TSP::manualShuffle(std::vector<int>& path) {
    for (int i = size - 1; i > 1; i--) {
        int j = (rand() % i) + 1;
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }
}

// Obliczanie sumy wag krawędzi w cyklu
int TSP::calculateCost(const std::vector<int>& path) {
    long cost = 0;
    for (long i = 0; i < size - 1; i++) {
        long val = matrix[path[i]][path[i + 1]];
        if (val == -1) return 2147483647; // Jeśli trafimy na -1, ścieżka jest nieprawidłowa
        cost += val;
    }
    long lastStep = matrix[path[size - 1]][path[0]];
    if (lastStep == -1) return 2147483647;
    return cost + lastStep;
}

// Główna pętla algorytmu RAND
int TSP::solveRAND(long long iterations) {
    std::vector<int> currentPath(size);
    for (long i = 0; i < size; i++) currentPath[i] = i;

    long minCost = 2147483647; // Max int

    for (long i = 0; i < iterations; i++) {
        manualShuffle(currentPath);
        int currentCost = calculateCost(currentPath);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = currentPath;
        }
    }
    return minCost;
}

//Funkcja pomocnicza: Rekurencyjny Nearest Neighbour
void TSP::nnRecursive(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int startNode, int& bestCost) {
    // Warunek stopu: odwiedziliśmy wszystkie miasta
    if (visitedCount == size) {
        int returnCost = matrix[currentNode][startNode]; // Koszt powrotu do punktu startu
        if (returnCost != -1) {
            int totalCost = currentCost + returnCost;
            if (totalCost < bestCost) {
                bestCost = totalCost; // Znaleźliśmy lepszą trasę
            }
        }
        return;
    }

    int minWeight = 2147483647; // Max int
    std::vector<int> candidates;

    // Szukamy najmniejszej wagi wśród nieodwiedzonych sąsiadów
    for (int i = 0; i < size; i++) {
        if (!visited[i] && matrix[currentNode][i] != -1) {
            if (matrix[currentNode][i] < minWeight) {
                // Znaleźliśmy nową najmniejszą wagę - czyścimy starą listę
                minWeight = matrix[currentNode][i];
                candidates.clear();
                candidates.push_back(i);
            } else if (matrix[currentNode][i] == minWeight) {
                // znaleźliśmy remis - dodajemy do listy kandydatów do rozgałęzienia
                candidates.push_back(i);
            }
        }
    }

    // Ślepa uliczka (brak sąsiadów, a graf nie w pełni odwiedzony)
    if (candidates.empty()) return;

    // Sprawdzamy każdą z wytypowanych dróg
    for (int nextNode : candidates) {
        visited[nextNode] = true;
        nnRecursive(nextNode, visited, currentCost + minWeight, visitedCount + 1, startNode, bestCost);
        visited[nextNode] = false; // Backtracking - cofamy odwiedzenie, by sprawdzić inne gałęzie
    }
}

// Nearest Neighbour (NN)
int TSP::solveNN(int startNode) {
    int bestCost = 2147483647;
    std::vector<bool> visited(size, false);

    visited[startNode] = true;
    nnRecursive(startNode, visited, 0, 1, startNode, bestCost);

    return bestCost;
}

//Repetitive Nearest Neighbour (RNN)
int TSP::solveRNN() {
    int globalBest = 2147483647;

    // RNN uruchamia algorytm NN startując z każdego możliwego miasta
    for (int i = 0; i < size; i++) {
        int currentBest = solveNN(i);
        if (currentBest < globalBest) {
            globalBest = currentBest;
        }
    }

    return globalBest;
}

// Główna funkcja wywołująca brute force
int TSP::solveBnB_DFS(int upperBound) {
    // bestCost nie zaczyna się od max int, tylko od podanego górnego ograniczenia
    int bestCost = upperBound;
    std::vector<bool> visited(size, false);

    visited[0] = true;

    bruteForceRecursiveImproved(0, visited, 0, 1, bestCost);
    return bestCost;
}

// Przeszukiwanie wszerz (BFS)
int TSP::solveBnB_BFS(int upperBound) {
    int bestCost = upperBound;
    std::queue<Node> q;

    std::vector<int> initialPath;
    // Start z miasta 0. Maska 1 << 0 zapala zerowy bit (odwiedzono).
    q.push(Node(0, 0, 1, 1 << 0, initialPath));

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        // Warunek stopu - odwiedzono wszystkie miasta
        if (node.level == size) {
            int returnCost = matrix[node.currentCity][0];
            if (returnCost != -1) {
                int totalCost = node.cost + returnCost;
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestPath = node.path; // Zapisujemy nową najlepszą trasę
                }
            }
            continue;
        }

        // Przeszukiwanie sąsiadów
        for (int i = 0; i < size; ++i) {
            // Sprawdzamy na masce bitowej, czy i-ty bit jest zgaszony (miasto nieodwiedzone)
            if ((node.visitedMask & (1 << i)) == 0 && matrix[node.currentCity][i] != -1) {
                int newCost = node.cost + matrix[node.currentCity][i];

                // Branch & Bound: Wchodzimy w gałąź tylko, jeśli ma szansę pobić najlepszy wynik.
                if (newCost < bestCost) {
                    // Tworzymy nowy węzeł, zapalając i-ty bit w masce: node.visitedMask | (1 << i)
                    q.push(Node(i, newCost, node.level + 1, node.visitedMask | (1 << i), node.path));
                }
            }
        }
    }
    return bestCost;
}

// Przeszukiwanie najniższy koszt (Best-First Search)
int TSP::solveBnB_BestFirstSearch(int upperBound) {
    int bestCost = upperBound;
    // Kolejka priorytetowa używa przeciążonego operatora > ze struktury Node
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    std::vector<int> initialPath;
    pq.push(Node(0, 0, 1, 1 << 0, initialPath));

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // Dodatkowe cięcie: jeśli wyciągnięty z kolejki węzeł już jest droższy niż bestCost,
        // przerywamy jego analizę.
        if (node.cost >= bestCost) continue;

        // Warunek stopu
        if (node.level == size) {
            int returnCost = matrix[node.currentCity][0];
            if (returnCost != -1) {
                int totalCost = node.cost + returnCost;
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestPath = node.path;
                }
            }
            continue;
        }

        // Przeszukiwanie sąsiadów
        for (int i = 0; i < size; ++i) {
            if ((node.visitedMask & (1 << i)) == 0 && matrix[node.currentCity][i] != -1) {
                int newCost = node.cost + matrix[node.currentCity][i];

                if (newCost < bestCost) {
                    pq.push(Node(i, newCost, node.level + 1, node.visitedMask | (1 << i), node.path));
                }
            }
        }
    }
    return bestCost;
}

// Funkcja rekurencyjna przeszukująca wszystkie permutacje
void TSP::bruteForceRecursive(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int& bestCost) {
    // Warunek stopu - odwiedzono wszystkie miasta
    if (visitedCount == size) {
        int returnCost = matrix[currentNode][0]; // Powrót do miasta startowego
        if (returnCost != -1) {
            int totalCost = currentCost + returnCost;
            if (totalCost < bestCost) {
                bestCost = totalCost;
            }
        }
        return;
    }

    // Przeszukiwanie wszystkich sąsiadów
    for (int i = 0; i < size; ++i) {
        if (!visited[i] && matrix[currentNode][i] != -1) {
            visited[i] = true;
            // Idziemy dalej nie sprawdzając czy to się opłaca
            bruteForceRecursive(i, visited, currentCost + matrix[currentNode][i], visitedCount + 1, bestCost);
            visited[i] = false;
        }
    }
}

// Ulepszona funkacja która przycina nie opłacalne ścieżki
void TSP::bruteForceRecursiveImproved(int currentNode, std::vector<bool>& visited, int currentCost, int visitedCount, int& bestCost) {
    // Warunek stopu - odwiedzono wszystkie miasta
    if (visitedCount == size) {
        int returnCost = matrix[currentNode][0]; // Powrót do miasta 0
        if (returnCost != -1) {
            int totalCost = currentCost + returnCost;
            if (totalCost < bestCost) {
                bestCost = totalCost; // Znaleziono nową lepszą trasę
            }
        }
        return;
    }

    // Przeszukiwanie sąsiadów
    for (int i = 0; i < size; ++i) {
        if (!visited[i] && matrix[currentNode][i] != -1) {

            // Optymalizacja (Branch & Bound):
            // Wchodzimy w gałąź tylko, jeśli ma szansę pobić najlepszy wynik.
            if (currentCost + matrix[currentNode][i] < bestCost) {
                visited[i] = true;
                bruteForceRecursiveImproved(i, visited, currentCost + matrix[currentNode][i], visitedCount + 1, bestCost);
                visited[i] = false; // Backtracking
            }
        }
    }
}

// Generowanie niesymetrycznej macierzy
void TSP::generateRandomAsymetric(int n, std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << n << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                file << "-1 "; // Przekatna
            } else {
                file << (rand() % 100 + 1) << " "; // Wagi od 1 do 100
            }
        }
        file << std::endl;
    }
    file << "sum_min=0" << std::endl; // Dla losowych nie znamy optimum
    file.close();
    std::cout << "Wygenerowano instancje: " << filename << std::endl;
}

// Generowanie symetrycznej macierzy
void TSP::generateRandomSymmetric(int n, std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Blad otwarcia pliku!" << std::endl;
        return;
    }

    file << n << std::endl;

    // Tworzymy tymczasową macierz w pamięci, żeby łatwo zapisać lustrzane odbicie
    std::vector<std::vector<int>> tempMatrix(n, std::vector<int>(n, 0));

    // Losujemy wagi tylko dla górnej połowy macierzy i kopiujemy na dół
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                tempMatrix[i][j] = -1; // Przekątna
            } else {
                int weight = rand() % 100 + 1; // Wagi od 1 do 100
                tempMatrix[i][j] = weight;     // A -> B
                tempMatrix[j][i] = weight;     // B -> A
            }
        }
    }

    // Zapisujemy gotową macierz do pliku
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << tempMatrix[i][j] << " ";
        }
        file << std::endl;
    }

    file << "sum_min=0" << std::endl;
    file.close();
    std::cout << "Wygenerowano instancje symetryczna: " << filename << std::endl;
}