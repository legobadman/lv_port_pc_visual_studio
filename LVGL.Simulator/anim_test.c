#include "lvgl/lvgl.h"

static uint32_t num = 0;

static void spectrum_anim_cb(void* a, int32_t v)
{
    //lv_obj_t* label = a;
    lv_obj_set_x(a, v);
    //lv_label_set_text_fmt(label, "%d", v);
}


void anim_test(lv_obj_t* parent)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, "abc");

    lv_anim_t a;
    lv_anim_init(&a);

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)spectrum_anim_cb);

    lv_anim_set_var(&a, label);

    lv_anim_set_time(&a, 5000);

    lv_anim_set_values(&a, 0, 200);

    lv_anim_set_repeat_count(&a, 2);

    lv_anim_start(&a);
}

void test_shadow(lv_obj_t* parent, lv_obj_t* target)
{
    lv_obj_t* shadow = lv_obj_create(lv_layer_top());
    lv_obj_set_size(shadow, LV_PCT(100), LV_PCT(100));
    //lv_obj_align_to(shadow, target, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(shadow, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(shadow, LV_OPA_50, LV_PART_MAIN);  // 设置透明度
    lv_obj_set_style_radius(shadow, 0, LV_PART_MAIN);          // 视需求决定是否圆角
    lv_obj_clear_flag(shadow, LV_OBJ_FLAG_CLICKABLE);          // 让它不响应点击
}
