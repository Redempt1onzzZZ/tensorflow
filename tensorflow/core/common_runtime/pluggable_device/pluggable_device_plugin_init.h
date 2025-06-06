/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_COMMON_RUNTIME_PLUGGABLE_DEVICE_PLUGGABLE_DEVICE_PLUGIN_INIT_H_
#define TENSORFLOW_CORE_COMMON_RUNTIME_PLUGGABLE_DEVICE_PLUGGABLE_DEVICE_PLUGIN_INIT_H_

#include "tensorflow/core/platform/status.h"

// Forward declarations to avoid dependency.
struct PJRT_Api;
struct SE_PlatformRegistrationParams;
struct TFNPD_Api;
struct TFNPD_PluginParams;
struct TF_ProfilerRegistrationParams;
struct TP_OptimizerRegistrationParams;
struct TSL_Status;

namespace stream_executor {
using SEInitPluginFn = void (*)(SE_PlatformRegistrationParams* const,
                                TSL_Status* const);
}  // namespace stream_executor

namespace tensorflow {

namespace grappler {
using TFInitGraphPluginFn = void (*)(TP_OptimizerRegistrationParams* const,
                                     TSL_Status* const);
}  // namespace grappler

namespace profiler {
using TFInitProfilerFn = void (*)(TF_ProfilerRegistrationParams* const,
                                  TSL_Status* const);
}  // namespace profiler

using PjrtApiInitFn = const PJRT_Api* (*)();
using TFKernelInitFn = void (*)();
using TFNPDInitPluginFn = const TFNPD_Api* (*)(TFNPD_PluginParams*,
                                               TSL_Status*);

struct PluggableDeviceInit_Api {
  ::stream_executor::SEInitPluginFn init_plugin_fn = nullptr;
  TFNPDInitPluginFn init_np_plugin_fn = nullptr;
  PjrtApiInitFn get_pjrt_api_fn = nullptr;
  TFKernelInitFn init_kernel_fn = nullptr;
  grappler::TFInitGraphPluginFn init_graph_fn = nullptr;
  profiler::TFInitProfilerFn init_profiler_fn = nullptr;
};

absl::Status RegisterPluggableDevicePlugin(void* dso_handle);
absl::Status RegisterPluggableDevicePlugin(const PluggableDeviceInit_Api* api);

}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_COMMON_RUNTIME_PLUGGABLE_DEVICE_PLUGGABLE_DEVICE_PLUGIN_INIT_H_
