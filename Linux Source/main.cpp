#include "class.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("DDCal");
    Window window;
    window.resize(610,520);
    window.show();
    return app.exec();
}
