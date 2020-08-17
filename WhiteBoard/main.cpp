#include <QApplication>

#include "controlpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ControlPanel controPanel;
    controPanel.move(QApplication::desktop()->width() / 2 - controPanel.width() / 2,
                     QApplication::desktop()->height() - 150);
    controPanel.show();
    return a.exec();
}
