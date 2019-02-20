#include "canvas.h"

bool CCanvas::on_motion_notify_event(GdkEventMotion *event) {
	m_tMousePos = SPoint { *event };
	queue_draw();
	return true;
}

bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr) {
	Gtk::Allocation allocation { get_allocation() };
	auto const width { (double) allocation.get_width() };
	auto const height { (double) allocation.get_height() };

	// position of mouse cursor in relation to center of the window
	float sensor_x = m_tMousePos.x - width / 2;
	float sensor_y = m_tMousePos.y - height / 2;

	// blue "sky"
	cr->set_source_rgb(0.16, 0.47, 0.94);
	cr->paint();

	// brown "ground"
	cr->set_source_rgb(0.54, 0.28, 0);
	cr->set_line_width(1);

	// start drawing the shape
	// upper left verticle, moves when you move mouse cursor around
	cr->move_to(0, height / 2 + sensor_y + sensor_x);
	// upper right verticle, moves when you move mouse cursor around
	cr->line_to(width, height / 2 + sensor_y - sensor_x);
	// lower right corner of the window
	cr->line_to(width, height);
	// lower left corner of the window
	cr->line_to(0, height);
	cr->close_path();
	cr->stroke_preserve();
	cr->fill();

	// draw aircaft attitude symbol
	cr->set_source_rgb(1, 1, 1);
	cr->move_to(width / 2 - 250, height / 2);
	cr->line_to(width / 2 + 250, height / 2);
	cr->set_line_width(4);
	cr->stroke();

	// picture png quadratic, mask with a round hole in it
	// - load picture
	static Glib::RefPtr<Gdk::Pixbuf> const image = Gdk::Pixbuf::create_from_file("mask.svg");
	// - scale picture to destination size
	static Glib::RefPtr<Gdk::Pixbuf> imageS = image->scale_simple(width, height, Gdk::INTERP_BILINEAR);
	// - place scaled pictures to specified position in render context
	Gdk::Cairo::set_source_pixbuf(cr, imageS, width / 2 - 400, height / 2 - 300);
	// - open a hole for the pixels
	cr->rectangle(width / 2 - 400, height / 2 - 300, width / 2 + 400, height / 2 + 300);
	// - show the hole
	cr->fill();
	return true;
}
