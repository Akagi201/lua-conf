/*
 * @file conf.h
 * @author Akagi201
 * @date 2014/12/09
 */

#ifndef CONF_H_
#define CONF_H_ (1)

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define MAX_LUA_EXPR (256)

int conf_init(const char *filename);

int conf_get_string(const char *expr, const char **out);

int conf_get_double(const char *expr, double *out);

int conf_get_int(const char *expr, int *out);

int conf_get_bool(const char *expr, int *out);

void conf_free(void);

#endif // CONF_H_
