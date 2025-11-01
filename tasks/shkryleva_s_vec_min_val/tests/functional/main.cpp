#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "shkryleva_s_vec_min_val/common/include/common.hpp"
#include "shkryleva_s_vec_min_val/mpi/include/ops_mpi.hpp"
#include "shkryleva_s_vec_min_val/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace shkryleva_s_vec_min_val {

class ShkrylevaRunFuncTestsProcesses : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  static std::string PrintTestParam(const TestType &test_param) {
    return std::to_string(std::get<0>(test_param)) + "_" + std::get<1>(test_param);
  }

 protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    int test_case = std::get<0>(params);

    switch (test_case) {
      case 0:
        input_data_ = {5, 3, 8, 1, 9};
        expected_output_ = 1;
        break;
      case 1:
        input_data_ = {-2, 0, 5, -8, 3};
        expected_output_ = -8;
        break;
      case 2:
        input_data_ = {42};
        expected_output_ = 42;
        break;
      case 3:
        input_data_ = {7, 7, 7, 7, 7};
        expected_output_ = 7;
        break;
      case 4:
        input_data_ = {1000, -1000, 500, -500, 0};
        expected_output_ = -1000;
        break;
      default:
        input_data_ = {1, 2, 3};
        expected_output_ = 1;
        break;
    }
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return (expected_output_ == output_data);
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_;
  OutType expected_output_;
};

namespace {

TEST_P(ShkrylevaRunFuncTestsProcesses, FindMinValue) {
  ExecuteTest(GetParam());
}

const std::array<TestType, 5> kTestParam = {std::make_tuple(0, "small_vector"), std::make_tuple(1, "negative_vector"),
                                            std::make_tuple(2, "single_element"), std::make_tuple(3, "all_equal"),
                                            std::make_tuple(4, "large_values")};

const auto kTestTasksList = std::tuple_cat(
    ppc::util::AddFuncTask<ShkrylevaSVecMinValMPI, InType>(kTestParam, PPC_SETTINGS_shkryleva_s_vec_min_val),
    ppc::util::AddFuncTask<ShkrylevaSVecMinValSEQ, InType>(kTestParam, PPC_SETTINGS_shkryleva_s_vec_min_val));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

const auto kPerfTestName = ShkrylevaRunFuncTestsProcesses::PrintFuncTestName<ShkrylevaRunFuncTestsProcesses>;

INSTANTIATE_TEST_SUITE_P(VectorMinTests, ShkrylevaRunFuncTestsProcesses, kGtestValues, kPerfTestName);

}  // namespace

}  // namespace shkryleva_s_vec_min_val
