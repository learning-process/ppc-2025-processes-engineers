#ifndef PETERSON_R_MIN_IN_COLS_SEQ_H
#define PETERSON_R_MIN_IN_COLS_SEQ_H

#include <vector>
#include <string>

cat > include/peterson_r_min_in_cols_seq.h << 'EOF'
#ifndef PETERSON_R_MIN_IN_COLS_SEQ_H
#define PETERSON_R_MIN_IN_COLS_SEQ_H

#include <vector>
#include <string>

namespace peterson_r_min_in_cols_seq {

std::vector<std::vector<int>> readMatrix(const std::string& filename);
std::vector<int> findMinInColumns(const std::vector<std::vector<int>>& matrix);
void writeResults(const std::vector<int>& minValues, const std::string& filename);

}  // namespace peterson_r_min_in_cols_seq

#endif  // PETERSON_R_MIN_IN_COLS_SEQ_H
