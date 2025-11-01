#pragma once

#include "shkryleva_s_vec_min_val/common/include/common.hpp"
#include "task/include/task.hpp"

namespace shkryleva_s_vec_min_val {

class ShkrylevaSVecMinValSEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  explicit ShkrylevaSVecMinValSEQ(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace shkryleva_s_vec_min_val
