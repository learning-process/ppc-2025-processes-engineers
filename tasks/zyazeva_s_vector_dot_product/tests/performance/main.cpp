#include <gtest/gtest.h>

#include "zyazeva_s_vector_dot_product/common/include/common.hpp"
#include "zyazeva_s_vector_dot_product/mpi/include/ops_mpi.hpp"
#include "zyazeva_s_vector_dot_product/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace zyazeva_s_vector_dot_product {

class ExampleRunPerfTestProcesses : public ppc::util::BaseRunPerfTests<InType, OutType> {
  const int kCount_ = 100;
  InType input_data_{};

  void SetUp() override {
    input_data_ = kCount_;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return input_data_ == output_data;
  }

  InType GetTestInputData() final {
    return input_data_;
  }
};

TEST_P(ExampleRunPerfTestProcesses, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, ZyazevaSVecDotProduct, ZyazevaSVecDotProductSEQ>(PPC_SETTINGS_zyazeva_s_vector_dot_product);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

const auto kPerfTestName = ExampleRunPerfTestProcesses::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, ExampleRunPerfTestProcesses, kGtestValues, kPerfTestName);

}  // namespace zyazeva_s_vector_dot_product
