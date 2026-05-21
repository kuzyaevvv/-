#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Чтение матрицы из файла
vector<vector<double>> readMatrixFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    int n;
    file >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}

// Запись матрицы в файл
void writeMatrixToFile(const vector<vector<double>>& matrix, const string& filename) {
    ofstream file(filename);
    int n = matrix.size();
    file << n << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

// Перемножение матриц
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Time of matrix multiplication: " << duration.count() << " ms" << endl;
    cout << "Problem size: " << n << "x" << n << " matrices" << endl;

    return C;
}

int main() {
    try {
        // Чтение исходных матриц
        auto A = readMatrixFromFile("matrix_A.txt");
        auto B = readMatrixFromFile("matrix_B.txt");

        // Проверка совместимости размеров
        if (A.size() != B.size()) {
            throw runtime_error("Matrix dimensions do not match!");
        }

        // Перемножение матриц
        auto C = multiplyMatrices(A, B);

        // Запись результата
        writeMatrixToFile(C, "result_matrix.txt");

        cout << "Matrix multiplication completed successfully!" << endl;
        cout << "Result saved to 'result_matrix.txt'" << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
