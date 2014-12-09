/*
 * @file conf.c
 * @author Akagi201
 * @date 2014/12/09
 */

#include "conf.h"
#include <errno.h>

static lua_State *L;

/*
 * @brief init a lua config file
 * @return -1: failed / 0: success
 */
int conf_init(const char *filename) {

    if (!L || !filename){
        return EINVAL;
    }

    // Init lua state
    L = luaL_newstate();
    if (NULL == L) {
        printf("luaL_newstate failed.\n");
        return -1;
    }

    // Open lua standard libs
    luaL_openlibs(L);

    // Load and run script
    if (luaL_dofile(L, filename)) {
        printf("luaL_dofile failed: %s.\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return -1;
    }

    return 0;
}

/*
 * @brief Evaluates a Lua expression and returns the string result.
 * @return errno: error / 0: success
 */
int conf_get_string(const char *expr, const char *out){
    int ret = 0;
    char buf[MAX_LUA_EXPR] = {0};

    if (!L || !expr){
        return EINVAL;
    }

    // Assign the Lua expression to a Lua global variale.
    snprintf(buf, sizeof(buf), "expr=%s", expr);
    if (!luaL_dostring(L, buf)) {
        // Get the value of the global variable
        lua_getglobal(L, "expr");
        if (lua_isstring(L, -1)) {
            out = lua_tostring(L, -1);
            ret = 0;
        }

        // remove lua_getglobal value
        lua_pop(L, 1);
    } else {
        printf("luaL_dostring failed.\n");
        ret = -1;
    }
    return ret;

}

/*
 * @brief Evaluates a Lua expression that results in a number
 * The number is stored in out.
 * @return -1: error / 0: success
 */
int conf_get_double(const char *expr, double *out) {
    int ret = -1;
    char buf[MAX_LUA_EXPR] = {0};

    if (!L || !expr || !out){
        return EINVAL;
    }

    /* Assign the Lua expression to a Lua global variable. */
    snprintf(buf, sizeof(buf), "expr=%s", expr);
    if (!luaL_dostring(L, buf)) {
        /* Get the value of the global varibable */
        lua_getglobal(L, "expr");
        if (lua_isnumber(L, -1)) {
            *out = lua_tonumber(<#L#>, -1);
            ret = 0;
        }

        // remove lua_getglobal value
        lua_pop(L, 1);
    } else {
        printf("luaL_dostring failed.\n");
        ret = -1;
    }

    return ret;
}

/*
 * @brief Evaluates a Lua expression that results in a number and cast to an int.
 * @return -1: error / 0: success
 */
int conf_get_int(const char *expr, int *out) {
    double d = 0;
    int ret = -1;

    if (!L || !expr || !out){
        return EINVAL;
    }

    ret = conf_get_double(L, expr, &d);
    if (0 == ret) {
        *out = (int)d;
    }

    return ret;
}

/*
 * @brief Evaluates a Lua expression that results in a number and cast to a bool.
 * @return -1: error / 0: success
 */
int conf_get_bool(const char *expr, int *out) {
    int ret = -1;
    char buf[MAX_LUA_EXPR] = {0};

    if (!L || !expr || !out){
        return EINVAL;
    }

    /* Assign the Lua expression to a Lua global variable. */
    snprintf(buf, sizeof(buf), "expr=%s", expr);

    if (!luaL_dostring(<#L#>, buf)) {
        /* Get the value of the global varibable */
        lua_getglobal(L, "expr");
        if (lua_isboolean(<#L#>, -1)) {
            *out = lua_toboolean(L, -1);
            ret = 0;
        }

        // remove lua_getglobal value
        lua_pop(L, 1);
    } else {
        printf("luaL_dostring failed.\n");
        ret = -1;
    }

    return ret;
}

/*
 * @brief release resources owned by config file
 */
void conf_free(void) {
    lua_close(L);

    return;
}