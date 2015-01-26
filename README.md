lua-conf
========

[![Build Status](https://travis-ci.org/Akagi201/lua-conf.svg)](https://travis-ci.org/Akagi201/lua-conf)

Use lua as config file

## Dependencies
* liblua.a

## Build

`./start_build.sh`

## API

* See `sample.c` and `src/conf.h`

```
int conf_init(const char *filename);

int conf_get_string(const char *expr, const char **out);

int conf_get_double(const char *expr, double *out);

int conf_get_int(const char *expr, int *out);

int conf_get_bool(const char *expr, int *out);

void conf_free(void);
```