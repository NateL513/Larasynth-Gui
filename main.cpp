#include "training.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Training w;
    w.show();
    return a.exec();
}
