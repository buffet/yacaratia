/* Copyright (c), Niclas Meyer <niclas@countingsort.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "ya.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>

static void log_message(enum ya_log_verbosity verb, const char *fmt, va_list args);

static enum ya_log_verbosity min_verb = YA_LWARN;
static ya_log_func_t log_callback = log_message;
static FILE *output;

static const char *verbosity_colors[] = {
    [YA_LERROR] = "\x1b[1;31m",
    [YA_LWARN]  = "\x1b[1;33m",
    [YA_LINFO]  = "\x1b[1;34m",
    [YA_LDEBUG] = "\x1b[1;30m",
};

static void
log_message(enum ya_log_verbosity verb, const char *fmt, va_list args)
{
    // time prefix
    struct tm result;
    time_t t = time(NULL);
    struct tm *tm_info = localtime_r(&t, &result);
    char buffer[23];
    strftime(buffer, sizeof(buffer), "%F %T", tm_info);

    // colors
    const char *color_prefix  = "";
    const char *color_postfix = "";
    if (isatty(fileno(output))) {
        size_t c = (verb < YA_LVERBOSITY_LAST) ? verb : YA_LVERBOSITY_LAST - 1;
        color_prefix  = verbosity_colors[c];
        color_postfix = "\x1b[0m";
    }

#ifdef _POSIX_THREAD_SAFE_FUNCTIONS
    flockfile(output);
    fprintf(output, "%s - %s", buffer, color_prefix);
    vfprintf(output, fmt, args);
    fprintf(output, "%s\n", color_postfix);
    funlockfile(output);
#else
    fprintf(output, "%s - %s", buffer, color_prefix);
    vfprintf(output, fmt, args);
    fprintf(output, "%s\n", color_postfix);
#endif
}

void
ya_init(enum ya_log_verbosity verb, ya_log_func_t callback)
{
    output = stderr;
    min_verb = verb;

    if (callback) {
        log_callback = callback;
    }
}

void
ya_set_verbosity(enum ya_log_verbosity verb)
{
    min_verb = (verb < YA_LVERBOSITY_LAST) ? verb : YA_LVERBOSITY_LAST - 1;
}

enum ya_log_verbosity
ya_get_verbosity(void)
{
    return min_verb;
};
 
void
_ya_log(enum ya_log_verbosity verb, const char *fmt, ...)
{
    if (verb > min_verb) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    log_callback(verb, fmt, args);
    va_end(args);
}

void
ya_file(FILE *file)
{
    output = file;
}
