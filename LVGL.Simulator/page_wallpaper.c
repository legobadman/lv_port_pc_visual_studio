#include "round_button.h"

void cb_ensure_wallpaper(lv_event_t* event)
{

}

lv_obj_t* create_img_group(lv_obj_t* parent, uint32_t w, uint32_t h)
{
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_style_pad_all(cond, 0, 0);
    lv_obj_set_style_pad_gap(cond, 16, 0);
    lv_obj_set_style_pad_left(cond, 32, 0);
    lv_obj_set_style_pad_right(cond, 32, 0);
    lv_obj_set_style_bg_opa(cond, LV_OPA_TRANSP, 0);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_border_width(cond, 0, 0);
    lv_obj_set_size(cond, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    lv_obj_t* img1 = lv_obj_create(cond);
    lv_obj_set_size(img1, w, h);
    lv_obj_set_style_radius(img1, 20, 0);
    lv_obj_set_style_border_width(img1, 0, 0);
    lv_obj_set_style_bg_color(img1, lv_color_hex(0xFF0000), 0);

    lv_obj_t* img2 = lv_obj_create(cond);
    lv_obj_set_size(img2, w, h);
    lv_obj_set_style_radius(img2, 20, 0);
    lv_obj_set_style_border_width(img1, 0, 0);
    lv_obj_set_style_bg_color(img2, lv_color_hex(0x00FF00), 0);

    lv_obj_t* img3 = lv_obj_create(cond);
    lv_obj_set_size(img3, w, h);
    lv_obj_set_style_radius(img3, 20, 0);
    lv_obj_set_style_border_width(img1, 0, 0);
    lv_obj_set_style_bg_color(img3, lv_color_hex(0x0000FF), 0);

    return cond;
}

void create_wallpaper(lv_obj_t* parent)
{
    lv_obj_t* background = lv_obj_create(parent);
    lv_obj_set_style_bg_color(background, lv_color_black(), 0);
    lv_obj_set_size(background, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(background, 0, 0);
    lv_obj_set_style_pad_all(background, 0, 0);
    lv_obj_set_style_pad_top(background, 80, 0);

    // 2. 滚动区域容器（内部放大内容）
    lv_obj_t* scroll_container = lv_obj_create(background);
    lv_obj_set_style_pad_all(scroll_container, 0, 0);
    lv_obj_set_style_bg_opa(scroll_container, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(scroll_container, 0, 0);
    lv_obj_set_style_radius(scroll_container, 0, 0);

    lv_obj_set_size(scroll_container, LV_PCT(100), LV_SIZE_CONTENT);  // scroll 可视区域高度
    lv_obj_align(scroll_container, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_scroll_dir(scroll_container, LV_DIR_HOR);        // 横向滚动
    lv_obj_add_flag(scroll_container, LV_OBJ_FLAG_SCROLLABLE);  // 开启拖动
    lv_obj_set_scrollbar_mode(scroll_container, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_set_style_clip_corner(scroll_container, true, 0);    // 防止被撑开

    static const uint32_t img_width = 196, img_height = 686, size_button = 72;
    lv_obj_t* imgs = create_img_group(scroll_container, img_width, img_height);
    lv_obj_t* btn = create_ok_button(background, size_button, cb_ensure_wallpaper);
    lv_obj_align_to(btn, scroll_container, LV_ALIGN_OUT_BOTTOM_MID, 0, 62);
}
