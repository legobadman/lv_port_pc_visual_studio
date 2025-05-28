#include "lvgl/lvgl.h"


LV_IMG_DECLARE(img_anim_moveleft)

static void spectrum_anim_cb(void* a, int32_t v)
{
    lv_obj_set_x((lv_obj_t*)a, v);
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

void test_img(lv_obj_t* parent) {
    lv_obj_set_style_bg_color(parent, lv_color_black(), 0);
    lv_obj_t* img = lv_img_create(parent);
    lv_img_set_src(img, &img_anim_moveleft);
}

void test_shadow(lv_obj_t* parent, lv_obj_t* target)
{
    lv_obj_t* shadow = lv_obj_create(lv_layer_top());
    lv_obj_set_size(shadow, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(shadow, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(shadow, LV_OPA_70, LV_PART_MAIN);  // 设置透明度
    lv_obj_set_style_radius(shadow, 0, LV_PART_MAIN);          // 视需求决定是否圆角
    lv_obj_clear_flag(shadow, LV_OBJ_FLAG_CLICKABLE);          // 让它不响应点击
    lv_obj_set_style_pad_all(shadow, 0, LV_PART_MAIN);

    lv_obj_t* img = lv_img_create(shadow);
    lv_img_set_src(img, &img_anim_moveleft);
    lv_obj_update_layout(img);

    int screen_width = lv_obj_get_width(lv_scr_act());
    int screen_height = lv_obj_get_height(lv_scr_act());
    int obj_width = 80;// lv_obj_get_width(img); 取得是整个包括阴影的宽度，现在只要手指那部分就行
    int obj_height = lv_obj_get_height(img);
    int center_x = (screen_width - obj_width) / 2;
    int center_y = (screen_height - obj_height) / 2;

    lv_obj_set_y(img, center_y);  // 固定垂直位置
    lv_obj_set_x(img, screen_width);     // 初始放在屏幕右侧（外面）

    lv_obj_t* lbl_tip = lv_label_create(shadow);
    lv_label_set_text(lbl_tip, "向左滑动");
    lv_obj_set_style_text_color(lbl_tip, lv_color_white(), 0);
    lv_obj_set_style_text_opa(lbl_tip, 217, 0);
    lv_obj_set_style_text_font(lbl_tip, &lv_font_notosanssc_medium_30, 0);
    lv_obj_align(lbl_tip, LV_ALIGN_CENTER, 0, obj_height + 20);


    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)spectrum_anim_cb);
    lv_anim_set_var(&a, img);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, screen_width, center_x);
    lv_anim_set_repeat_count(&a, 10);
    lv_anim_start(&a);
}
