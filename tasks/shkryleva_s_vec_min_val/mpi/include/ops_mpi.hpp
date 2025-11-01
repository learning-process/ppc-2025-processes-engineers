#pragma once

#include "shkryleva_s_vec_min_val/common/include/common.hpp"
#include "task/include/task.hpp"
#include <mpi.h>

namespace shkryleva_s_vec_min_val {

class ShkrylevaSVecMinValMPI : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit ShkrylevaSVecMinValMPI(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace shkryleva_s_vec_min_val