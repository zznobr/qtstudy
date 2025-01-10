#include <QLineEdit>
#include <QMouseEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit();
    MyLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit clicked();
        }
        QLineEdit::mousePressEvent(event);
    }
};
