#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QLineEdit>
#include <QDialog>
#include <QEvent>

namespace Ui {
class keyboard;
}

class keyboard : public QDialog
{
    Q_OBJECT

public:
    explicit keyboard(QWidget *parent = nullptr);
    ~keyboard();
    void setInputTarget(QLineEdit* lineEdit);

public slots:
    void virtualKeyPressed();
    void virtualKeyReleased();

private:
    Ui::keyboard *ui;
    QLineEdit* target;

    //void emitKey(Qt::Key key);
    void emitKey(QEvent::Type type, Qt::Key key, Qt::KeyboardModifiers modifiers);
};

#endif // KEYBOARD_H
