#include <Editor.h>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication Application(argc, argv);
    Editor MainWindow;
    MainWindow.show();
    return QApplication::exec();
}