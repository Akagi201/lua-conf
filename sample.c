/*
 * @file sample.c
 * @author Akagi201
 * @date 2014/12/09
 */

#include <stdio.h>
#include <string.h>
#include "conf.h"

int main(void) {
    int width = 0;
    int height = 0;
    int fullscreen = 0;
    int image_count = 0;
    int i = 0;
    int ret = 0;
    char expr[64] = {0};
    const char *image;

    conf_init("config.lua");

    ret = conf_get_int("settings.resolution.width", &width);

    printf("ret: %d, width: %d\n", ret, width);

    ret = conf_get_int("settings.resolution.height", &height);

    printf("ret: %d, height: %d\n", ret, height);

    ret = conf_get_bool("settings.resolution.fullscreen", &fullscreen);

    printf("ret: %d, fullscreen: %d\n", ret, fullscreen);

    ret = conf_get_int("#settings.images", &image_count);

    printf("ret: %d, image_count: %d\n", ret, image_count);

    for (i = 0; i < image_count; ++i) {
        memset(expr, 0, sizeof(expr));
        snprintf(expr, sizeof(expr), "settings.images[%d]", i + 1);
        ret = conf_get_string(expr, image);
        printf("ret: %d, settings.images[%d] = %s\n", ret, i + 1, image);
    }
    conf_free();

    return 0;
}