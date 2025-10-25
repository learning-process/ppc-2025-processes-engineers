#pragma once

#include "zyazeva_s_vector_dot_product/common/include/common.hpp"
#include "task/include/task.hpp"

namespace zyazeva_s_vector_dot_product {

class NesterovATestTaskMPI : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit NesterovATestTaskMPI(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace zyazeva_s_vector_dot_product
