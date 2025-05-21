#include "round_button.h"
#include <stdio.h>


static lv_obj_t* button_15s;
static lv_obj_t* button_30s;
static lv_obj_t* button_1min;
static lv_obj_t* button_2min;
static lv_obj_t* button_5min;

static void callback_15seconds(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        //lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
        lv_obj_clear_state(button_30s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_1min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_2min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_5min, LV_STATE_CHECKED);

        //do something here.
    }
}

static void callback_30seconds(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        //lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
        lv_obj_clear_state(button_15s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_1min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_2min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_5min, LV_STATE_CHECKED);
    }
}

static void callback_1minute(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        //lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
        lv_obj_clear_state(button_15s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_30s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_2min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_5min, LV_STATE_CHECKED);
    }
}

static void callback_2minute(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        //lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
        lv_obj_clear_state(button_15s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_30s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_1min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_5min, LV_STATE_CHECKED);
    }
}

static void callback_5minute(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        //lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
        lv_obj_clear_state(button_15s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_30s, LV_STATE_CHECKED);
        lv_obj_clear_state(button_1min, LV_STATE_CHECKED);
        lv_obj_clear_state(button_2min, LV_STATE_CHECKED);
    }
}

lv_obj_t* create_aod_settings(lv_obj_t* parent) {
    lv_obj_t* background = lv_obj_create(parent);

    lv_obj_set_size(background, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(background, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = create_center_cond(background);

    button_15s = create_checkable_button(cond, 234, 72, callback_15seconds, "15秒", lv_color_white(), LV_OPA_20, 31, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211);
    button_30s = create_checkable_button(cond, 234, 72, callback_30seconds, "30秒", lv_color_white(), LV_OPA_20, 31, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211);
    button_1min = create_checkable_button(cond, 234, 72, callback_1minute, "1 分钟", lv_color_white(), LV_OPA_20, 31, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211);
    button_2min = create_checkable_button(cond, 234, 72, callback_2minute, "2 分钟", lv_color_white(), LV_OPA_20, 31, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211);
    button_5min = create_checkable_button(cond, 234, 72, callback_5minute, "5 分钟", lv_color_white(), LV_OPA_20, 31, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211);

    lv_obj_add_state(button_1min, LV_STATE_CHECKED);

    lv_obj_center(cond);

    return background;
}
