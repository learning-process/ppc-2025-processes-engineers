#include "shkryleva_s_vec_min_val/seq/include/ops_seq.hpp"

#include <vector>
#include <climits>
#include <algorithm>

namespace shkryleva_s_vec_min_val {

ShkrylevaSVecMinValSEQ::ShkrylevaSVecMinValSEQ(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool ShkrylevaSVecMinValSEQ::ValidationImpl() {
  return (!GetInput().empty()) && (GetOutput() == 0);
}

bool ShkrylevaSVecMinValSEQ::PreProcessingImpl() {
  GetOutput() = INT_MAX;
  return true;
}

bool ShkrylevaSVecMinValSEQ::RunImpl() {
  if (GetInput().empty()) {
    return false;
  }
  int min_val = *std::min_element(GetInput().begin(), GetInput().end());
  GetOutput() = min_val;
  return true;
}

bool ShkrylevaSVecMinValSEQ::PostProcessingImpl() {
  return GetOutput() > INT_MIN;
}

}  // namespace shkryleva_s_vec_min_val