#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "keyboard.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* obj, QEvent* ev);

private:
    Ui::MainWindow *ui;
    keyboard* key;
};
#endif // MAINWINDOW_H
