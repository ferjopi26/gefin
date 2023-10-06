#include "mainwindow.h"
#include <locale.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.gefin");

    setlocale(LC_NUMERIC, "C");

    auto mainwindow = new MainWindow();

    Gtk::Window * window = mainwindow->getWindow();

    return app->run(*window);
}
