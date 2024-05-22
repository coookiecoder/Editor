#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow {
Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);

    ~Editor() override;

private slots:
    void    on_actionNew_triggered() {newDocument();};
    void    on_actionOpen_triggered() {open();};
    void    on_actionSave_triggered() {save();};
    void    on_actionSave_as_triggered() {saveAs();};
    void    on_actionOpen_folder_triggered() {openFolder();};

private:
    Ui::Editor* ui;
    QString     _currentFile;

    void    newDocument();
    void    open();
    void    openFolder();
    void    save();
    void    saveAs();
};