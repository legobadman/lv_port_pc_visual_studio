#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"
#include <stdio.h>

LV_IMG_DECLARE(img_shutdown);
LV_IMG_DECLARE(img_restart);
LV_IMG_DECLARE(img_brightness);
LV_IMG_DECLARE(img_checked);

static void event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if (code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

lv_obj_t* create_column_layoutobj(lv_obj_t* parent) {
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(cond, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(cond, LV_OPA_TRANSP, 0);
    lv_obj_set_size(cond, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    return cond;
}

lv_obj_t* create_center_cond(lv_obj_t* parent) {
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(cond, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(cond, 0, LV_PART_MAIN);
    //lv_obj_set_style_bg_color(cond, lv_color_make(255,0,0), LV_PART_MAIN);   //Debug
    lv_obj_set_style_bg_opa(cond, LV_OPA_TRANSP, 0);
    lv_obj_set_style_radius(cond, 0, LV_PART_MAIN);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(cond, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    return cond;
}

lv_obj_t* create_ok_button(lv_obj_t* parent, lv_coord_t size, lv_event_cb_t cb)
{
    lv_obj_t* button = lv_btn_create(parent);
    lv_obj_remove_style_all(button);  // 彻底移除所有从主题继承的样式

    lv_obj_add_event_cb(button, cb, LV_EVENT_ALL, NULL);
    lv_obj_set_size(button, size, size);
    lv_obj_set_style_radius(button, 75, 0);
    lv_obj_set_style_bg_color(button, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(button, LV_OPA_20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(button, lv_color_white(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(button, LV_OPA_30, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t* iconobj = lv_img_create(button);
    lv_img_set_src(iconobj, &img_checked);
    lv_obj_center(iconobj);
    return button;
}

lv_obj_t* create_button(
    lv_obj_t* parent,
    lv_coord_t w,
    lv_coord_t h,
    lv_event_cb_t cb,
    const char* text,
    const lv_img_dsc_t* icon, //图标，如果没有就填0
    const char* under_text,  //文本下方的小提示文本，如没有就填0
    /* 基础按钮的背景色，以及normal和clicked状态下的alpha值*/
    lv_color_t bgclr,
    lv_opa_t alpha_normal,
    lv_opa_t alpha_clicked,
    /* 文本的背景色，以及对应的alpha值，和底下小文本的alpha值（如有）*/
    lv_color_t font_clr,
    lv_opa_t alpha_text,
    lv_opa_t alpha_undertext
)
{
    lv_obj_t* button = lv_btn_create(parent);
    lv_obj_remove_style_all(button);  // 彻底移除所有从主题继承的样式

    lv_obj_add_event_cb(button, cb, LV_EVENT_ALL, NULL);
    lv_obj_set_size(button, w, h);
    lv_obj_set_style_radius(button, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(button, bgclr, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(button, alpha_normal, LV_PART_MAIN);
    lv_obj_set_style_bg_color(button, bgclr, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(button, alpha_clicked, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_set_layout(button, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(button, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    if (icon) {
        lv_obj_set_flex_flow(button, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_pad_gap(button, 12, 0);

        lv_obj_t* iconobj = lv_img_create(button);
        lv_img_set_src(iconobj, icon);

        lv_obj_t* label = lv_label_create(button);
        lv_obj_set_style_text_font(label, &lv_font_notosanssc_medium_24, 0);
        lv_label_set_text(label, text);
        lv_obj_set_style_text_color(label, font_clr, 0);
        lv_obj_set_style_text_opa(label, alpha_text, 0);
    }
    else if (under_text && strlen(under_text) > 0)
    {
        lv_obj_set_flex_flow(button, LV_FLEX_FLOW_COLUMN);

        lv_obj_t* label = lv_label_create(button);
        lv_obj_set_style_text_font(label, &lv_font_notosanssc_medium_24, 0);
        lv_label_set_text(label, text);
        lv_obj_set_style_text_color(label, font_clr, 0);
        lv_obj_set_style_text_opa(label, alpha_text, 0);

        lv_obj_t* label_under = lv_label_create(button);
        lv_obj_set_style_text_font(label_under, &lv_font_notosanssc_medium_18, 0);
        lv_label_set_text(label_under, under_text);
        lv_obj_set_style_text_color(label_under, font_clr, 0);
        lv_obj_set_style_text_opa(label_under, alpha_undertext, 0);
    }
    else
    {
        lv_obj_t* label = lv_label_create(button);
        lv_obj_set_style_text_font(label, &lv_font_notosanssc_medium_24, 0);
        lv_label_set_text(label, text);
        lv_obj_set_style_text_color(label, font_clr, 0);
        lv_obj_set_style_text_opa(label, alpha_text, 0);
        lv_obj_center(label);
    }
    return button;
}

void toggle_checked_state(lv_event_t* e) {
    lv_obj_t* btn = lv_event_get_target(e);

    if (lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        lv_obj_clear_state(btn, LV_STATE_CHECKED);  // 取消选中
    }
    else {
        lv_obj_add_state(btn, LV_STATE_CHECKED);    // 设置选中
    }
}

lv_obj_t* create_checkable_button(
    lv_obj_t* parent,
    lv_coord_t w,
    lv_coord_t h,
    lv_event_cb_t cb_stated_changed,
    const char* text,
    lv_color_t bgclr,
    lv_opa_t alpha_normal,
    lv_opa_t alpha_clicked,
    lv_color_t bgclr_on,
    lv_opa_t alpha_on_normal,
    lv_opa_t alpha_on_clicked,
    lv_color_t font_clr,
    lv_opa_t alpha_text
) {
    lv_obj_t* button = lv_btn_create(parent);
    lv_obj_remove_style_all(button);  // 彻底移除所有从主题继承的样式

    lv_obj_add_event_cb(button, cb_stated_changed, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(button, w, h);
    lv_obj_set_style_radius(button, LV_RADIUS_CIRCLE, 0);

    lv_obj_clear_state(button, LV_STATE_CHECKED);  // 取消选中

    lv_obj_set_style_bg_color(button, bgclr, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(button, alpha_normal, LV_PART_MAIN);
    lv_obj_set_style_bg_color(button, bgclr, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(button, alpha_clicked, LV_PART_MAIN | LV_STATE_PRESSED);
    //checked:
    lv_obj_set_style_bg_color(button, bgclr_on, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(button, alpha_on_normal, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(button, bgclr_on, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(button, alpha_on_clicked, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);

    lv_obj_set_layout(button, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(button, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t* label = lv_label_create(button);
    lv_obj_set_style_text_font(label, &lv_font_notosanssc_medium_24, 0);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, font_clr, 0);
    lv_obj_set_style_text_opa(label, alpha_text, 0);
    lv_obj_center(label);

    return button;
}

lv_obj_t* create_brightness_slider(lv_obj_t* parent) {
    // slider
    lv_obj_t* slider = lv_slider_create(parent);
    //lv_obj_remove_style_all(slider);  // 彻底移除所有从主题继承的样式

    lv_obj_set_size(slider, 234, 72);
    lv_slider_set_range(slider, 0, 100);
    lv_slider_set_value(slider, 50, LV_ANIM_OFF);

    // 样式设置：主背景
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(slider, 31, LV_PART_MAIN);
    lv_obj_set_style_radius(slider, LV_RADIUS_CIRCLE, LV_PART_MAIN);

    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_radius(slider, 0, LV_PART_INDICATOR);

    // 移除滑块（Knob）
    lv_obj_set_style_bg_opa(slider, LV_OPA_TRANSP, LV_PART_KNOB);
    lv_obj_set_style_border_width(slider, 0, LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 0, LV_PART_KNOB);

    // 图标
    lv_obj_t* img = lv_img_create(slider);
    lv_img_set_src(img, &img_brightness);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 10, 0);

    return slider;
}


void button_display_demo(lv_obj_t* parent) {
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_size(cond, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cond, lv_color_black(), 0);
    lv_obj_clear_flag(cond, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);

    create_button(cond, 234, 72, event_handler, "壁纸", 0, 0, lv_color_white(), 51, 30, lv_color_white(), 216, 0);
    create_button(cond, 234, 72, event_handler, "关机", &img_shutdown, "", lv_color_hex(0xFF3B30), LV_OPA_30, LV_OPA_20, lv_color_hex(0xFF0000), LV_OPA_100, 0);
    create_button(cond, 234, 72, event_handler, "重启", &img_restart, "", lv_color_make(4, 222, 113), LV_OPA_30, LV_OPA_20, lv_color_make(4, 222, 113), LV_OPA_100, 0);
    create_button(cond, 234, 72, event_handler, "息屏", 0, "2 分钟", lv_color_white(), LV_OPA_20, 31, lv_color_white(), 217, 145);
    create_button(cond, 234, 72, event_handler, "2 分钟", 0, 0, lv_color_make(32, 148, 250), 255, 168, lv_color_white(), 211, 0);
    create_brightness_slider(cond);
    create_ok_button(cond, 72, event_handler);
    create_checkable_button(cond, 234, 72, toggle_checked_state, "30 秒",
        lv_color_white(), LV_OPA_20, 31,
        lv_color_make(32, 148, 250), 255, 168,
        lv_color_white(), 211);
}
