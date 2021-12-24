use gtk::prelude::*;
use glib::SignalHandlerId;
use gtk::{DrawingArea};
use std::rc::Rc;
use std::cell::RefCell;
use std::ops::Range;
use pango::FontDescription;

pub trait Draw<T> {
    fn draw(
        drawable: Rc<RefCell<T>>
    ) -> SignalHandlerId;
}

#[derive(Debug, Clone)]
pub struct Gauge {
    outer: f64,
    inner: f64,
    xc: f64,
    yc: f64,
    theta_start: isize,
    theta_end: isize,
    step: usize,
    step_angle: usize,
    min: f64,
    max: f64,
    pub val: f64,
    dial_diameter: f64,
    drawing_area: DrawingArea,
}
impl Gauge {

    pub fn new(
        radius: f64,
        dial_diameter: f64,
        xc: f64,
        yc: f64,
        start_angle: isize,
        end_angle: isize,
        min: f64,
        max: f64,
        step: usize,
        tick_width: f64,
        drawing_area: DrawingArea,
    ) -> Gauge {

        let g = Gauge {
            outer: radius,
            inner: radius - tick_width,
            xc: xc,
            yc: yc,
            theta_start: 180 - end_angle,
            theta_end: 180 - start_angle,
            step: step, 
            step_angle: (end_angle - start_angle) as usize * step / (max - min) as usize,
            min: min,
            max: max, 
            val: 0.0, 
            dial_diameter: dial_diameter,
            drawing_area: drawing_area,
        };

        return g;
    }

    pub fn set_value(&mut self, val: f64) {
        if val <= self.max && val >= self.min {
            self.val = val;
        } else if val > self.max {
            self.val = self.max;
        } else {
            self.val = self.min;
        }

        self.drawing_area.queue_draw();
    }

    pub fn get_range(&self) -> Range<f64> {
        return Range {start: self.min, end: self.max};
    }

    pub fn draw_internal(&self, c: &cairo::Context, w: &DrawingArea) {
        c.set_source_rgb(1.0, 1.0, 1.0);
        c.paint();

        c.arc(self.xc, self.yc, self.dial_diameter, 0.0, 2.0 * std::f64::consts::PI);
        c.set_source_rgb(0.0, 0.0, 0.0);
        c.set_line_width(2.0);
        c.fill();

        let mut font = FontDescription::new();
        font.set_family("Monospace");
        font.set_weight(pango::Weight::Semibold);
        font.set_size(10 * pango::SCALE);

        let num_steps = (self.max - self.min) as usize / self.step;
        for theta in (self.theta_start..=self.theta_end).step_by(self.step_angle) {
            let a = theta as f64 * std::f64::consts::PI / 180.0;

            c.move_to(self.xc + (self.outer * a.cos()) , self.yc - (self.outer * a.sin()));
            c.line_to(self.xc + (self.inner * a.cos()), self.yc - (self.inner * a.sin()));

            let val = self.max as isize - (((theta) - self.theta_start) * (self.max - self.min) as isize  / (self.theta_end - self.theta_start));
            let v = (val).to_string();
            let layout = w.create_pango_layout(Some(&v));
            layout.set_font_description(Some(&font));

            let (w, mut h) = layout.pixel_size();

            if theta > 0 && theta < 180 {
                h = 0;
            }

            c.move_to(self.xc + (self.inner * a.cos()) - (w as f64 / 2.0), self.yc - (self.inner * a.sin()) - h as f64);
            pangocairo::show_layout(c, &layout);

        }

        c.stroke();

        c.move_to(self.xc, self.yc);
        c.set_source_rgb(1.0, 0.05, 0.05);
        c.set_line_width(self.outer / 2.0 / 10.0);
        
        let pct = (self.val - self.min) / (self.max - self.min);

        let d = self.theta_end as f64 - ((self.theta_end - self.theta_start) as f64 * pct);
        let a = d * std::f64::consts::PI / 180.0;

        c.line_to(self.xc + (self.outer * a.cos()) , self.yc - (self.outer * a.sin()));
        c.stroke();

        let val = format!("{:.2}", self.val);
        let layout = w.create_pango_layout(Some(&val));
        layout.set_font_description(Some(&font));
        let (w, h) = layout.pixel_size();

        c.move_to(self.xc - (w as f64 / 2.0), self.yc + self.dial_diameter);
        pangocairo::show_layout(c, &layout);
    }
}

impl Draw<Gauge> for Gauge {
    fn draw(
        gauge: Rc<RefCell<Gauge>>
    ) -> SignalHandlerId {

        let g = Rc::clone(&gauge);
        let handler = gauge.borrow().drawing_area.connect_draw( move |w, c| {
            g.borrow().draw_internal(c, w);
            
            w.queue_draw();

            gtk::Inhibit(false)
        });

        return handler;
    }
}