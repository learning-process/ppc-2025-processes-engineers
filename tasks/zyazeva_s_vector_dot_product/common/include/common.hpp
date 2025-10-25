#pragma once

#include <string>
#include <tuple>

#include "task/include/task.hpp"

namespace zyazeva_s_vector_dot_product {

using InType = int;
using OutType = int;
using TestType = std::tuple<int, std::string>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace zyazeva_s_vector_dot_product
