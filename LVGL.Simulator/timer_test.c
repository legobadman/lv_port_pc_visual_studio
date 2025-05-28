#include "lvgl/lvgl.h"

static int count = 0;
static lv_obj_t* label;

void my_timer(lv_timer_t* timer)
{
    lv_obj_t* _label = timer->user_data;
    lv_label_set_text_fmt(_label, "%d", count++);
}


void btn_cb(lv_event_t* event) {
    if (event->code == LV_EVENT_CLICKED) {
        lv_obj_t* timer = event->user_data;
        lv_timer_reset(timer);
    }
}

void timer_demo(lv_obj_t* parent)
{
    lv_obj_t* btn = lv_btn_create(parent);

    label = lv_label_create(parent);
    lv_obj_align_to(label, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_label_set_text(label, "abb");

    lv_timer_t* timer = lv_timer_create(my_timer, 5000, label);
    lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_ALL, timer);
    //lv_timer_ready(timer);
}
