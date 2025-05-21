#include "round_button.h"
#include <stdio.h>

LV_IMG_DECLARE(img_warning)

static void cb_shutdown(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
}

static void cb_cancel_shutdown(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
}

lv_obj_t* create_page_shutdown_restart(lv_obj_t* parent) {
    lv_obj_t* page = lv_obj_create(parent);

    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(page, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = create_center_cond(page);

    lv_obj_t* img = lv_img_create(cond);
    lv_img_set_src(img, &img_warning);

    lv_obj_t* lbl_hint2 = lv_label_create(cond);
    lv_label_set_text(lbl_hint2, "关机将终止或暂停正在进行中的任务");
    lv_obj_set_style_text_font(lbl_hint2, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_hint2, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_hint2, LV_OPA_100, LV_PART_MAIN);
    lv_obj_set_width(lbl_hint2, 200);
    lv_label_set_long_mode(lbl_hint2, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_bg_color(lbl_hint2, lv_color_make(0, 255, 0), 0);

    lv_obj_t* spaceobj = lv_obj_create(cond);
    lv_obj_set_size(spaceobj, 1, 60);
    lv_obj_set_style_bg_opa(spaceobj, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(spaceobj, 0, 0);

    create_button(cond, 210, 72, cb_shutdown, "关机", 0, 0, lv_color_white(), 51, 30, lv_color_white(), LV_OPA_100, 0);
    create_button(cond, 210, 72, cb_cancel_shutdown, "取消", 0, 0, lv_color_white(), 51, 30, lv_color_white(), LV_OPA_100, 0);

    lv_obj_center(cond);

    return page;
}
