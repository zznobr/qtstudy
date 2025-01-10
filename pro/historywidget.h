#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>

namespace Ui {
class historyWidget;
}

class historyWidget : public QWidget
{
    Q_OBJECT

public:

    void readHistoryToTextEdit();
    void writeStringToHistory(QString content);
    void clearHistoryFile();

    void language(QString str);

    explicit historyWidget(QWidget *parent = nullptr);
    ~historyWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::historyWidget *ui;
};

#endif // HISTORYWIDGET_H
