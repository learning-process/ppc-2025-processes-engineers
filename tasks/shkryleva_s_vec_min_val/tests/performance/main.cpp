#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "shkryleva_s_vec_min_val/common/include/common.hpp"
#include "shkryleva_s_vec_min_val/mpi/include/ops_mpi.hpp"
#include "shkryleva_s_vec_min_val/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace shkryleva_s_vec_min_val {

class ShkrylevaSVecMinValPerfTests : public ppc::util::BaseRunPerfTests<InType, OutType> {
  const size_t kVectorSize_ = 100000000;
  InType input_data_{};
  OutType expected_min_{};

  void SetUp() override {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    input_data_.resize(kVectorSize_);
    for (size_t i = 0; i < kVectorSize_; i++) {
      input_data_[i] = dist(gen);
    }

    expected_min_ = -1500;
    input_data_[kVectorSize_ / 2] = expected_min_;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return expected_min_ == output_data;
  }

  InType GetTestInputData() final {
    return input_data_;
  }
};

TEST_P(ShkrylevaSVecMinValPerfTests, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks = ppc::util::MakeAllPerfTasks<InType, ShkrylevaSVecMinValMPI, ShkrylevaSVecMinValSEQ>(
    PPC_SETTINGS_shkryleva_s_vec_min_val);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

const auto kPerfTestName = ShkrylevaSVecMinValPerfTests::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, ShkrylevaSVecMinValPerfTests, kGtestValues, kPerfTestName);

}  // namespace shkryleva_s_vec_min_val
