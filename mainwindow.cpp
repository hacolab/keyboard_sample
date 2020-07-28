#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyboard.h"

#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    key = new keyboard(this);
    key->setInputTarget(ui->lineEdit);
    key->show();
    this->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::eventFilter(QObject* obj, QEvent* ev)
{
    if (ev->type() == QEvent::KeyPress || ev->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(ev);
        qDebug() << "TYPE:" << ev->type() << "KEY:" << keyEvent->key() << "MOD:" << keyEvent->modifiers();
        return false;
    }
    else {
        qDebug() << "MEV:" << ev->type();
        return false;
    }
}
