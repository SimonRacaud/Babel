#include <QApplication>
#include "gui/Window/Window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI::Window win;
    win.show();

    return app.exec();
}