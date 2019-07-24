#ifndef ONEFLOW_CORE_GRAPH_CUDA_RING_ALL_REDUCE_TASK_NODE_H_
#define ONEFLOW_CORE_GRAPH_CUDA_RING_ALL_REDUCE_TASK_NODE_H_

#include "oneflow/core/graph/task_node.h"

namespace oneflow {

class CudaRingAllReduceTaskNode final : public TaskNode {
 public:
  OF_DISALLOW_COPY_AND_MOVE(CudaRingAllReduceTaskNode);
  CudaRingAllReduceTaskNode() = default;
  ~CudaRingAllReduceTaskNode() override = default;

  void Init(int64_t machine_id, int64_t thrd_id, const LogicalBlobId& lbi,
            const Shape& logical_blob_shape, const ParallelContext& parallel_ctx);
  void ProduceAllRegstsAndBindEdges() override;
  void ConsumeAllRegsts() override;
  TaskType GetTaskType() const override { return TaskType::kCudaRingAllReduce; }
  void AddRing(const std::vector<int64_t>& ring_next, TaskNode* send_to, TaskNode* recv_from);

 private:
  bool IsReadyForBuild() override;
  void BuildExecGphAndRegst() override;
  void InferProducedDataRegstTimeShape() override;
  OperatorConf GenOpConf() const;
  const ParallelContext* parallel_ctx() const override { return &parallel_ctx_; }
  void ToProto(TaskProto*) override;
  void PinConsumedRegstMemCase(MemoryCase*) override;

  LogicalBlobId lbi_;
  ParallelContext parallel_ctx_;
  std::vector<std::vector<int64_t>> rings_;
  std::vector<TaskNode*> send_to_;
  std::vector<TaskNode*> recv_from_;
  Shape logical_blob_shape_;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_GRAPH_CUDA_RING_ALL_REDUCE_TASK_NODE_H_
