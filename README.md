<h1 align="center">yacaratia</h1>
<p align="center"><i>Edible logs</i></p>
<hr><p align="center">
  <img alt="Stars" src="https://img.shields.io/github/stars/buffet/yacaratia.svg?label=Stars&style=flat" />
  <a href="https://github.com/buffet/yacaratia/issues"><img alt="GitHub issues" src="https://img.shields.io/github/issues/buffet/yacaratia.svg"/></a>
  <a href="https://github.com/buffet/yacaratia/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/buffet/yacaratia"></a>
</p>

yacaratia is a simple and small logging library for my needs.


## Getting Started

Just drop the files and a license notice into your project.


## Usage

There are 4 different verbosities.

- `YA_LDEBUG`
- `YA_LINFO`
- `YA_LWARN`
- `YA_LERROR`

Use `ya_init(level, callback)` to initialize yacaratia.
You can pass `NULL` as `callback` for the default logger.
`ya_file(file)` can be used to change the location the log gets saved to (default is `stderr`).
`ya_set_verbosity` and `ya_get_verbosity` can be used to change the verbosity during runtime.
`ya_log(level, fmt, ...)` can be used to log stuff, even though its recommended to use the macros.
These exist in pairs and are called `YA_ERROR/YA_LOGE`, `YA_WARN/YA_LOGW`, etc.
By defining `YA_LOG_VERBOSITY` to a number between 0 and 3, you can disable some of these at compile time.
By defining it to `-1`, you can disable all logging.
