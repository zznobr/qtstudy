#include "testedit.h"
#include "ui_testedit.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextBlock>
#include <QTextLayout>
#include <QTextCursor>


testEdit::testEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::testEdit)
{
    ui->setupUi(this);
    //调用Window剪切板
    is_selected = false;
    rowNumber=0;columNumber=0;
    clipboard = QApplication::clipboard();
    //Dialog一次创建多次显示
    about = new aboutDialog(this);
    search = new searchDialog(this);
    replace = new replaceDialog(this);
    cursor = ui->textEdit->textCursor();
    //光标移动时状态栏显示
    connect(ui->textEdit,&QTextEdit::cursorPositionChanged,this,&testEdit::cursorChange);

    //about窗口
    about->setModal(true);
    connect(ui->actionAbout,&QAction::triggered,[=](){
        about->show();
    });

    //替换与查找
    connect(this->search,&searchDialog::return_cursor_position,this,&testEdit::search_and_replace);
    connect(this->replace,&replaceDialog::return_cursor_position,this,&testEdit::search_and_replace);

    //查找窗口
    search->setModal(false);
    connect(ui->actionSearch,&QAction::triggered,[=](){
        search->getText(ui->textEdit->toPlainText().toUtf8());
        search->show();
        // ui->textEdit->setReadOnly(true);
    });

    replace->setModal(false);
    // 替换窗口
    connect(ui->actionReplace,&QAction::triggered,[=](){
        replace->getText(ui->textEdit->toPlainText().toUtf8());
        replace->show();
        // ui->textEdit->setReadOnly(true);
    });

    //全部替换
    connect(this->replace,&replaceDialog::replace_all,[=](QString target,QString replace_word){
        QString text = ui->textEdit->toPlainText().toUtf8();
        text.replace(target,replace_word);
        ui->textEdit->setPlainText(text);
    });

    // connect(this->search,&searchDialog::unlock_textEdit,[=](){
    //     ui->textEdit->setReadOnly(false);
    // });

    connect(ui->textEdit,&QTextEdit::textChanged,[=](){
        search->getText(ui->textEdit->toPlainText().toUtf8());
        replace->getText(ui->textEdit->toPlainText().toUtf8());
    });


    connect(ui->actionNew,&QAction::triggered,this,&testEdit::action_new_file);//新建
    connect(ui->actionOpen,&QAction::triggered,this,&testEdit::action_open_file);//打开
    connect(ui->actionSave,&QAction::triggered,this,&testEdit::action_save_file);//保存
    connect(ui->actionSaveOther,&QAction::triggered,this,&testEdit::action_saveOther_file);//另存为
    connect(ui->textEdit,&QTextEdit::copyAvailable,[=](bool is_selected){
        this->is_selected = is_selected;
        // qDebug()<<is_selected;
    });
    //复制
    connect(ui->actionCopy,&QAction::triggered,[=](){
        if(!is_selected){
            // qDebug()<<"没有选中文本";
            ui->statusbar->showMessage("没有选中文本");
        }
        else{
            QString selected_text = ui->textEdit->textCursor().selectedText();
            clipboard->setText(selected_text);
            // qDebug()<<clipboard->text();
        }
    });
    //剪切
    connect(ui->actionCut,&QAction::triggered,[=](){
        if(!is_selected){
            ui->statusbar->showMessage("没有选中文本");
        }
        else{
            clipboard->setText(ui->textEdit->textCursor().selectedText());
            ui->textEdit->textCursor().removeSelectedText();
        }
    });
    //粘贴
    connect(ui->actionPaste,&QAction::triggered,[=](){
        cursor.insertText(clipboard->text());
    });
    //全选
    connect(ui->actionAll,&QAction::triggered,[=](){
        ui->textEdit->selectAll();
    });
    //撤销
    connect(ui->actionBefore,&QAction::triggered,[=](){
        ui->textEdit->undo();
    });
    //恢复
    connect(ui->actionBefore,&QAction::triggered,[=](){
        ui->textEdit->redo();
    });

    //字体
    connect(ui->actionFont,&QAction::triggered,[=](){
        bool ok = false;
        QFont font = QFontDialog::getFont(&ok);
        if(ok)
            ui->textEdit->setFont(font);
    });

    //颜色
    connect(ui->actionColor,&QAction::triggered,[=](){
        QColor color = QColorDialog::getColor();
        if(color.isValid()){
            QPalette palette = ui->textEdit->palette();
            palette.setColor(QPalette::Text,color);
            ui->textEdit->setPalette(palette);
        }
    });

    //背景色
    connect(ui->actionBackgroundColor,&QAction::triggered,[=](){
        QColor color = QColorDialog::getColor();
        if(color.isValid()){
            QString colorStyle = QString("background-color: rgb(%1, %2, %3);").arg(color.red()).arg(color.green()).arg(color.blue());
            ui->textEdit->setStyleSheet(colorStyle);
        }
    });
}

