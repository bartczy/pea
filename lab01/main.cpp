#include <iostream>
#include <iomanip>
#include <chrono>
#include "TSP.h"

int main() {
    TSP problem;
    // std::string fileName = "matrix_6x6.atsp"; int upperBound = 150;
    // std::string fileName = "matrix_8x8.atsp"; int upperBound = 145;
    // std::string fileName = "matrix_11x11.atsp"; int upperBound = 160;
    // std::string fileName = "matrix_12x12.atsp"; int upperBound = 203;
    // std::string fileName = "matrix_13x13.atsp"; int upperBound = 216;
    // std::string fileName = "matrix_14x14.atsp"; int upperBound = 172;
    // std::string fileName = "matrix_15x15.atsp"; int upperBound = 210;
    // std::string fileName = "matrix_16x16.atsp"; int upperBound = 294;
    // std::string fileName = "matrix_17x17.atsp"; int upperBound = 235;
    // std::string fileName = "matrix_18x18.atsp"; int upperBound = 229;
    // std::string fileName = "matrix_19x19.atsp"; int upperBound = 178;
    // std::string fileName = "matrix_20x20.atsp"; int upperBound = 262;
    // std::string fileName = "matrix_21x21.atsp"; int upperBound = 231;
    // std::string fileName = "matrix_22x22.atsp"; int upperBound = 239;
    // std::string fileName = "matrix_23x23.atsp"; int upperBound = 272;
    // std::string fileName = "matrix_50x50.atsp"; int upperBound = 239;
    // std::string fileName = "matrix_60x60.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_70x70.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_71x71.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_72x72.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_73x73.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_74x74.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_75x75.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_76x76.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_77x77.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_78x78.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_79x79.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_80x80.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_90x90.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_91x91.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_92x92.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_93x93.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_94x94.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_95x95.atsp"; int upperBound = 2147483647;
    // std::string fileName = "matrix_100x100.atsp"; int upperBound = 2147483647;

    // std::string fileName = "s_matrix_6x6.atsp"; int upperBound = 266;
     std::string fileName = "s_matrix_8x8.atsp"; int upperBound = 242;
    // std::string fileName = "s_matrix_11x11.atsp"; int upperBound = 185;
    // std::string fileName = "s_matrix_12x12.atsp"; int upperBound = 208;
    // std::string fileName = "s_matrix_13x13.atsp"; int upperBound = 190;
    // std::string fileName = "s_matrix_14x14.atsp"; int upperBound = 2147483647;
    // std::string fileName = "s_matrix_15x15.atsp"; int upperBound = 210;
    // std::string fileName = "s_matrix_16x16.atsp"; int upperBound = 172;
    // std::string fileName = "s_matrix_17x17.atsp"; int upperBound = 238;
    // std::string fileName = "s_matrix_18x18.atsp"; int upperBound = 192;
    // std::string fileName = "s_matrix_19x19.atsp"; int upperBound = 341;
    // std::string fileName = "s_matrix_20x20.atsp"; int upperBound = 201;
    // std::string fileName = "s_matrix_21x21.atsp"; int upperBound = 239;
    // std::string fileName = "s_matrix_22x22.atsp"; int upperBound = 240;
    // std::string fileName = "s_matrix_23x23.atsp"; int upperBound = 281;
    // std::string fileName = "s_matrix_24x24.atsp"; int upperBound = 291;
    // std::string fileName = "s_matrix_25x25.atsp"; int upperBound = 254;
    // std::string fileName = "s_matrix_26x26.atsp"; int upperBound = 301;
    // std::string fileName = "s_matrix_27x27.atsp"; int upperBound = 247;
    // std::string fileName = "s_matrix_28x28.atsp"; int upperBound = 229;
    // std::string fileName = "s_matrix_29x29.atsp"; int upperBound = 206;

    // upperBound = 2147483647;


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


         // int result = problem.solveBnB_DFS(upperBound);
         // int result = problem.solveBnB_BFS(upperBound);
          int result = problem.solveBnB_BestFirstSearch(upperBound);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;

        double error = 0;
        if (opt > 0) {
            error = (static_cast<double>(result - opt) / opt) * 100.0;
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
     problem.generateRandomAsymetric(16, "matrix_16x16.atsp");
     problem.generateRandomAsymetric(17, "matrix_17x17.atsp");
     problem.generateRandomAsymetric(18, "matrix_18x18.atsp");
     problem.generateRandomAsymetric(19, "matrix_19x19.atsp");

*/

    return 0;
}