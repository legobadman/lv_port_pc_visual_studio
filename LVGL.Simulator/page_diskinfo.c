#include "round_button.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

LV_IMG_DECLARE(img_sata)
LV_IMG_DECLARE(img_disk_used)
LV_IMG_DECLARE(img_block_nodisk)

enum alert_level {
    alert_normal,
    alert_warning,
    alert_serious
};

enum stroge_level {
    stroge_GB,
    stroge_TB
};

struct nas_disk_info {
    bool connected;
    int id;
    float total;
    float tempaure;
    enum stroge_level stroge;
    enum alert_level alert;  //也许level可以在本地算
};

static struct nas_disk_info nas_disks[6];

static void _random_init_nas_disk_infos() {

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 6; i++) {
        nas_disks[i].id = i + 1;
        nas_disks[i].total = 1.8f;
        nas_disks[i].stroge = stroge_TB;
        nas_disks[i].alert = alert_normal;
        nas_disks[i].tempaure = 48.f;

        int random_num = rand() % 5;
        if (random_num <= 1) nas_disks[i].connected = false;
        else nas_disks[i].connected = true;

        if (nas_disks[i].connected) {
            random_num = rand() % 3;
            if (random_num == 0) {
                nas_disks[i].alert = alert_normal;
            }
            else if (random_num == 1) {
                nas_disks[i].alert = alert_warning;
            }
            else if (random_num == 2) {
                nas_disks[i].alert = alert_serious;
            }
        }
    }
}

