/* Copyright (c), Niclas Meyer <niclas@countingsort.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef YA_H
#define YA_H

#include <stdarg.h>
#include <stdio.h>

#define ya_log(verb, fmt, ...) \
    _ya_log(verb, "[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#ifndef YA_LOG_VERBOSITY
#define YA_LOG_VERBOSITY 3
#endif /* YA_LOG_VERBOSITY */

#if YA_LOG_VERBOSITY > -1
#define YA_ERROR(fmt, ...) ya_log(YA_LERROR, fmt, ##__VA_ARGS__)
#define YA_LOGE(fmt, ...) ya_log(YA_LERROR, fmt, ##__VA_ARGS__)
#else
#define YA_ERROR(...)
#define YA_LOGE(...)
#endif /* YA_LOG_VERBOSITY > -1 */

#if YA_LOG_VERBOSITY > 0
#define YA_WARN(fmt, ...) ya_log(YA_LWARN, fmt, ##__VA_ARGS__)
#define YA_LOGW(fmt, ...) ya_log(YA_LWARN, fmt, ##__VA_ARGS__)
#else
#define YA_WARN(...)
#define YA_LOGW(...)
#endif /* YA_LOG_VERBOSITY > 0 */

#if YA_LOG_VERBOSITY > 1
#define YA_INFO(fmt, ...) ya_log(YA_LINFO, fmt, ##__VA_ARGS__)
#define YA_LOGI(fmt, ...) ya_log(YA_LINFO, fmt, ##__VA_ARGS__)
#else
#define YA_INFO(...)
#define YA_LOGI(...)
#endif /* YA_LOG_VERBOSITY > 1 */

#if YA_LOG_VERBOSITY > 2
#define YA_DEBUG(fmt, ...) ya_log(YA_LDEBUG, fmt, ##__VA_ARGS__)
#define YA_LOGD(fmt, ...) ya_log(YA_LDEBUG, fmt, ##__VA_ARGS__)
#else
#define YA_DEBUG(...)
#define YA_LOGD(...)
#endif /* YA_LOG_VERBOSITY > 2 */

enum ya_log_verbosity {
    YA_LERROR = 0,
    YA_LWARN = 1,
    YA_LINFO = 2,
    YA_LDEBUG = 3,
    YA_LVERBOSITY_LAST,
};

typedef void (*ya_log_func_t)(enum ya_log_verbosity verb, const char *fmt, va_list args);

void ya_init(enum ya_log_verbosity verb, ya_log_func_t callback);
void ya_set_verbosity(enum ya_log_verbosity verb);
enum ya_log_verbosity ya_get_verbosity(void);
void _ya_log(enum ya_log_verbosity verb, const char *format, ...);
void ya_file(FILE *file);

#endif /* YA_H */
