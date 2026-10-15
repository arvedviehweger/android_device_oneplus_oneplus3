/*
 * SPDX-FileCopyrightText: 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.oneplus3"

#include "KeyDisabler.h"
#include "KeySwapper.h"
#include "TouchscreenGesture.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::lineage::touch::KeyDisabler;
using aidl::vendor::lineage::touch::KeySwapper;
using aidl::vendor::lineage::touch::TouchscreenGesture;

template <typename T>
static void addService(const std::shared_ptr<T>& service) {
    const std::string instance = std::string(T::descriptor) + "/default";
    binder_status_t status = AServiceManager_addService(service->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << instance << " " << status;
}

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    addService(ndk::SharedRefBase::make<KeyDisabler>());
    addService(ndk::SharedRefBase::make<KeySwapper>());
    addService(ndk::SharedRefBase::make<TouchscreenGesture>());

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
