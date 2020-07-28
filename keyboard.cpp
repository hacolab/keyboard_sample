#include "keyboard.h"
#include "ui_keyboard.h"

#include <QCoreApplication>
#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
#include <QDebug>


static QString chars[12]= {
    "1234567890-^",
    "qwertyuiop@[",
    "asdfghjkl+*]",
    "zxcvbnm,./\\ "
};

keyboard::keyboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);
    QSize size = QSize(55, 45);
    for (int i=0; i<4; i++) {
        for (int j=0; j<12; j++) {
            QPushButton *btn = new QPushButton(this);
            btn->setText(chars[i].at(j));
            btn->setFocusPolicy(Qt::NoFocus);
            btn->setFixedSize(size);
            ui->gridLayout->addWidget(btn, i, j);
            connect(btn, SIGNAL(pressed()), this, SLOT(virtualKeyPressed()));
            connect(btn, SIGNAL(released()), this, SLOT(virtualKeyReleased()));
        }
    }
    parent->setWindowFlags(Qt::WindowStaysOnTopHint);
    parent->setLayout(ui->gridLayout);
    //this->setFocusPolicy(Qt::NoFocus);
    this->clearFocus();
}


keyboard::~keyboard()
{
    delete ui;
}

/**
 * @brief keyboard::setInputTarget
 * @param lineEdit
 */
void keyboard::setInputTarget(QLineEdit* lineEdit)
{
    this->target = lineEdit;
    connect(lineEdit, SIGNAL(returnPressed()), qApp->inputMethod(), SLOT(hide()));
}

/**
 * @brief keyboard::keyPushed
 * @param b
 */
void keyboard::virtualKeyPressed()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());
    //char c = button->text()->at(0);
    qDebug() << "PUSH:" << button->text();
    //QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
    //this->target->parentWidget()->activateWindow();
    //this->target->setFocus();
    //QCoreApplication::postEvent(this->target->parentWidget(), event);
    //QApplication::sendEvent(this->target->parentWidget(), event);
    //QApplication::sendEvent(QGuiApplication::focusObject(), event);
    emitKey(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
}

void keyboard::virtualKeyReleased()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());
    qDebug() << "RELEASE:" << button->text();
    //QKeyEvent* event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_A, Qt::NoModifier);
    //QApplication::sendEvent(this->target->parentWidget(), event);
    //QApplication::sendEvent(QGuiApplication::focusObject(), event);
    emitKey(QEvent::KeyRelease, Qt::Key_A, Qt::NoModifier);
}

void keyboard::emitKey(QEvent::Type type, Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    //QWidget* receiver = qobject_cast<QWidget*>(QGuiApplication::focusObject());
    QWidget* receiver = this->target;
    qDebug() << "REC:" << receiver->window();
    if(!receiver) {
        return;
    }
    QKeyEvent event = QKeyEvent(type, key, modifiers, QKeySequence(key).toString());
    QCoreApplication::sendEvent(receiver, &event);
}

