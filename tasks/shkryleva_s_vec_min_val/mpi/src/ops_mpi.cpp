#include "shkryleva_s_vec_min_val/mpi/include/ops_mpi.hpp"

#include <algorithm>
#include <climits>
#include <vector>

namespace shkryleva_s_vec_min_val {

ShkrylevaSVecMinValMPI::ShkrylevaSVecMinValMPI(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool ShkrylevaSVecMinValMPI::ValidationImpl() {
  return (!GetInput().empty()) && (GetOutput() == 0);
}

bool ShkrylevaSVecMinValMPI::PreProcessingImpl() {
  int initialized;
  MPI_Initialized(&initialized);
  if (!initialized) {
    MPI_Init(nullptr, nullptr);
  }

  GetOutput() = INT_MAX;
  return true;
}

bool ShkrylevaSVecMinValMPI::RunImpl() {
  if (GetInput().empty()) {
    return false;
  }

  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  const std::vector<int> *input_data_ptr = nullptr;
  size_t total_size = 0;

  if (world_rank == 0) {
    input_data_ptr = &GetInput();
    total_size = input_data_ptr->size();
  }

  MPI_Bcast(&total_size, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

  size_t base_local_size = total_size / world_size;
  size_t remainder = total_size % world_size;

  std::vector<int> sendcounts(world_size);
  std::vector<int> displacements(world_size);

  size_t offset = 0;
  for (int i = 0; i < world_size; ++i) {
    sendcounts[i] = base_local_size + (i < static_cast<int>(remainder) ? 1 : 0);
    displacements[i] = static_cast<int>(offset);
    offset += sendcounts[i];
  }

  std::vector<int> local_data(sendcounts[world_rank]);

  if (world_rank == 0) {
    MPI_Scatterv(input_data_ptr->data(), sendcounts.data(), displacements.data(), MPI_INT, local_data.data(),
                 sendcounts[world_rank], MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT, local_data.data(), sendcounts[world_rank], MPI_INT, 0,
                 MPI_COMM_WORLD);
  }

  int local_min = INT_MAX;
  for (int value : local_data) {
    if (value < local_min) {
      local_min = value;
    }
  }

  int global_min;
  MPI_Allreduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
  GetOutput() = global_min;

  return true;
}

bool ShkrylevaSVecMinValMPI::PostProcessingImpl() {
  int finalized;
  MPI_Finalized(&finalized);
  if (!finalized) {
    // MPI_Finalize();
  }
  return GetOutput() > INT_MIN;
}

}  // namespace shkryleva_s_vec_min_val
