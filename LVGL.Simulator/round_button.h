#include "lvgl/lvgl.h"

//创建一个用于居中摆放的布局组件
extern lv_obj_t* create_center_cond(lv_obj_t* parent);

extern lv_obj_t* create_ok_button(lv_obj_t* parent, lv_coord_t size, lv_event_cb_t cb);
extern lv_obj_t* create_button(
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
);
extern lv_obj_t* create_checkable_button(
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
);
extern lv_obj_t* create_brightness_slider(lv_obj_t* parent);
