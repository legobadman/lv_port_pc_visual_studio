#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"
#include <stdio.h>

static lv_obj_t* label_date;
static lv_obj_t* label_time;
static lv_obj_t* meter;
static lv_style_t style_bullet;

static lv_obj_t* arc_outer;    // 外层圆弧
static lv_obj_t* arc_middle;   // 中层圆弧
static lv_obj_t* arc_inner;    // 内层圆弧

static lv_obj_t* label_cpu;    //CPU的百分比数值
static lv_obj_t* label_gpu;
static lv_obj_t* label_ram;

static void create_datetime(lv_obj_t* parent)
{
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);

    //调试时打开
    //lv_obj_set_style_bg_color(cond, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(cond, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(cond, 0, 0);
    lv_obj_set_style_shadow_width(cond, 0, 0);

    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(cond, 14, 0);
    lv_obj_set_style_pad_all(cond, 0, 0);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    label_date = lv_label_create(cond);
    lv_label_set_text(label_date, "4月16日 周三");
    lv_obj_set_style_text_font(label_date, &lv_font_simsun_16_cjk, 0);
    lv_obj_set_style_text_color(label_date, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    label_time = lv_label_create(cond);
    lv_label_set_text(label_time, "09:15");
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(label_time, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
}

static void meter_box_with_arc(lv_obj_t* root) {
    meter = lv_meter_create(root);
    lv_obj_center(meter);

    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);
    lv_obj_remove_style(meter, NULL, LV_PART_MAIN);

    lv_obj_set_size(meter, 72, 72);

    static uint16_t groove_width = 7;

    arc_outer = lv_arc_create(meter);
    lv_obj_set_size(arc_outer, 72, 72);
    lv_obj_center(arc_outer);
    lv_arc_set_range(arc_outer, 0, 100);
    lv_arc_set_value(arc_outer, 80);
    lv_arc_set_bg_angles(arc_outer, 0, 360);        //背景弧是整个圆
    lv_obj_set_style_arc_width(arc_outer, groove_width, LV_PART_MAIN);  //设置背景凹槽圆弧的宽度
    lv_obj_set_style_arc_color(arc_outer, lv_color_make(64, 51, 60), LV_PART_MAIN);    //设置背景凹槽圆弧的原色
    lv_arc_set_mode(arc_outer, LV_ARC_MODE_NORMAL);
    lv_obj_set_style_arc_width(arc_outer, groove_width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_outer, lv_color_make(8, 224, 224), LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc_outer, true, LV_PART_INDICATOR);
    // 去除 knob 和点击事件
    lv_obj_remove_style(arc_outer, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(arc_outer, LV_OBJ_FLAG_CLICKABLE);

    arc_middle = lv_arc_create(meter);
    lv_obj_set_size(arc_middle, 56, 56);  // 比外层小
    lv_obj_center(arc_middle);
    lv_arc_set_range(arc_middle, 0, 100);
    lv_arc_set_value(arc_middle, 50);
    lv_arc_set_bg_angles(arc_middle, 0, 360);
    lv_obj_set_style_arc_width(arc_middle, groove_width, LV_PART_MAIN);  //设置背景凹槽圆弧的宽度
    lv_obj_set_style_arc_color(arc_middle, lv_color_make(64, 51, 60), LV_PART_MAIN);    //设置背景凹槽圆弧的原色
    lv_arc_set_mode(arc_middle, LV_ARC_MODE_NORMAL);
    lv_obj_set_style_arc_width(arc_middle, groove_width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_middle, lv_color_make(30, 152, 246), LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc_middle, true, LV_PART_INDICATOR);
    // 去除 knob 和点击事件
    lv_obj_remove_style(arc_middle, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(arc_middle, LV_OBJ_FLAG_CLICKABLE);

    arc_inner = lv_arc_create(meter);
    lv_obj_set_size(arc_inner, 40, 40);  // 更小
    lv_obj_center(arc_inner);
    lv_arc_set_range(arc_inner, 0, 100);
    lv_arc_set_value(arc_inner, 30);
    lv_arc_set_bg_angles(arc_inner, 0, 360);
    lv_obj_set_style_arc_width(arc_inner, groove_width, LV_PART_MAIN);  //设置背景凹槽圆弧的宽度
    lv_obj_set_style_arc_color(arc_inner, lv_color_make(64, 51, 60), LV_PART_MAIN);    //设置背景凹槽圆弧的原色
    lv_arc_set_mode(arc_inner, LV_ARC_MODE_NORMAL);
    lv_obj_set_style_arc_width(arc_inner, groove_width, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc_inner, lv_color_make(114, 127, 250), LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc_inner, true, LV_PART_INDICATOR);
    // 去除 knob 和点击事件
    lv_obj_remove_style(arc_inner, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(arc_inner, LV_OBJ_FLAG_CLICKABLE);
}

static void hareware_playload(lv_obj_t* parent, float cpu_val, float gpu_val, float ram_val) {

    static lv_coord_t col_dsc[] = {
        20,  // 圆点列自动适配（也可以直接写固定值如20）
        0,   //第一列和第二列的空隙
        43,  // 名称列
        8,   //第二列和第三列的空隙
        60,  // 数值列
        LV_GRID_TEMPLATE_LAST
    };
    static lv_coord_t row_dsc[] = { LV_SIZE_CONTENT, LV_SIZE_CONTENT, LV_SIZE_CONTENT, LV_GRID_TEMPLATE_LAST };

    lv_obj_t* grid = lv_obj_create(parent);
    lv_obj_set_size(grid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0);
    lv_obj_set_style_pad_all(grid, 0, 0);
    lv_obj_set_style_pad_column(grid, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(grid, 12, LV_PART_MAIN);

    // 去掉grid的边框
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(grid, 0, 0);
    lv_obj_set_style_shadow_width(grid, 0, 0);

    lv_obj_center(grid);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);

    struct {
        const char* name;
        float value;
        lv_color_t color;
    } items[] = {
        { "CPU", cpu_val, lv_color_hex(0x00F5EA) },
        { "GPU", gpu_val, lv_color_hex(0x2094FA) },
        { "RAM", ram_val, lv_color_hex(0x787AFF) },
    };

    for (int i = 0; i < 3; i++) {
        // 彩色圆点
        lv_obj_t* bullet = lv_obj_create(grid);
        lv_obj_set_size(bullet, 8, 8);
        lv_obj_set_style_radius(bullet, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_color(bullet, items[i].color, 0);
        lv_obj_set_style_bg_opa(bullet, LV_OPA_COVER, 0);
        lv_obj_clear_flag(bullet, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_style(bullet, &style_bullet, 0);
        lv_obj_set_style_align(bullet, LV_ALIGN_CENTER, 0);
        lv_obj_set_grid_cell(bullet, LV_GRID_ALIGN_CENTER, 0, 1,
            LV_GRID_ALIGN_CENTER, i, 1);

        // 左侧 label（如 CPU）
        lv_obj_t* label_name = lv_label_create(grid);
        lv_label_set_text(label_name, items[i].name);
        lv_obj_set_style_text_font(label_name, &lv_font_montserrat_20, LV_PART_MAIN);  // 设置字体大小
        lv_obj_set_style_text_color(label_name, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_set_style_text_opa(label_name, 148, LV_PART_MAIN);
        lv_obj_set_style_align(label_name, LV_ALIGN_CENTER, 0);
        lv_obj_set_grid_cell(label_name, LV_GRID_ALIGN_START, 2, 1,
            LV_GRID_ALIGN_CENTER, i, 1);

        lv_obj_t* label_val = lv_label_create(grid);
        char buf[16];
        snprintf(buf, sizeof(buf), "%.1f%%", items[i].value * 100);

        lv_label_set_text(label_val, buf);
        lv_obj_set_style_text_font(label_val, &lv_font_montserrat_20, LV_PART_MAIN);
        lv_obj_set_style_text_color(label_val, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_set_style_text_opa(label_val, 236, LV_PART_MAIN);
        lv_obj_set_grid_cell(label_val, LV_GRID_ALIGN_END, 4, 1,
            LV_GRID_ALIGN_CENTER, i, 1);

        if (i == 0) label_cpu = label_val;
        else if (i == 1) label_gpu = label_val;
        else if (i == 2) label_ram = label_val;
    }
}

static void init_style() {
    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);
}

static void create_hareware_playload(lv_obj_t* parent)
{
    init_style();

    lv_obj_t* root = lv_obj_create(parent);
    lv_obj_set_layout(root, LV_LAYOUT_FLEX);

    //lv_obj_set_style_bg_color(root, lv_color_make(46, 0, 36), 0);
    lv_obj_set_style_bg_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(root, 0, 0);
    lv_obj_set_style_shadow_width(root, 0, 0);

    lv_obj_set_flex_flow(root, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_gap(root, 14, 0);
    lv_obj_set_style_pad_all(root, 0, 0);
    lv_obj_set_size(root, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_flex_align(root, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    meter_box_with_arc(root);
    hareware_playload(root, 0.652f, 0.403f, 0.229f);
}

void create_home_page(lv_obj_t * parent) {
    lv_obj_t* cond = lv_obj_create(parent);
    lv_obj_set_layout(cond, LV_LAYOUT_FLEX);
    lv_obj_set_style_bg_color(cond, lv_color_black(), 0);
    lv_obj_set_flex_flow(cond, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_gap(cond, 14, 0);
    lv_obj_set_style_pad_all(cond, 0, 0);
    lv_obj_set_style_pad_top(cond, 200, 0);
    lv_obj_set_flex_align(cond, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(cond, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(cond, lv_color_make(46, 0, 36), 0);

    create_datetime(cond);
    create_hareware_playload(cond);
}
