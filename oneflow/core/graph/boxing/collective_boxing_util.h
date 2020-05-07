#ifndef ONEFLOW_CORE_JOB_COLLECTIVE_BOXING_UTIL_H_
#define ONEFLOW_CORE_JOB_COLLECTIVE_BOXING_UTIL_H_

#include "oneflow/core/common/util.h"
#include "oneflow/core/job/plan.pb.h"
#include "oneflow/core/operator/op_conf.pb.h"
#include "oneflow/core/common/protobuf.h"
#include "oneflow/core/graph/boxing/collective_boxing.pb.h"
#include "oneflow/core/common/shape.h"

namespace oneflow {

namespace boxing {

namespace collective {

inline bool operator==(const OpDesc& lhs, const OpDesc& rhs) { return PbMd::Equals(lhs, rhs); }

inline bool operator==(const DeviceDesc& lhs, const DeviceDesc& rhs) {
  return PbMd::Equals(lhs, rhs);
}

inline bool operator==(const DeviceSet& lhs, const DeviceSet& rhs) {
  return PbMd::Equals(lhs, rhs);
}

inline bool operator!=(const DeviceSet& lhs, const DeviceSet& rhs) { return !(lhs == rhs); }

bool GenericOpHasInput(const RankDesc& rank_desc);

bool GenericOpHasOutput(const RankDesc& rank_desc);

Shape GenericOpGetInputShape(const RankDesc& rank_desc);

Shape GenericOpGetOutputShape(const RankDesc& rank_desc);

}  // namespace collective

}  // namespace boxing

}  // namespace oneflow

namespace std {

template<>
struct hash<oneflow::boxing::collective::DeviceDesc> {
  size_t operator()(const oneflow::boxing::collective::DeviceDesc& device_desc) const {
    size_t hash = std::hash<int64_t>()(device_desc.machine_id());
    oneflow::HashCombine(hash, std::hash<int64_t>()(device_desc.device_type()));
    oneflow::HashCombine(hash, std::hash<int64_t>()(device_desc.device_id()));
    return hash;
  }
};

template<>
struct hash<oneflow::boxing::collective::DeviceSet> {
  size_t operator()(const oneflow::boxing::collective::DeviceSet& device_set) const {
    size_t hash = 0;
    for (const auto& device : device_set.device()) {
      oneflow::HashCombine(hash, std::hash<oneflow::boxing::collective::DeviceDesc>()(device));
    }
    return hash;
  }
};

}  // namespace std

#endif  // ONEFLOW_CORE_JOB_COLLECTIVE_BOXING_UTIL_H_
