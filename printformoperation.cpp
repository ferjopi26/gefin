#include "printformoperation.h"

PrintFormOperation::PrintFormOperation(){}

PrintFormOperation::~PrintFormOperation(){}

void PrintFormOperation::fill_color(const Cairo::RefPtr<Cairo::Context>& cr, int y, int current_x, double width, int fontSize)
{
  int rectangleYPadding = 2;

  cr->set_source_rgb(1, 1, 1);
  cr->rectangle(current_x, y+2, width, fontSize + 2 * rectangleYPadding);
  cr->fill_preserve();

  if (fill == 1)
  {
    cr->set_source_rgb(0.9, 0.9, 0.9);
  }
  else
  {
    cr->set_source_rgb(1, 1, 1);
  }

  cr->fill();
  cr->set_source_rgb(0, 0, 0);
}

void PrintFormOperation::current_time()
{
  time_t rawtime = time(NULL);

  struct tm *ptm = localtime(&rawtime);

  sprintf(time_string, "%02d/%02d/%d %02d:%02d:%02d", ptm->tm_mday, (ptm->tm_mon + 1), (ptm->tm_year + 1900), ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
}

void PrintFormOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
    set_n_pages(1);
}

void PrintFormOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
{
    Cairo::RefPtr<Cairo::Context> cairo_ctx = print_context->get_cairo_context();
    
    header(cairo_ctx, print_context);
    footer(cairo_ctx, print_context);
    body(cairo_ctx, print_context, page_nr);
}
