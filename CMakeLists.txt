# Copyright (c) 2015-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 2.8.7)

project(wca-support-api C)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC9)
webos_component(1 0 0)

include(FindPkgConfig)
include_directories(include/public)

install(DIRECTORY "include/public/" DESTINATION @WEBOS_INSTALL_INCLUDEDIR@ FILES_MATCHING PATTERN "*.h" PATTERN ".*" EXCLUDE)
webos_build_pkgconfig(files/pkgconfig/wca-support-api)

webos_config_build_doxygen(doc Doxyfile)
