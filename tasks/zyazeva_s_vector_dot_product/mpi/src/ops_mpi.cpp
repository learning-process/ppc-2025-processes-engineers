#include "zyazeva_s_vector_dot_product/mpi/include/ops_mpi.hpp"

#include <mpi.h>

#include <numeric>
#include <vector>

#include "task/include/task.hpp"
#include "/workspaces/ppc-2025-processes-engineers-1/tasks/zyazeva_s_vector_dot_product/common/include/common.hpp"

namespace zyazeva_s_scalar_product_of_vectors {

ZyazevaSTestTaskMPI::ZyazevaSTestTaskMPI(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool ZyazevaSTestTaskMPI::ValidationImpl() {
  return (GetInput() > 0) && (GetOutput() == 0);
}

bool ZyazevaSTestTaskMPI::PreProcessingImpl() {
  int vector_size = GetInput();
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank == 0) {
    std::vector<int> vec1 = generateRandomVector(vector_size);
    std::vector<int> vec2 = generateRandomVector(vector_size);
    std::vector<int> vec3 = generateRandomVector(vector_size);
    input_ = {vec1, vec2};
  }
  
  return true;
}

bool ZyazevaSTestTaskMPI::RunImpl() {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  int vector_size = GetInput();
  
  MPI_Bcast(&vector_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

  int chunk_size = vector_size / size;
  int remainder = vector_size % size;
  
  // Вычисляем смещения и размеры для каждого процесса
  std::vector<int> sendcounts(size);
  std::vector<int> displs(size);
  
  int offset = 0;
  for (int i = 0; i < size; ++i) {
    sendcounts[i] = chunk_size + (i < remainder ? 1 : 0);
    displs[i] = offset;
    offset += sendcounts[i];
  }
  
  int local_size = sendcounts[rank];
  std::vector<int> local_vec1(local_size);
  std::vector<int> local_vec2(local_size);
  
  // Распределяем данные по процессам
  if (rank == 0) {
    // Процесс 0 разбивает и рассылает данные
    std::vector<int> scatter_counts1(size);
    std::vector<int> scatter_displs1(size);
    std::vector<int> scatter_counts2(size);
    std::vector<int> scatter_displs2(size);
    
    for (int i = 0; i < size; ++i) {
      scatter_counts1[i] = sendcounts[i];
      scatter_displs1[i] = displs[i];
      scatter_counts2[i] = sendcounts[i];
      scatter_displs2[i] = displs[i];
    }
    
    // Рассылаем части векторов
    MPI_Scatterv(input_[0].data(), scatter_counts1.data(), scatter_displs1.data(), MPI_INT,
                 local_vec1.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(input_[1].data(), scatter_counts2.data(), scatter_displs2.data(), MPI_INT,
                 local_vec2.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    // Остальные процессы получают свои части
    MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT,
                 local_vec1.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT,
                 local_vec2.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);
  }
  
  // Вычисляем локальное скалярное произведение
  int local_dot_product = 0;
  for (int i = 0; i < local_size; ++i) {
    local_dot_product += local_vec1[i] * local_vec2[i];
  }
  
  // Собираем результаты со всех процессов
  int global_dot_product = 0;
  MPI_Reduce(&local_dot_product, &global_dot_product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  // Сохраняем результат на процессе 0
  if (rank == 0) {
    res = global_dot_product;
  }
  
  return true;
}

bool ZyazevaSTestTaskMPI::PostProcessingImpl() {
  // Только процесс 0 записывает результат
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank == 0) {
    GetOutput() = res;
  }
  
  return true;
}

}  // namespace zyazeva_s_scalar_product_of_vectors
