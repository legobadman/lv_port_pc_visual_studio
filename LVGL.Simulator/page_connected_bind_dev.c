#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"
#include <stdio.h>

LV_IMG_DECLARE(img_qrcode_bind_dev);

lv_obj_t* create_page_connected_bind_dev(lv_obj_t* parent) {

    lv_obj_t* background = lv_obj_create(parent);
    lv_obj_set_size(background, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(background, lv_color_black(), LV_PART_MAIN);

    lv_obj_t* cond = lv_obj_create(background);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(cond, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(cond, 0, LV_PART_MAIN);
    //lv_obj_set_style_bg_color(cond, lv_color_make(255,0,0), LV_PART_MAIN);   //Debug
    lv_obj_set_style_bg_opa(cond, LV_OPA_TRANSP, 0);
    lv_obj_set_style_radius(cond, 0, LV_PART_MAIN);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(cond, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    static int alpha = 235;

    lv_obj_t* lbl_binddev = lv_label_create(cond);
    lv_label_set_text(lbl_binddev, "绑定设备");
    lv_obj_set_style_text_font(lbl_binddev, &lv_font_notosanssc_medium_36, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_binddev, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_binddev, alpha, LV_PART_MAIN);

    lv_obj_t* spaceobj = lv_obj_create(cond);
    lv_obj_set_size(spaceobj, 1, 60);
    lv_obj_set_style_bg_opa(spaceobj, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(spaceobj, 0, 0);

    lv_obj_t* qrcode = lv_img_create(cond); /*Create an image object for the cursor */
    lv_obj_set_style_radius(qrcode, 5, 0);
    lv_img_set_src(qrcode, &img_qrcode_bind_dev);
    //lv_obj_set_size(qrcode, 183, 183);

    lv_obj_t* spaceobj2 = lv_obj_create(cond);
    lv_obj_set_size(spaceobj2, 1, 30);
    lv_obj_set_style_bg_opa(spaceobj2, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(spaceobj2, 0, 0);

    static lv_coord_t col_dsc[] = { 20, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = { 36, 72, LV_GRID_TEMPLATE_LAST };

    lv_obj_t* grid = lv_obj_create(cond);
    lv_obj_set_size(grid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(grid, 0, 0);
    lv_obj_set_style_shadow_width(grid, 0, 0);
    lv_obj_set_style_pad_all(grid, 0, 0);
    lv_obj_set_style_pad_column(grid, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_row(grid, 10, LV_PART_MAIN);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

    lv_obj_t* lbl_first = lv_label_create(grid);
    lv_label_set_text(lbl_first, "1.");
    lv_obj_set_style_text_font(lbl_first, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_first, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_first, alpha, LV_PART_MAIN);
    lv_obj_set_grid_cell(lbl_first, LV_GRID_ALIGN_START, 0, 1,
        LV_GRID_ALIGN_START, 0, 1);

    lv_obj_t* lbl_hint1 = lv_label_create(grid);
    lv_label_set_text(lbl_hint1, "扫码下载APP");
    lv_obj_set_style_text_font(lbl_hint1, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_hint1, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_hint1, alpha, LV_PART_MAIN);
    lv_obj_set_grid_cell(lbl_hint1, LV_GRID_ALIGN_START, 1, 1,
        LV_GRID_ALIGN_START, 0, 1);

    lv_obj_t* lbl_second = lv_label_create(grid);
    lv_label_set_text(lbl_second, "2.");
    lv_obj_set_style_text_font(lbl_second, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_second, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_second, alpha, LV_PART_MAIN);
    lv_obj_set_grid_cell(lbl_second, LV_GRID_ALIGN_START, 0, 1,
        LV_GRID_ALIGN_START, 1, 1);

    lv_obj_t* lbl_hint2 = lv_label_create(grid);
    lv_label_set_text(lbl_hint2, "在APP登录页面点击新设备注册");
    lv_obj_set_style_text_font(lbl_hint2, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_hint2, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_opa(lbl_hint2, alpha, LV_PART_MAIN);
    lv_obj_set_width(lbl_hint2, 200);
    lv_label_set_long_mode(lbl_hint2, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_bg_color(lbl_hint2, lv_color_make(0, 255, 0), 0);
    lv_obj_set_grid_cell(lbl_hint2, LV_GRID_ALIGN_START, 1, 1,
        LV_GRID_ALIGN_START, 1, 1);

    lv_obj_center(cond);

    return background;
}