testEdit::~testEdit()
{
    delete ui;
}

//关闭窗口保存文件
void testEdit::closeEvent(QCloseEvent *event)
{
    action_saveOther_file();
    event->accept();
}

void testEdit::resizeEvent(QResizeEvent *event)
{
    emit this->cursorChange();
    event->accept();
}
//新建文件
void testEdit::action_new_file()
{
    qDebug()<<"new";
    bool is_save = true;
    if(!openFilePath.isEmpty()||!ui->textEdit->toPlainText().isEmpty()){
        if(QMessageBox::question(this,"当前文本尚未保存","是否保存当前文本")==QMessageBox::Yes){
            emit is_save = action_save_file();
            if(is_save)
                qDebug()<<"文件已保存";
        }
        else{
            is_save = false;
        }
    }
    if(is_save){
        ui->textEdit->clear();
        openFilePath.clear();
        saveFilePath.clear();
    }
}

//打开文件
void testEdit::action_open_file()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this,"打开文件");
    // qDebug()<<filePath[0];
    if(filePaths.size()==1&&filePaths[0].right(4)==".txt"){
        openFilePath = filePaths[0];
        QFile file(openFilePath);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败!";
        }
        else{
            QTextStream textContent(&file);
            ui->textEdit->clear();
            ui->textEdit->setText(textContent.readAll());
            file.close();
        }
    }
    else{
        qDebug()<<"没有文件被打开 or 只支持打开一个文件 or 只支持编辑txt文件";
    }
}

//保存文件
bool testEdit::action_save_file()
{
    if(openFilePath.isEmpty()){
        QStringList filePaths = QFileDialog::getOpenFileNames(this,"请选择保存到文件路径");
        if(filePaths.size()==1&&filePaths[0].right(4)==".txt"){
            openFilePath = filePaths[0];
        }
    }
    if(openFilePath.right(4)==".txt"){
        saveFilePath = openFilePath;
        QFile file(saveFilePath);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"保存路径有误";
            return false;
        }
        else{
            // qDebug()<<ui->textEdit->toPlainText();
            file.write(ui->textEdit->toPlainText().toUtf8());
            return true;
        }
    }
    return false;
}

//另存为
void testEdit::action_saveOther_file()
{
    QFileDialog::saveFileContent(ui->textEdit->toPlainText().toUtf8(),"text.txt");
}

//光标改变
void testEdit::cursorChange()
{
    cursor = ui->textEdit->textCursor();
    columNumber = cursor.position()-cursor.block().position();
    rowNumber = cursor.block().layout()->lineForTextPosition(columNumber).lineNumber()+cursor.block().firstLineNumber()+1;
    QString statusMessage = QString("当前行数:%1, 当前列数:%2").arg(rowNumber).arg(columNumber);
    ui->statusbar->showMessage(statusMessage);
}


//隐藏显示工具栏
void testEdit::on_actionToolBar_triggered()
{
    if(ui->toolBar->isHidden())
        ui->toolBar->show();
    else
        ui->toolBar->hide();
}

//隐藏显示状态栏
void testEdit::on_actionStatusBar_triggered()
{
    if(ui->statusbar->isHidden())
        ui->statusbar->show();
    else
        ui->statusbar->hide();
}

//开启关闭自动换行
void testEdit::on_actionReturnLine_triggered()
{
    QTextOption::WrapMode wrap = ui->textEdit->wordWrapMode();
    if(wrap == QTextOption::WrapAtWordBoundaryOrAnywhere)
        ui->textEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);
    else
        ui->textEdit->setWordWrapMode(QTextOption::WrapMode::WrapAtWordBoundaryOrAnywhere);
}

void testEdit::search_and_replace(int position, int length, QString replace_word, bool is_replace)
{
    qDebug()<<position<<length<<replace_word;
    // ui->textEdit->textCursor().setPosition(position);
    // ui->textEdit->textCursor().setPosition(position+length,QTextCursor::KeepAnchor);
    cursor.setPosition(position);
    cursor.setPosition(position+length,QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(cursor);
    if(is_replace){
        ui->textEdit->textCursor().removeSelectedText();
        ui->textEdit->textCursor().insertText(replace_word);
    }
    qDebug()<<ui->textEdit->textCursor().position();
    emit cursorChange();
}



void testEdit::on_actionShowLine_triggered(bool checked)
{
    ;
}

