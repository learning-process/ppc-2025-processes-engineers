#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

std::vector<std::vector<int>> readMatrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        exit(1);
    }
    
    int rows, cols;
    file >> rows >> cols;
    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                std::cerr << "Error reading matrix element at (" << i << "," << j << ")" << std::endl;
                exit(1);
            }
        }
    }
    
    file.close();
    return matrix;
}

std::vector<int> findMinInColumns(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return {};
    
    int cols = matrix[0].size();
    std::vector<int> minValues(cols, std::numeric_limits<int>::max());
    
    for (int j = 0; j < cols; ++j) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            if (matrix[i][j] < minValues[j]) {
                minValues[j] = matrix[i][j];
            }
        }
    }
    
    return minValues;
}

void writeResults(const std::vector<int>& minValues, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create file " << filename << std::endl;
        return;
    }
    
    for (size_t i = 0; i < minValues.size(); ++i) {
        file << minValues[i];
        if (i != minValues.size() - 1) {
            file << " ";
        }
    }
    file << std::endl;
    
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    try {
        // Чтение матрицы
        auto matrix = readMatrix(inputFile);
        
        // Поиск минимальных значений по столбцам
        auto minValues = findMinInColumns(matrix);
        
        // Запись результатов
        writeResults(minValues, outputFile);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
