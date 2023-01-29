/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "PowerShareService"

#include "PowerShare.h"
#include <hidl/HidlTransportSupport.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace powershare {
namespace V1_0 {
namespace implementation {

static const char *wireless_tx_enable_path = "/proc/wireless/enable_tx";

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

Return<bool> PowerShare::isEnabled() {
    const auto value = get<std::string>(wireless_tx_enable_path, "0");
    return !(value == "disable" || value == "0");
}

Return<bool> PowerShare::setEnabled(bool enable) {
    set(wireless_tx_enable_path, enable ? 1 : 0);

    return isEnabled();
}

Return<uint32_t> PowerShare::getMinBattery() {
    return 0;
}

Return<uint32_t> PowerShare::setMinBattery(uint32_t) {
    return getMinBattery();
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace powershare
}  // namespace lineage
}  // namespace vendor
