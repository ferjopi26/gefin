#include "relatorio_mensal.h"

void RelatorioMensal::get_itens(Glib::ustring dataini, Glib::ustring datafin)
{
    QueryItem *query_item = new QueryItem();
    listItens = query_item->GetItens(dataini.c_str(), datafin.c_str());
}

void RelatorioMensal::get_totais_itens(Glib::ustring dataini, Glib::ustring datafin)
{
    QueryItem *query_item = new QueryItem();
    listItens = query_item->GetTotaisItens(dataini.c_str(), datafin.c_str());
}

void RelatorioMensal::body(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
{
    Glib::RefPtr<Pango::Layout> layout = print_context->create_pango_layout();
    
    layout->set_font_description(Pango::FontDescription("Arial 10"));

    double current_y = 70;

    RelatorioMensal::get_itens(data_ini, data_fin);
    
    for (auto itens = listItens->begin(); itens != listItens->end(); ++itens)
    {
        int current_x = 10;
        RelatorioMensal::fill_color(cr, current_y-2, current_x, 550, 11);

        //iditem
        layout->set_text(itens->get_iditem());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_RIGHT);
        cr->move_to(50, current_y);
        layout->show_in_cairo_context(cr);

        //item
        layout->set_text(itens->get_item());
        layout->set_width(220 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(80, current_y);
        layout->show_in_cairo_context(cr);

        //valor
        layout->set_text(itens->get_valor());
        layout->set_width(50 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_RIGHT);
        cr->move_to(250, current_y);
        layout->show_in_cairo_context(cr);
        
        //data
        layout->set_text(itens->get_data());
        layout->set_width(100 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(340, current_y);
        layout->show_in_cairo_context(cr);
        
        //classe
        layout->set_text(itens->get_classe());
        layout->set_width(100 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(400, current_y);
        layout->show_in_cairo_context(cr);
        
        current_y +=10;

        if(fill == 0) fill = 1;
        else fill = 0;

        if (current_y > 780)
        {
            cr->show_page();
            page++;
            header(cr, print_context);
            footer(cr, print_context);
            current_y = 70;
        }
    }

    layout->set_text("Receitas");
    layout->set_width(20 * PANGO_SCALE);
    layout->set_alignment(Pango::ALIGN_LEFT);
    cr->move_to(20, current_y + 10);
    layout->show_in_cairo_context(cr);

    layout->set_text("Despesas");
    layout->set_width(20 * PANGO_SCALE);
    layout->set_alignment(Pango::ALIGN_LEFT);
    cr->move_to(70, current_y + 10);
    layout->show_in_cairo_context(cr);

    layout->set_text("Saldo");
    layout->set_width(20 * PANGO_SCALE);
    layout->set_alignment(Pango::ALIGN_LEFT);
    cr->move_to(120, current_y + 10);
    layout->show_in_cairo_context(cr);

    current_y +=10;

    if (current_y > 780)
    {
        cr->show_page();
        page++;
        header(cr, print_context);
        footer(cr, print_context);
        current_y = 70;
    }

    RelatorioMensal::get_totais_itens(data_ini, data_fin);

    for (auto totais = listItens->begin(); totais != listItens->end(); ++totais)
    {
        layout->set_text(totais->get_receitas());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(20, current_y + 10);
        layout->show_in_cairo_context(cr);

        layout->set_text(totais->get_despesas());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(70, current_y + 10);
        layout->show_in_cairo_context(cr);

        layout->set_text(totais->get_saldo());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(120, current_y + 10);
        layout->show_in_cairo_context(cr);
    }

}

void RelatorioMensal::footer(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
    Glib::ustring pagina;

    cr->set_line_width(0.5);
    cr->move_to(10, 790);
    cr->line_to(570, 790);
    cr->stroke();

    current_time();
        
    Glib::RefPtr<Pango::Layout> layout = print_context->create_pango_layout();

    layout->set_font_description(Pango::FontDescription("Arial 8"));
    
    layout->set_text(Glib::ustring("Gestão Financeira").normalize(Glib::NORMALIZE_DEFAULT));
    cr->move_to(20, 800);
    layout->show_in_cairo_context(cr);

    layout->set_text(Glib::ustring("Relatório Mensal").normalize(Glib::NORMALIZE_DEFAULT));
    cr->move_to(160, 800);
    layout->show_in_cairo_context(cr);

    layout->set_text(time_string);
    cr->move_to(305, 800);
    layout->show_in_cairo_context(cr);

    pagina = Glib::ustring::sprintf("Página %d de %d", page, num_pages);

    layout->set_text(Glib::ustring(pagina).normalize(Glib::NORMALIZE_DEFAULT));
    cr->move_to(450, 800);
    layout->show_in_cairo_context(cr);

}

RelatorioMensal::RelatorioMensal(){}

RelatorioMensal::~RelatorioMensal(){}

Glib::RefPtr<RelatorioMensal> RelatorioMensal::create()
{
    return Glib::RefPtr<RelatorioMensal>(new RelatorioMensal());
}

void RelatorioMensal::header(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
    Glib::RefPtr<Pango::Layout> layout = print_context->create_pango_layout();

    layout->set_font_description(Pango::FontDescription("Arial 15"));
    layout->set_text("Relatório Mensal");
    cr->move_to(20, 20);
    layout->show_in_cairo_context(cr);

    layout->set_font_description(Pango::FontDescription("Arial 10"));

    layout->set_text(interval);
    cr->move_to(150, 25);
    layout->show_in_cairo_context(cr);
    
    layout->set_text("Id");
    cr->move_to(20, 40);
    layout->show_in_cairo_context(cr);

    layout->set_text("Item");
    cr->move_to(80, 40);
    layout->show_in_cairo_context(cr);

    layout->set_text("Valor");
    cr->move_to(260, 40);
    layout->show_in_cairo_context(cr);

    layout->set_text("Data");
    cr->move_to(340, 40);
    layout->show_in_cairo_context(cr);

    layout->set_text("Classe");
    cr->move_to(400, 40);
    layout->show_in_cairo_context(cr);

    cr->set_line_width(1.0);
    cr->move_to(10, 60);
    cr->line_to(560, 60);
    cr->stroke();
}

void RelatorioMensal::list_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring period)
{
    data_ini = dataini;
    data_fin = datafin;
    interval = period;

    Glib::RefPtr<Gtk::PageSetup> pagesetup =  Gtk::PageSetup::create();
    Gtk::PaperSize *papersize = new Gtk::PaperSize(Gtk::PAPER_NAME_A4, "A4", 595, 842, Gtk::UNIT_POINTS);

    pagesetup->set_paper_size(*papersize);
    
    set_default_page_setup(pagesetup);

    run();
}
