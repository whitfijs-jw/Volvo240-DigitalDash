#[macro_use]
extern crate glib;
extern crate gio;
extern crate gtk;

use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Button, DrawingArea};
use std::rc::Rc;
use std::cell::RefCell;
use std::time::Duration;
use std::fs::File;
use std::io::Read;

mod gauge;

use crate::gauge::*;

fn main() {
    let application = Application::builder()
        .application_id("com.example.FirstGtkApp")
        .build();

    application.connect_activate(|app| {
        let window = ApplicationWindow::builder()
            .application(app)
            .title("First GTK Program")
            .default_width(512)
            .default_height(768)
            .build();

        let button = Button::with_label("Click me!");
        

        let frame = gtk::Box::new(gtk::Orientation::Vertical, 3);
        let area = DrawingArea::new();
        let temp_area = DrawingArea::new();
        frame.pack_start(&temp_area, true, true, 0);
        frame.pack_start(&area, true, true, 0);
        window.add(&frame);
        
        
        let gauge = Gauge::new(
            175.0,
            35.0,
            512.0 / 2.0,
            768.0 / 4.0,
            0,
            240,
            0.0,
            4000.0,
            500,
            50.0, 
            area,
        );
        let rc_gauge = Rc::new(RefCell::new(gauge));
        let g1 = Rc::clone(&rc_gauge);
        Gauge::draw(g1);

        
        let temp_gauge = Gauge::new(
            125.0,
            15.0,
            512.0 / 2.0,
            768.0 / 4.0,
            43,
            135,
            120.0,
            300.0,
            45,
            40.0, 
            temp_area,
        );

        let rc_temp_gauge = Rc::new(RefCell::new(temp_gauge));
        let g1 = Rc::clone(&rc_temp_gauge);
        Gauge::draw(g1);

        glib::timeout_add_local(Duration::from_millis(50), move || {
            // fan speed
            let mut rc_gauge = rc_gauge.borrow_mut();

            let mut f = File::open("/sys/class/hwmon/hwmon5/fan1_input").unwrap();

            let mut line = String::new();
            f.read_to_string(&mut line).unwrap();
            let va: f64 = line.trim_end().parse().unwrap();

            rc_gauge.set_value(va as f64);

            // cpu temp
            let mut rc_temp_gauge = rc_temp_gauge.borrow_mut();
            let mut temp_f = File::open("/sys/class/hwmon/hwmon4/temp2_input").unwrap();

            let mut line = String::new();
            temp_f.read_to_string(&mut line).unwrap();
            let va: f64 = line.trim_end().parse().unwrap();
            rc_temp_gauge.set_value(va / 1000.0 * (9.0 / 5.0) + 32.0);

            glib::Continue(true)
        });


        window.show_all();
    });

    application.run();
}