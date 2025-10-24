#include <iostream>
#include "peterson_r_min_in_cols_seq.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    try {
        auto matrix = peterson_r_min_in_cols_seq::readMatrix(inputFile);
        auto minValues = peterson_r_min_in_cols_seq::findMinInColumns(matrix);
        peterson_r_min_in_cols_seq::writeResults(minValues, outputFile);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
