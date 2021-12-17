use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Button, DrawingArea};
use std::rc::Rc;
use std::cell::RefCell;

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
            .default_width(1024)
            .default_height(768)
            .build();

        let button = Button::with_label("Click me!");
        

        let frame = gtk::Box::new(gtk::Orientation::Vertical, 2);
        let area = DrawingArea::new();
        frame.pack_start(&button, false, true, 0);
        frame.pack_start(&area, true, true, 0);
        window.add(&frame);
        
        
        let mut gauge = Gauge::new(
            175.0,
            35.0,
            1024.0 / 2.0,
            768.0 / 2.0,
            -60,
            240,
            0.0,
            7000.0,
            30,
            25.0
        );

        gauge.set_value(550.0);
        Gauge::draw(&area.clone(), gauge);

        let rc_area = Rc::new(area);
        let rc_gauge = Rc::new(RefCell::new(gauge));
        button.connect_clicked(move |_| {
            let mut rc_gauge = rc_gauge.borrow_mut();
            let v = rc_gauge.val;
            rc_gauge.set_value(v + 100.0);
            // value += 100.0;
            Gauge::draw(&*rc_area, *rc_gauge);
        });


        window.show_all();
    });

    application.run();
}