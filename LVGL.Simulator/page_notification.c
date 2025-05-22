#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "round_button.h"
#include <stdio.h>


static lv_obj_t* list_cond;

static void cb_remove_all_messages(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        lv_obj_clean(list_cond);
    }
}

lv_obj_t* create_message_block(lv_obj_t* parent, const char* date, const char* message, bool show_whole_msg) {
    lv_obj_t* block = lv_obj_create(parent);
    lv_obj_set_size(block, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(block, 12, 0);
    lv_obj_set_style_bg_color(block, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(block, LV_OPA_20, 0);
    lv_obj_set_style_border_width(block, 0, 0);
    lv_obj_set_layout(block, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(block, LV_FLEX_FLOW_COLUMN);

    lv_obj_t* lbl_time = lv_label_create(block);
    lv_label_set_text(lbl_time, date);
    lv_obj_set_style_text_font(lbl_time, &lv_font_notosanssc_medium_18, 0);
    lv_obj_set_style_text_color(lbl_time, lv_color_white(), 0);
    lv_obj_set_style_text_opa(lbl_time, 115, 0);

    lv_obj_t* lbl_message = lv_label_create(block);
    lv_label_set_text(lbl_message, message);
    lv_obj_set_style_text_font(lbl_message, &lv_font_notosanssc_medium_24, 0);
    lv_obj_set_style_text_color(lbl_message, lv_color_white(), 0);
    lv_obj_set_style_text_opa(lbl_message, LV_OPA_90, 0);

    if (show_whole_msg) {
        lv_obj_set_width(lbl_message, 198);
        lv_label_set_long_mode(lbl_message, LV_LABEL_LONG_WRAP);
    }
    else {
        lv_obj_set_width(lbl_message, 198);
        lv_obj_set_height(lbl_message, 72);  //通知卡片最多显示两行，根据设计稿所见到的固定高度
        lv_label_set_long_mode(lbl_message, LV_LABEL_LONG_DOT); //超出打点显示
    }
    return block;
}

void create_notification_list(lv_obj_t* parent) {
    list_cond = create_center_cond(parent);
    lv_obj_set_style_pad_gap(list_cond, 12, 0);

    create_message_block(list_cond, "3 分钟前", "设备蜂鸣：风扇故障设备蜂鸣：风扇故障", true);
    create_message_block(list_cond, "56 分钟前", "HDMI已接入", true);
    create_message_block(list_cond, "07:45", "U盘已接入", true);
    create_message_block(list_cond, "周一", "HDMI已接入", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);
    create_message_block(list_cond, "2025/03/25 09:15", "LAN 1 已断开连接", true);

    create_message_block(list_cond, "昨天", "U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入U盘已接入", false);
}

void create_no_message_page(lv_obj_t* parent) {
    lv_obj_t* page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(page, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = create_center_cond(page);
    lv_obj_set_style_pad_gap(cond, 30, 0);

    lv_obj_t* img = lv_img_create(cond);
    LV_IMG_DECLARE(img_nomessage);
    lv_img_set_src(img, &img_nomessage);

    lv_obj_t* lbl = lv_label_create(cond);
    lv_label_set_text(lbl, "暂无通知");
    lv_obj_set_style_text_font(lbl, &lv_font_notosanssc_medium_30, 0);
    lv_obj_set_style_text_color(lbl, lv_color_white(), 0);
    lv_obj_set_style_text_opa(lbl, LV_OPA_50, 0);

    lv_obj_center(cond);
}

void create_message_page(lv_obj_t* parent) {
    lv_obj_t* page = lv_obj_create(parent);

    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(page, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = create_center_cond(page);
    lv_obj_set_style_pad_gap(cond, 30, 0);
    lv_obj_set_style_pad_top(cond, 60, 0);

    create_button(cond, 210, 72, cb_remove_all_messages, "全部清除", 0, 0, lv_color_white(), 30, 16, lv_color_white(), LV_OPA_100, 0);
    create_notification_list(cond);
}
