#include <iostream>
#include <iomanip>
#include <chrono>
#include "TSP.h"

int main() {
    TSP problem;
      std::string fileName = "matrix_6x6.atsp";
    // std::string fileName = "matrix_8x8.atsp";
    // std::string fileName = "matrix_11x11.atsp";
    // std::string fileName = "matrix_12x12.atsp";
    // std::string fileName = "matrix_13x13.atsp";
    // std::string fileName = "matrix_14x14.atsp";
    // std::string fileName = "matrix_15x15.atsp";
    // std::string fileName = "matrix_20x20.atsp";
    // std::string fileName = "matrix_21x21.atsp";
    // std::string fileName = "matrix_22x22.atsp";
    // std::string fileName = "matrix_23x23.atsp";
    // std::string fileName = "matrix_50x50.atsp";
    // std::string fileName = "matrix_60x60.atsp";
    // std::string fileName = "matrix_70x70.atsp";
    // std::string fileName = "matrix_71x71.atsp";
    // std::string fileName = "matrix_72x72.atsp";
    // std::string fileName = "matrix_73x73.atsp";
    // std::string fileName = "matrix_74x74.atsp";
    // std::string fileName = "matrix_75x75.atsp";
    // std::string fileName = "matrix_76x76.atsp";
    // std::string fileName = "matrix_77x77.atsp";
    // std::string fileName = "matrix_78x78.atsp";
    // std::string fileName = "matrix_79x79.atsp";
    // std::string fileName = "matrix_80x80.atsp";
    // std::string fileName = "matrix_90x90.atsp";
    // std::string fileName = "matrix_91x91.atsp";
    // std::string fileName = "matrix_92x92.atsp";
    // std::string fileName = "matrix_93x93.atsp";
    // std::string fileName = "matrix_94x94.atsp";
    // std::string fileName = "matrix_95x95.atsp";
    // std::string fileName = "matrix_100x100.atsp";

   // std::string fileName = "s_matrix_6x6.atsp";
    // std::string fileName = "s_matrix_8x8.atsp";
    // std::string fileName = "s_matrix_11x11.atsp";
    // std::string fileName = "s_matrix_12x12.atsp";
    // std::string fileName = "s_matrix_13x13.atsp";
    // std::string fileName = "s_matrix_14x14.atsp";
    // std::string fileName = "s_matrix_15x15.atsp";
    // std::string fileName = "s_matrix_16x16.atsp";
    // std::string fileName = "s_matrix_17x17.atsp";
    // std::string fileName = "s_matrix_18x18.atsp";
    // std::string fileName = "s_matrix_19x19.atsp";
        // std::string fileName = "s_matrix_20x20.atsp";

    if (!problem.loadFromFile(fileName)) {
        std::cout << "Blad pliku!" << std::endl;
        return 1;
    }

    int opt = problem.getOptimalValue();
    // Liczba iteracji do testowania
    long long iterations = 190;

    std::cout << "Instancja: " << fileName << " (Rozmiar: " << problem.getSize() << ")" << std::endl;
    if (opt==0) {
        std::cout << "Brak znanego wyniku optymalnego" << std::endl;
    }else {
        std::cout << "Znany wynik optymalny: " << opt << std::endl;
    }
    std::cout << "--- Rozpoczynam badanie ---" << std::endl;

   // for (int i = 0; i < 10; ++i) {
     //   std::cout << "proba nr: " << i << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
       // int result = problem.solveRAND(iterations);
        //  int result = problem.solveNN(0);
        // int result = problem.solveRNN();

          int upperBound = 2147483647;
         // int result = problem.solveBnB_DFS(upperBound);
         // int result = problem.solveBnB_BFS(upperBound);
           int result = problem.solveBnB_BestFirstSearch(upperBound);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;

        double error = 0;
        if (opt > 0) {
            error = (static_cast<double>(result - opt) / opt) * 100.0;
        } else {
            std::cout << " (Brak znanego rozwiazania optymalnego dla tej instancji) ";
        }

        std::cout << "Najlepszy znaleziony koszt: " << result << std::endl;
        std::cout << "Blad wzgledny: " << std::fixed << std::setprecision(2) << error << "%" << std::endl;
        std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
        std::cout << "Czas wykonania w sekundach: " << elapsed.count() / 1000 << " s" << std::endl;
        std::cout << "Czas wykonania w minutach: " << elapsed.count() / 60000 << " min" << std::endl;

    /*
        if (error <= 10.0) {
            std::cout << "SUKCES: Osiagnieto blad ponizej 10%!" << std::endl;
        }
        */
  //  }
    /*
     problem.generateRandomSymmetric(16, "s_matrix_16x16.atsp");
     problem.generateRandomSymmetric(17, "s_matrix_17x17.atsp");
     problem.generateRandomSymmetric(18, "s_matrix_18x18.atsp");
     problem.generateRandomSymmetric(19, "s_matrix_19x19.atsp");

*/


    return 0;
}