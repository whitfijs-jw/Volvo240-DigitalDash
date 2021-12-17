use gtk::prelude::*;
use glib::SignalHandlerId;
use std::rc::Rc;

pub trait Draw<T> {
    fn draw(
        area: &gtk::DrawingArea,
        drawable: T
    ) -> SignalHandlerId;
}

#[derive(Debug, Copy, Clone)]
pub struct Gauge {
    outer: f64,
    inner: f64,
    xc: f64,
    yc: f64,
    theta_start: isize,
    theta_end: isize,
    step: usize,
    min: f64,
    max: f64,
    pub val: f64,
    needle_center_diameter: f64,
}
impl Gauge {

    pub fn new(
        radius: f64,
        needle_center_diameter: f64,
        xc: f64,
        yc: f64,
        start_angle: isize,
        end_angle: isize,
        min: f64,
        max: f64,
        step: usize,
        tick_width: f64,
    ) -> Gauge {

        return Gauge {
            outer: radius,
            inner: radius - tick_width,
            xc: xc,
            yc: yc,
            theta_start: 180 - end_angle,
            theta_end: 180 - start_angle,
            step: step, 
            min: min,
            max: max, 
            val: 0.0, 
            needle_center_diameter: needle_center_diameter
        };
    }

    pub fn set_value(&mut self, val: f64) {
        if val <= self.max && val >= self.min {
            self.val = val;
        } else if val > self.max {
            self.val = self.max;
        } else {
            self.val = self.min;
        }
    }


    fn draw_background(&self, c: &cairo::Context) {
        c.set_source_rgb(1.0, 1.0, 1.0);
        c.paint();
    }

    fn draw_needle(&self, c: &cairo::Context) {
        // needle center
        c.arc(self.xc, self.yc, self.needle_center_diameter, 0.0, 2.0 * std::f64::consts::PI);
        c.set_source_rgb(0.0, 0.0, 0.0);
        c.set_line_width(2.0);
        c.fill();

        c.move_to(self.xc, self.yc);
        c.set_source_rgb(1.0, 0.6, 0.0);
        c.set_line_width(10.0);
        
        let pct = self.val / (self.max - self.min);

        let d = self.theta_end as f64 - ((self.theta_end - self.theta_start) as f64 * pct);
        let a = d * std::f64::consts::PI / 180.0;

        c.line_to(self.xc + (self.outer * a.cos()) , self.yc - (self.outer * a.sin()));
        c.stroke();
    }

    fn draw_gauge_face(&self, c: &cairo::Context) {
        c.set_source_rgb(0.0, 0.0, 0.0);
        c.set_line_width(2.0);

        for theta in (self.theta_start..=self.theta_end).step_by(self.step) {
            let a = theta as f64 * std::f64::consts::PI / 180.0;

            c.move_to(self.xc + (self.outer * a.cos()) , self.yc - (self.outer * a.sin()));
            c.line_to(self.xc + (self.inner * a.cos()), self.yc - (self.inner * a.sin()));
        }
        c.stroke();
    }

    fn draw_internal(&self, c: &cairo::Context) {

        self.draw_background(c);

        self.draw_gauge_face(c);

        self.draw_needle(c);
    }
}

impl Draw<Gauge> for Gauge {
    fn draw(
        area: &gtk::DrawingArea,
        gauge: Gauge
    ) -> SignalHandlerId {

        let rc_gauge = Rc::new(gauge);

        let handler = area.connect_draw( move |w, c| {
            rc_gauge.draw_internal(c);
            
            w.queue_draw();

            gtk::Inhibit(false)
        });

        return handler;
    }
}