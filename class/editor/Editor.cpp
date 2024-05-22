// You may need to build the project (run Qt uic code generator) to get "ui_Editor.h" resolved

#include <Editor.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringListModel>
#include <QFileSystemModel>
#include "ui_Editor.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Editor) {
    ui->setupUi(this);
}

Editor::~Editor() {
    delete ui;
}

void    Editor::newDocument() {
    _currentFile.clear();
    ui->textEdit->setText(QString());
}

void Editor::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    _currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Editor::openFolder() {
    QString folderName = QFileDialog::getExistingDirectory(this, "Open folder");
    if (folderName.isEmpty())
        return;
    QDir directory("Pictures/MyPictures");
    QStringList images = directory.entryList(QStringList() << "*",QDir::Files);
}

void Editor::save() {
    QString fileName;
    if (_currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        _currentFile = fileName;
    } else {
        fileName = _currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Editor::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    _currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}