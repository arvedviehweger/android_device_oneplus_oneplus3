/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include "KeySwapper.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

static constexpr const char* kControlPath = "/proc/s1302/key_rep";

ndk::ScopedAStatus KeySwapper::getEnabled(bool* _aidl_return) {
    std::string buf;
    if (!android::base::ReadFileToString(kControlPath, &buf)) {
        LOG(ERROR) << "Failed to read " << kControlPath;
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    *_aidl_return = std::stoi(android::base::Trim(buf)) == 1;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus KeySwapper::setEnabled(bool enabled) {
    if (!android::base::WriteStringToFile(std::to_string(enabled), kControlPath)) {
        LOG(ERROR) << "Failed to write " << kControlPath;
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
