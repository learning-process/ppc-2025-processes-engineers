#include "task/include/task.hpp"
#pragma once

#include <string>
#include <vector>

#include "tasks/zyazeva_s_vector_dot_product/common/include/common.hpp"

namespace zyazeva_s_scalar_product_of_vectors {

class ZyazevaSTestTaskMPI : public BaseTask {
  std::vector<int> generateRandomVector(int v_size);
  int calculateDotProduct(const std::vector<int>& vec_1, const std::vector<int>& vec_2);
  
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit ZyazevaSTestTaskMPI(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
  std::vector<std::vector<int>> input_;
  int res{};
};

}  // namespace zyazeva_s_scalar_product_of_vectors

