// You may need to build the project (run Qt uic code generator) to get "ui_Editor.h" resolved

#include <Editor.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QPushButton>
#include "ui_Editor.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Editor), _button(nullptr) {
    ui->setupUi(this);
}

Editor::~Editor() {
    delete ui;
}

void    Editor::newDocument() {
    _currentFile.clear();
    ui->TextEditor->setText(QString());
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
    ui->TextEditor->setText(text);
    file.close();
}

void Editor::openFolder() {
    QString folderName = QFileDialog::getExistingDirectory(this, "Open folder");
    if (folderName.isEmpty())
        return;
    QDir directory(folderName);
    QStringList elements = directory.entryList(QStringList(),QDir::AllEntries);

    int idx = 0;
    if (_button != nullptr) {
        while (auto& button = _button[idx]) {
            delete button;
            idx++;
        }
        delete _button;
        ui->ScrollBar->setLayout(ui->FileMenu);
        ui->ScrollBar->setVisible(true);
    }

    _button = new QPushButton*[elements.size() + 1 - 2];
    idx = 0;

    for (auto& element : elements) {
        if (idx < 2) {
            idx++;
            continue;
        }
        _button[idx - 2] = new QPushButton(element);
        _button[idx - 2]->setMinimumHeight(10);
        ui->FileMenu->addWidget(_button[idx++ - 2]);
    }

    _button[idx - 2] = nullptr;
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
    QString text = ui->TextEditor->toPlainText();
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
    QString text = ui->TextEditor->toPlainText();
    out << text;
    file.close();
}