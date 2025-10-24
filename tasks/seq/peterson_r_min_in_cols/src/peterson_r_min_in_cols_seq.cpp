#include "peterson_r_min_in_cols_seq.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>

namespace peterson_r_min_in_cols_seq {

std::vector<std::vector<int>> readMatrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }
    
    int rows, cols;
    file >> rows >> cols;
    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                throw std::runtime_error("Error reading matrix element");
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
        throw std::runtime_error("Cannot create file " + filename);
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

}  // namespace peterson_r_min_in_cols_seq
