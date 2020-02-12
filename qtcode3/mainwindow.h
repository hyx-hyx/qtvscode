#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QProcess>
#include "codeedit.h"
#include <QPlainTextEdit>
#include <QMessageBox>
#include <qtreeview.h>
#include "highlighter.h"
#include"highlighterpython.h"
#include<QLineEdit>
#include<QLabel>
#include <qfilesystemmodel.h>
#include<windows.h>
#include<QWindow>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include <QTextCodec>
#include<QGroupBox>
#include<QRadioButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void setUpHighlighter();
    void doProcessTriggeredByGB18030();
    void doProcessTriggeredByUTF_8();
    void searchfile(CodeEdit *);
    void CreateButton();
    void showaddress(QString path);
    void widgetlayout(QWidget *widget);
    ~MainWindow();
    void CodeMove(CodeEdit *changearea);
    void newdebugwidget();
    void makejson();
    void LanguageLabel();
    void SavePath();
    void sethighlighter(CodeEdit *codehighlighter);
private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
    QVBoxLayout *layoutV;
    QHBoxLayout *layoutH;
    QMenuBar *myMenuBar;
    int width;
    int height;
    int charsize=14;//size为窗口文字的大小
    QMenu *file;
    QMenu *edit;
    QMenu *select;
    QMenu *view;
    QMenu *go;
    QMenu *debug;
    QMenu *terminal;
    QMenu *help;
    QFile *qssFile;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QPushButton *btn_3;
    QPushButton *btn_4;
    QPushButton *btn_5;

    QPushButton *file_1;
    QPushButton *file_2;

    CodeEdit *codeArea;
    CodeEdit *secondcode;
    QPlainTextEdit *editor;
    QAction *actionNewWindow;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionOpenDir;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionPast;
    QAction *actionCopy;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *actionSelectAll;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actioncharbig;
    QAction *actioncharsmall;
    QAction *actionOpenRecent;
    QAction *actioncompile;
    //状态栏
    QPushButton *statuinform;
    QPushButton *statufeedback;
    QLabel *statumode;
    QPushButton *statuend;
    QPushButton *statucharcode;
    QPushButton *statuspace;
    QPushButton *statutorow=new QPushButton(this);
    QPushButton *statuerror;
    QPushButton *statuwarn;
    QPushButton *statuselect;
    //转到行
    QLineEdit *tolineedit;
    QTextCursor *cursor;
    QString s;
    QLabel *skip;
    int inte;
    //换肤
    QPushButton *change;

    //搜索
    QString filename;
    QString tosearch;
    QLineEdit *search;
    QPushButton *searchpush=new QPushButton(this);
    //字符编码集
     QDialog *dialog;
     QLayout *dialoglayout;
     QMenuBar *dialogbar;
     int charcode=1;
     //显示最近打开的文件
     int count=0;
     QDialog *recentfile_dialog;
     //语言模式
     QString suffix;
     //添加地址栏
     QLabel *address;
     //资源管理器
     QFileSystemModel m_dir_model;
     QTreeView *m_resource_tree;
     QListView *m_current_listview;
     QDialog *side;
     
     //pdf查看器
     QAction *action_pdf;

     //集成终端:实现简单编译
     QProcess compile;
     QString title;
     bool compilebool;
     bool savebool;
     QString strTemp;//编译信息

     //实现断点，简单调试功能
     QAction *action_debug;
     QProcess debugger;
     QWidget *debugewidget;
     QLineEdit *debuglineedit;
     QTextEdit *textedit;
     QPushButton *SetBreakpoint;

     //集成git
     QProcess git;
     QAction *action_git;
     QProcess pdf;

     //多窗口文件的显示
     Highlighterpython *highlighterpython;
     int focus=1;
public slots:
    void openFile();
    void saveFile();
    void lineedit();
    void to();
    void changetheme();
    void searchlineedit();
    void searchclose();
    void showcharmodedialog();
    void smaller();
    void bigger();
    void recentshow();
    void do_cursorChanged();
    void button_clicked();
    void makecompile();
    void makedebug();
    void SecondCodeFocus();
    void CodeAreaFocus();
    void breakpoint();
    void gitinit();
    void openpdf();
    void UpdateCurrentTab(const QModelIndex&);
signals:
    void buttonclick();
};

#endif // MAINWINDOW_H
