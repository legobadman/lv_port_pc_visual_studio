#include "round_button.h"
#include <stdio.h>


LV_IMG_DECLARE(img_shutdown);
LV_IMG_DECLARE(img_restart);

static void callback_aod(lv_event_t* e)
{
    //息屏
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
    }
    else if (code == LV_EVENT_VALUE_CHANGED) {
    }
}

static void callback_wallpaper(lv_event_t* e)
{
    //息屏
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
    }
}

static void callback_restart(lv_event_t* e)
{
    //息屏
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
    }
}

static void callback_shutdown(lv_event_t* e)
{
    //息屏
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
    }
}


lv_obj_t* create_page_control_center(lv_obj_t* parent) {

    lv_obj_t* background = lv_obj_create(parent);

    lv_obj_set_size(background, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(background, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = create_center_cond(background);

    create_brightness_slider(cond);
    create_button(cond, 234, 88, callback_aod, "息屏", 0, "2 分钟", lv_color_white(), LV_OPA_20, 31, lv_color_white(), 217, 145);
    create_button(cond, 234, 72, callback_wallpaper, "壁纸", 0, 0, lv_color_white(), 51, 30, lv_color_white(), 216, 0);
    create_button(cond, 234, 72, callback_restart, "重启", &img_restart, "", lv_color_make(4, 222, 113), LV_OPA_30, LV_OPA_20, lv_color_make(4, 222, 113), LV_OPA_100, 0);
    create_button(cond, 234, 72, callback_shutdown, "关机", &img_shutdown, "", lv_color_hex(0xFF3B30), LV_OPA_30, LV_OPA_20, lv_color_hex(0xFF0000), LV_OPA_100, 0);

    lv_obj_center(cond);

    return background;
}
