#ifndef TESTEDIT_H
#define TESTEDIT_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QClipboard>
#include <QTextCursor>
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class testEdit;
}
QT_END_NAMESPACE

class testEdit : public QMainWindow
{
    Q_OBJECT

public:
    testEdit(QWidget *parent = nullptr);
    ~testEdit();
    QString openFilePath;
    QString saveFilePath;
    aboutDialog *about;
    searchDialog *search;
    replaceDialog *replace;
    QClipboard *clipboard;
    QTextCursor cursor;
    bool is_selected;
    int rowNumber;
    int columNumber;

    void closeEvent(QCloseEvent *event);  //关闭窗口提示保存
    void resizeEvent(QResizeEvent *event);  //更改窗口大小改变光标位置

private:
    Ui::testEdit *ui;

signals:

private slots:
    void action_new_file(); //新建文件
    void action_open_file();  //打开文件
    bool action_save_file();  //保存文件
    void action_saveOther_file();  //另存为
    void cursorChange();  //光标位置改变

    void on_actionToolBar_triggered();
    void on_actionStatusBar_triggered();
    void on_actionReturnLine_triggered();

    //替换与查找
    void search_and_replace(int position,int length,QString replace_word,bool is_replace);
    void on_actionShowLine_triggered(bool checked);
};
#endif // TESTEDIT_H
