#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"
#include <stdio.h>


void create_clear_button(lv_obj_t* parent) {
    lv_obj_t* btn = lv_btn_create(parent);  // 创建按钮，挂载在当前屏幕
    lv_obj_set_size(btn, 210, 72);               // 设置按钮大小（宽高）
    lv_obj_center(btn);                           // 居中显示

    // 设置圆角为最大（形成“胶囊”效果）
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);

    // 设置按钮背景颜色
    lv_obj_set_style_bg_color(btn, lv_color_make(32, 32, 32), 0);  // 深灰背景
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);                 // 不透明

    // 移除默认边框和点击效果
    lv_obj_set_style_border_width(btn, 0, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);

    // 创建文本标签
    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "全部清除");
    lv_obj_set_style_text_font(label, &lv_font_notosanssc_regular_24, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    // 居中对齐文本
    lv_obj_center(label);
}

void create_notification_list(lv_obj_t* parent) {

}

void create_notify_page(lv_obj_t* parent) {
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_style_bg_color(cond, lv_color_black(), 0);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(cond, 30, 0);
    lv_obj_set_style_pad_all(cond, 0, 0);
    lv_obj_set_style_pad_top(cond, 60, 0);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(cond, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cond, lv_color_black(), 0);

    create_clear_button(cond);
    create_notification_list(cond);
}
