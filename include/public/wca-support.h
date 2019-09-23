// Copyright (c) 2015-2019 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef WEBOS_CONNMAN_ADAPTER_SUPPORT_H_
#define WEBOS_CONNMAN_ADAPTER_SUPPORT_H_

#include <stdbool.h>
#include <pbnjson.h>
#include <luna-service2/lunaservice.h>

/**
 * @brief Basic callback function
 */
typedef void (*wca_support_callback)(bool success, void *user_data);

/**
 * @brief Callback function for services changes
 *
 *        At Start this function is called with all services currently known
 * @param services_added : Services added
 * @param services_removed : Services removed (Maybe NULL)
 */
typedef void (*wca_support_services_changed_callback_t)(const GVariant *services_added, const gchar **services_removed);

/**
 * @brief Callback function for service property changes
 *
 * @param path : The service path
 * @param value : The property
 * @param value : The value
 */
typedef void (*wca_support_service_property_changed_callback_t)(const gchar *path, const gchar *property, const GVariant *value);

/**
 * @brief Callback function for saved services changes
 *
 *        At Start this function is called with all saved services currently known
 * @param services_added : Services added
 * @param services_removed : Services removed (Maybe NULL)
 */
typedef void (*wca_support_saved_services_changed_callback_t)(const GVariant *saved_services_added, const gchar **saved_services_removed);

/**
 * @brief Callback function for property changes
 *
 *        At Start this function is called for all known properties
 * @param property : The Property
 * @param value : The value
 */
typedef void (*wca_support_manager_property_changed_callback_t)(const gchar * property, const GVariant *value);

/**
 * @brief Callback function for technologies added
 *
 *        At Start this function is called for all known technologies
 * @param path : The technoligies path
 * @param value : The value
 */
typedef void (*wca_support_technology_added_callback_t)(const gchar *path, const GVariant *value);

/**
 * @brief Callback function for technologies removed
 *
 * @param path : The technoligies path
 */
typedef void (*wca_support_technology_removed_callback_t)(const gchar *path);

/**
 * @brief Callback function for technologies property change
 *
 * @param path : The technoligies path
 * @param value : The property
 * @param value : The value
 */
typedef void (*wca_support_technology_property_changed_callback_t)(const gchar *path, const gchar *property, const GVariant *value);

/**
 * @brief Callback function for groups added
 *
 *        At Start this function is called for all known goups
 * @param path : The groups path
 * @param value : The value
 */
typedef void (*wca_support_group_added_callback_t)(const gchar *path, const GVariant *value);

/**
 * @brief Callback function for groups removed
 *
 * @param path : The groups path
 */
typedef void (*wca_support_group_removed_callback_t)(const gchar *path);

/**
 * @brief Callback function for group property changes
 *
 * @param path : The groups path
 * @param value : The property
 * @param value : The value
 */
typedef void (*wca_support_group_property_changed_callback_t)(const gchar *path, const gchar *property, const GVariant *value);

/**
 * @brief Callback function for group property changes
 *
 * @param sh : The luna service handle
 * @param message : The luna service message
 */
typedef void (*wca_support_get_user_status_called_callback_t)(LSHandle* sh, LSMessage *message);

/**
 * @brief Struct with different callbacks
 */
typedef struct {
	wca_support_services_changed_callback_t services_changed;
	wca_support_service_property_changed_callback_t service_property_changed;
	wca_support_saved_services_changed_callback_t saved_services_changed;
	wca_support_manager_property_changed_callback_t manager_property_changed;
	wca_support_technology_added_callback_t technology_added;
	wca_support_technology_removed_callback_t technology_removed;
	wca_support_technology_property_changed_callback_t technology_property_changed;
	wca_support_group_added_callback_t group_added;
	wca_support_group_removed_callback_t group_removed;
	wca_support_group_property_changed_callback_t group_property_changed;
} wca_support_connman_update_callbacks;

/**
 * @brief Initialize the support backend. When the implementation is done with
 *        initialization or failed the provided callback is called.
 *
 *        If the passed version number of the API doesn't match the one
 *        which the library has been implemented for the initialization
 *        will fail.
 * @param ls_wifi_handle : LS2 handle for com.webos.service.wifi
 * @param ls_cm_handle : LS2 handle for com.webos.service.connectionmanager
 * @param wca_callbacks : Callbacks that provide information about different
 *                        network properties
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 */
int wca_support_init(LSHandle *ls_wifi_handle, LSHandle *ls_cm_handle,
		wca_support_connman_update_callbacks *wca_callbacks,
		wca_support_callback callback, void *user_data);

/**
 * @brief Release all resources used for the support backend.
 */
void wca_support_release(void);

/**
 * @brief Enable WiFi tethering support.
 *
 *        Perform all steps depending on the target platform to enable WiFi tethering.
 *
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 * @return 0, if call was successful, negative value indicating the error (see errno.h)
 *         otherwise.
 */
int wca_support_wifi_enable_tethering(wca_support_callback callback, void *user_data);

/**
 * @brief Disable WiFi tethering support.
 *
 *        Perform all steps depending on the target platform to disable WiFi tethering.
 *
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 * @return 0, if call was successful, negative value indicating the error (see errno.h)
 *         otherwise.
 */
int wca_support_wifi_disable_tethering(wca_support_callback callback, void *user_data);

/**
 * @brief Configure WiFi country code.
 *
 *        Perform all steps depending on the target platform to setup country code
 *
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 * @return 0, if call was successful, negative value indicating the error (see errno.h)
 *         otherwise.
 */
int wca_support_wifi_configure_country_code(wca_support_callback callback, void *user_data);

/**
 * @brief Enable wol/wowl status.
 *
 *        Perform all steps depending on the target platform to enable wol/wowl status
 *
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 * @return 0, if call was successful, negative value indicating the error (see errno.h)
 *         otherwise.
 */
int wca_support_enable_wol_status(wca_support_callback callback, void *user_data);

/**
 * @brief Disable wol/wowl status.
 *
 *        Perform all steps depending on the target platform to disable wol/wowl status
 *
 * @param callback Callback which is called when the operation is done or
 *                 has failed.
 * @param user_data User data which is handed over when the callback is called.
 * @return 0, if call was successful, negative value indicating the error (see errno.h)
 *         otherwise.
 */
int wca_support_disable_wol_status(wca_support_callback callback, void *user_data);

#endif
