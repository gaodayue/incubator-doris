// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <map>
#include <memory>

#include "util/metrics.h"

namespace doris {

class CpuMetrics;
class MemoryMetrics;
class DiskMetrics;
class NetMetrics;
class FileDescriptorMetrics;

class SystemMetrics {
public:
    SystemMetrics();
    ~SystemMetrics();

    // install system metrics to registry
    void install(MetricRegistry* registry, const std::set<std::string>& disk_devices,
                 const std::vector<std::string>& network_interfaces);

    // update metrics
    void update();

    void get_disks_io_time(std::map<std::string, int64_t>* map);
    int64_t get_max_io_util(const std::map<std::string, int64_t>& lst_value, int64_t interval_sec);

    void get_network_traffic(std::map<std::string, int64_t>* send_map,
                             std::map<std::string, int64_t>* rcv_map);
    void get_max_net_traffic(const std::map<std::string, int64_t>& lst_send_map,
                             const std::map<std::string, int64_t>& lst_rcv_map,
                             int64_t interval_sec, int64_t* send_rate, int64_t* rcv_rate);

private:
    void _install_cpu_metrics(MetricRegistry*);
    // On Intel(R) Xeon(R) CPU E5-2450 0 @ 2.10GHz;
    // read /proc/stat would cost about 170us
    void _update_cpu_metrics();

    void _install_memory_metrics(MetricRegistry* registry);
    void _update_memory_metrics();

    void _install_disk_metrics(MetricRegistry* registry, const std::set<std::string>& devices);
    void _update_disk_metrics();

    void _install_net_metrics(MetricRegistry* registry, const std::vector<std::string>& interfaces);
    void _update_net_metrics();

    void _install_fd_metrics(MetricRegistry* registry);

    void _update_fd_metrics();

private:
    static const char* _s_hook_name;

    std::unique_ptr<CpuMetrics> _cpu_total;
    std::unique_ptr<MemoryMetrics> _memory_metrics;
    std::map<std::string, DiskMetrics*> _disk_metrics;
    std::map<std::string, NetMetrics*> _net_metrics;
    std::unique_ptr<FileDescriptorMetrics> _fd_metrics;
    int _proc_net_dev_version = 0;

    char* _line_ptr = nullptr;
    size_t _line_buf_size = 0;
    MetricRegistry* _registry = nullptr;
};

} // namespace doris
