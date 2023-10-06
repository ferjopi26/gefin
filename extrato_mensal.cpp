#include "extrato_mensal.h"

ExtratoMensal::ExtratoMensal(){}

ExtratoMensal::~ExtratoMensal(){}

void ExtratoMensal::get_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring banco)
{
    QueryItem *query_item = new QueryItem();
    listItens = query_item->GetItens(dataini.c_str(), datafin.c_str(), idbanco.c_str());
}

void ExtratoMensal::get_totais_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring idbanco)
{
    QueryItem *query_item = new QueryItem();
    listItens = query_item->GetTotaisItens(dataini.c_str(), datafin.c_str(), idbanco.c_str());
}

void ExtratoMensal::header(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)
{
    Glib::ustring banco;//, conta, agencia;

    Glib::RefPtr<Pango::Layout> layout = print_context->create_pango_layout();

    for (auto listbanco = listBanco->begin(); listbanco != listBanco->end(); ++listbanco)
    {
        banco = Glib::ustring::sprintf("Banco %s Conta %s Agência %s", listbanco->get_banco(), listbanco->get_conta(), listbanco->get_agencia());
        idbanco = listbanco->get_idbanco();
    }

    Glib::ustring periodo = Glib::ustring::sprintf("Período: %s/%s/%s - %s/%s/%s", data_ini.substr(8, 2).c_str(), data_ini.substr(5, 2).c_str(), 
    data_ini.substr(0, 4).c_str(), data_fin.substr(8, 2).c_str(), data_fin.substr(5, 2).c_str(), data_fin.substr(0, 4).c_str());

    layout->set_font_description(Pango::FontDescription("Arial 15"));
    layout->set_text("Extrato Mensal");
    cr->move_to(20, 20);
    layout->show_in_cairo_context(cr);

    layout->set_font_description(Pango::FontDescription("Arial 10"));

    layout->set_text(periodo);
    cr->move_to(150, 20);
    layout->show_in_cairo_context(cr);

    layout->set_text(banco);
    cr->move_to(150, 30);
    layout->show_in_cairo_context(cr);

    layout->set_text("Id");
    cr->move_to(20, 45);
    layout->show_in_cairo_context(cr);

    layout->set_text("Data");
    cr->move_to(80, 45);
    layout->show_in_cairo_context(cr);

    layout->set_text("Tipo");
    cr->move_to(160, 45);
    layout->show_in_cairo_context(cr);

    layout->set_text("Valor");
    cr->move_to(240, 45);
    layout->show_in_cairo_context(cr);

    layout->set_text("Histórico");
    cr->move_to(320, 45);
    layout->show_in_cairo_context(cr);

    cr->set_line_width(1.0);
    cr->move_to(10, 60);
    cr->line_to(560, 60);
    cr->stroke();
}

void ExtratoMensal::footer(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)
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

    layout->set_text(Glib::ustring("Extrato Mensal").normalize(Glib::NORMALIZE_DEFAULT));
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

void ExtratoMensal::body(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)
{
    Glib::RefPtr<Pango::Layout> layout = print_context->create_pango_layout();
    
    layout->set_font_description(Pango::FontDescription("Arial 10"));

    double current_y = 70;

    ExtratoMensal::get_itens(data_ini, data_fin, idbanco);

    for (auto itens = listItens->begin(); itens != listItens->end(); ++itens)
    {
        int current_x = 10;
        ExtratoMensal::fill_color(cr, current_y-2, current_x, 550, 11);

        //iditem
        layout->set_text(itens->get_iditem());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_RIGHT);
        cr->move_to(50, current_y);
        layout->show_in_cairo_context(cr);

        //data
        layout->set_text(itens->get_data());
        layout->set_width(100 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(80, current_y);
        layout->show_in_cairo_context(cr);

        //tipo
        layout->set_text(itens->get_tpbanc());
        layout->set_width(100 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(160, current_y);
        layout->show_in_cairo_context(cr);
        
        //valor
        layout->set_text(itens->get_valor());
        layout->set_width(50 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_RIGHT);
        cr->move_to(240, current_y);
        layout->show_in_cairo_context(cr);
        
        //historico
        layout->set_text(itens->get_item());
        layout->set_width(220 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(320, current_y);
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

    layout->set_text("Créditos");
    layout->set_width(20 * PANGO_SCALE);
    layout->set_alignment(Pango::ALIGN_LEFT);
    cr->move_to(20, current_y + 10);
    layout->show_in_cairo_context(cr);

    layout->set_text("Débitos");
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

    ExtratoMensal::get_totais_itens(data_ini, data_fin, idbanco);
    
    for (auto totais = listItens->begin(); totais != listItens->end(); ++totais)
    {
        layout->set_text(totais->get_creditos());
        layout->set_width(20 * PANGO_SCALE);
        layout->set_alignment(Pango::ALIGN_LEFT);
        cr->move_to(20, current_y + 10);
        layout->show_in_cairo_context(cr);

        layout->set_text(totais->get_debitos());
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

void ExtratoMensal::list_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring banco, std::list<Banco> *list_banco)
{
    data_ini = dataini;
    data_fin = datafin;
    idbanco = banco;
    listBanco = list_banco;
    
    Glib::RefPtr<Gtk::PageSetup> pagesetup =  Gtk::PageSetup::create();
    Gtk::PaperSize *papersize = new Gtk::PaperSize(Gtk::PAPER_NAME_A4, "A4", 595, 842, Gtk::UNIT_POINTS);

    pagesetup->set_paper_size(*papersize);
    
    set_default_page_setup(pagesetup);

    run();
}