lv_obj_t* create_measure_text_comp(lv_obj_t* parent, float numval, const char* measure) {
    //例如 1.8TB  48°C

    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_style_bg_opa(cond, LV_OPA_0, 0);
    lv_obj_set_style_border_width(cond, 0, 0);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(cond, 0, 0);
    lv_obj_set_size(cond, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    int int_part = (int)numval;
    int frac_part = (int)((numval - int_part) * 100); // 保留两位小数

    lv_obj_t* lbl_num = lv_label_create(cond);
    lv_obj_set_style_text_font(lbl_num, &lv_font_inter_24_regular, 0);
    lv_obj_set_style_text_color(lbl_num, lv_color_white(), 0);
    lv_label_set_text_fmt(lbl_num, "%d.%d", int_part, frac_part);

    lv_obj_t* lbl_measure = lv_label_create(cond);
    lv_obj_set_style_text_font(lbl_measure, &lv_font_d_din_pro_medium_24, 0);
    lv_obj_set_style_text_color(lbl_measure, lv_color_white(), 0);
    lv_label_set_text(lbl_measure, measure);

    return cond;
}

void create_disk_info_block(struct nas_disk_info info, int width, lv_obj_t* parent) {
    lv_obj_t* block = lv_obj_create(parent);
    lv_obj_set_layout(block, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(block, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_width(block, width);
    lv_obj_set_height(block, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(block, 12, 0);
    lv_obj_set_style_pad_gap(block, 18, 0);
    lv_obj_set_style_border_width(block, 0, 0);

    lv_color_t bg_color, dot_color;
    lv_opa_t bg_opa;

    switch (info.alert) {
    case alert_warning:
        bg_color = lv_color_hex(0xFF9500);
        bg_opa = LV_OPA_20;
        dot_color = bg_color;
        break;
    case alert_serious:
        bg_color = lv_color_hex(0xFF3B30);
        bg_opa = LV_OPA_20;
        dot_color = bg_color;
        break;
    case alert_normal:
    default:
        bg_color = lv_color_white();
        bg_opa = 31;
        dot_color = lv_color_hex(0x2094FA);
        break;
    }
    lv_obj_set_style_bg_color(block, bg_color, 0);
    lv_obj_set_style_bg_opa(block, bg_opa, 0);


    lv_obj_t* disk_id = lv_obj_create(block);
    lv_obj_set_layout(disk_id, LV_LAYOUT_FLEX);
    lv_obj_set_size(disk_id, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(disk_id, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(disk_id, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_all(disk_id, 0, 0);
    lv_obj_set_style_bg_opa(disk_id, LV_OPA_0, 0);
    lv_obj_set_style_border_width(disk_id, 0, 0);

    static lv_style_t style_gray_text;
    lv_style_init(&style_gray_text);
    lv_style_set_text_font(&style_gray_text, &lv_font_notosanssc_medium_20);
    lv_style_set_text_color(&style_gray_text, lv_color_white());
    lv_style_set_text_opa(&style_gray_text, 115);

    if (info.connected) {
        lv_obj_t* status_point = lv_obj_create(disk_id);
        lv_obj_set_style_bg_color(status_point, dot_color, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(status_point, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_radius(status_point, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_border_width(status_point, 0, 0);
        lv_obj_set_size(status_point, 10, 10);

        lv_obj_t* lbl_disk = lv_label_create(disk_id);
        lv_obj_set_style_text_font(lbl_disk, &lv_font_notosanssc_medium_24, 0);
        lv_obj_set_style_text_color(lbl_disk, lv_color_white(), 0);
        lv_label_set_text(lbl_disk, "硬盘");

        lv_obj_t* lbl_id = lv_label_create(disk_id);
        char id = '0' + info.id;
        lv_obj_set_style_text_font(lbl_id, &lv_font_notosanssc_medium_24, 0);
        lv_obj_set_style_text_color(lbl_id, lv_color_white(), 0);
        lv_label_set_text(lbl_id, &id);

        static lv_coord_t col_dsc[] = { LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST };
        static lv_coord_t row_dsc[] = { LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST };

        lv_obj_t* grid = lv_obj_create(block);
        lv_obj_set_size(grid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0);
        lv_obj_set_style_border_width(grid, 0, 0);
        lv_obj_set_style_shadow_width(grid, 0, 0);
        lv_obj_set_style_pad_all(grid, 0, 0);
        lv_obj_set_style_pad_column(grid, 24, LV_PART_MAIN);
        lv_obj_set_style_pad_row(grid, 10, LV_PART_MAIN);
        lv_obj_set_layout(grid, LV_LAYOUT_GRID);
        lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

        const char* stroge_ = (info.stroge == stroge_GB) ? "GB" : "TB";

        lv_obj_t* disk_total = create_measure_text_comp(grid, info.total, stroge_);
        lv_obj_set_grid_cell(disk_total, LV_GRID_ALIGN_START, 0, 1,
            LV_GRID_ALIGN_START, 0, 1);

        lv_obj_t* temparue = create_measure_text_comp(grid, info.tempaure, "°C");
        lv_obj_set_grid_cell(temparue, LV_GRID_ALIGN_START, 1, 1,
            LV_GRID_ALIGN_START, 0, 1);

        lv_obj_t* lbl_stroge = lv_label_create(grid);
        lv_label_set_text(lbl_stroge, "容量");
        lv_obj_add_style(lbl_stroge, &style_gray_text, 0);
        lv_obj_set_grid_cell(lbl_stroge, LV_GRID_ALIGN_START, 0, 1,
            LV_GRID_ALIGN_START, 1, 1);

        lv_obj_t* lbl_temparue = lv_label_create(grid);
        lv_label_set_text(lbl_temparue, "温度");
        lv_obj_add_style(lbl_temparue, &style_gray_text, 0);
        lv_obj_set_grid_cell(lbl_temparue, LV_GRID_ALIGN_START, 1, 1,
            LV_GRID_ALIGN_START, 1, 1);
    }
    else {
        lv_obj_set_style_pad_gap(block, 5, 0);

        lv_obj_t* lbl_disk = lv_label_create(disk_id);
        lv_obj_set_style_text_font(lbl_disk, &lv_font_notosanssc_medium_24, 0);
        lv_obj_set_style_text_color(lbl_disk, lv_color_white(), 0);
        lv_label_set_text(lbl_disk, "硬盘");

        lv_obj_t* lbl_id = lv_label_create(disk_id);
        char id = '0' + info.id;
        lv_obj_set_style_text_font(lbl_id, &lv_font_notosanssc_medium_24, 0);
        lv_obj_set_style_text_color(lbl_id, lv_color_white(), 0);
        lv_label_set_text(lbl_id, &id);

        lv_obj_t* lbl_unconn = lv_label_create(block);
        lv_label_set_text(lbl_unconn, "未连接");
        lv_obj_add_style(lbl_unconn, &style_gray_text, 0);
    }
}

lv_obj_t* create_disk_pos_image(lv_obj_t* parent) {
    lv_obj_set_style_bg_color(parent, lv_color_hex(0x000000), 0);
    static lv_style_t style;
    lv_style_init(&style);
    // 设置背景图片
    lv_style_set_bg_img_src(&style, &img_sata);
    lv_style_set_bg_img_opa(&style, LV_OPA_COVER); // 完全不透明
    lv_style_set_bg_color(&style, lv_color_hex(0x000000));
    lv_style_set_bg_img_tiled(&style, false); // 不平铺
    lv_style_set_pad_gap(&style, 5);
    lv_style_set_pad_left(&style, 20);
    lv_style_set_pad_right(&style, 20);
    lv_style_set_pad_top(&style, 20);
    lv_style_set_pad_bottom(&style, 32);
    lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW);
    lv_style_set_height(&style, 140);
    lv_style_set_width(&style, 204);
    lv_style_set_border_width(&style, 0);

    lv_obj_t* container = lv_obj_create(parent);
    lv_obj_add_style(container, &style, 0);
    lv_obj_set_layout(container, LV_LAYOUT_FLEX);
    lv_obj_set_style_pad_gap(container, 4, 0);
    lv_obj_set_scroll_dir(container, LV_DIR_NONE);  // 禁止主容器滚动
    lv_style_set_bg_img_src(&style, &img_sata);

    const int N = sizeof(nas_disks) / sizeof(struct nas_disk_info);
    for (int i = 0; i < N; i++) {
        lv_obj_t* disk_box_and_dot = create_column_layoutobj(container);
        lv_obj_set_style_pad_all(disk_box_and_dot, 0, 0);
        lv_obj_set_style_pad_gap(disk_box_and_dot, 4, 0);
        lv_obj_set_flex_align(disk_box_and_dot, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

        lv_obj_t* disk_groove = lv_obj_create(disk_box_and_dot);
        lv_obj_set_size(disk_groove, 24, 74); // 设置大小为图片宽度的1/6
        lv_obj_set_scroll_dir(disk_groove, LV_DIR_NONE);  // 禁止主容器滚动

        lv_obj_t* label = lv_label_create(disk_groove);
        lv_label_set_text_fmt(label, "%d", nas_disks[i].id);
        lv_obj_set_style_text_font(label, &lv_font_inter_12_regular, 0);//todo: 字体大小
        lv_obj_set_style_text_color(label, lv_color_white(), 0);
        lv_obj_set_style_text_opa(label, LV_OPA_50, 0);
        lv_obj_center(label);

        lv_obj_set_style_bg_img_src(disk_groove, nas_disks[i].connected ? &img_disk_used : &img_block_nodisk, 0);
        lv_obj_set_style_bg_img_opa(disk_groove, LV_OPA_COVER, 0);
        lv_obj_set_style_pad_gap(disk_groove, 5, 0);
        lv_obj_set_style_border_width(disk_groove, 0, 0);

        if (nas_disks[i].connected) {
            lv_color_t dot_color;
            switch (nas_disks[i].alert) {
            case alert_warning: dot_color = lv_color_hex(0xFF9500); break;
            case alert_serious: dot_color = lv_color_hex(0xFF3B30); break;
            case alert_normal:
            default:
                dot_color = lv_color_hex(0x2094FA);
                break;
            }

            lv_obj_t* status_point = lv_obj_create(disk_box_and_dot);
            lv_obj_set_style_bg_color(status_point, dot_color, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(status_point, LV_OPA_COVER, LV_PART_MAIN);
            lv_obj_set_style_radius(status_point, LV_RADIUS_CIRCLE, 0);
            lv_obj_set_style_border_width(status_point, 0, 0);
            lv_obj_set_size(status_point, 6, 6);
        }
    }
    return container;
}


void create_disk_info_page(lv_obj_t* parent) {
    _random_init_nas_disk_infos();

    lv_obj_t* background = lv_obj_create(parent);

    lv_obj_set_size(background, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(background, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_pad_all(background, 0, 0);
    lv_obj_set_style_radius(background, 0, 0);
    lv_obj_set_layout(background, LV_LAYOUT_FLEX);
    lv_obj_set_style_pad_column(background, 24, 0);
    lv_obj_set_style_pad_top(background, 24, 0);
    lv_obj_set_flex_flow(background, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(background, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(background, LV_DIR_NONE);  // 禁止主容器滚动

    lv_obj_t* title = lv_label_create(background);
    lv_label_set_text(title, "硬盘");
    lv_obj_set_style_text_font(title, &lv_font_notosanssc_medium_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_opa(title, 217, LV_PART_MAIN);
    lv_obj_set_scroll_dir(title, LV_DIR_NONE);

    lv_obj_t* cond = create_column_layoutobj(background);
    create_disk_pos_image(cond);
    lv_obj_set_scroll_dir(cond, LV_DIR_NONE);

    lv_obj_t* disk_blocks = create_column_layoutobj(background);
    lv_obj_set_style_pad_column(disk_blocks, 12, 0);
    lv_obj_set_height(disk_blocks, LV_PCT(100));
    lv_obj_set_flex_grow(disk_blocks, 1);
    lv_obj_set_scroll_dir(disk_blocks, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(disk_blocks, LV_SCROLLBAR_MODE_AUTO);

    for (int i = 0; i < 6; i++) {
        create_disk_info_block(nas_disks[i], 234, disk_blocks);
    }
}
