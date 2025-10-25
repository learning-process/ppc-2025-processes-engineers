#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace zyazeva_s_scalar_product_of_vectors {

using InType = int;
using OutType = int;
using TestType = std::tuple<int, std::string>;
using BaseTask = ppc::task::Task<InType, OutType>;

// Объявления функций
std::vector<int> generateRandomVector(int v_size);
int generateRandomNumber(int min, int max);
int calculateDotProduct(const std::vector<int>& vec_1, const std::vector<int>& vec_2);

}  // namespace zyazeva_s_scalar_product_of_vectors
