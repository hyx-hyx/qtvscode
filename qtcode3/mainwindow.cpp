#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCheckBox>
#define StartMenu "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,670);
    this->setWindowTitle("Qt Code"); 
    width=this->geometry().width();
    height=this->geometry().height();
    this->setWindowIcon(QPixmap(":/img/logo.png"));
    myMenuBar=new QMenuBar(this);
    //增加菜单栏
    file=myMenuBar->addMenu(tr("文件(&F)"));
    edit=myMenuBar->addMenu(tr("编辑(&E)"));
    select=myMenuBar->addMenu(tr("选择(&S)"));
    view=myMenuBar->addMenu(tr("查看(&V)"));
    go=myMenuBar->addMenu(tr("转到(&G)"));
    debug=myMenuBar->addMenu(tr("调试(&D)"));
    terminal=myMenuBar->addMenu(tr("终端(&T)"));
    help=myMenuBar->addMenu(tr("帮助(&H)"));
    //细分菜单栏
    actionNew=file->addAction(tr("新建文件"));
    actionNewWindow=file->addAction(tr("新建窗口"));
    actionNew->setShortcut(QKeySequence("Ctrl+N"));
    actionNewWindow->setShortcut(QKeySequence("Ctrl+Shift+N"));
    file->addSeparator();
    actionOpen=file->addAction(tr("打开文件"));
    actionOpenDir=file->addAction(tr("打开文件夹"));
    actionOpen->setShortcut(QKeySequence("Ctrl+O"));
    actionOpenDir->setShortcut(QKeySequence("Ctrl+Shift+O"));
    actionOpenRecent=file->addAction(tr("显示最近的文件"));
    actionSave=file->addAction(tr("保存"));
    actionSave->setShortcut(QKeySequence("Ctrl+S"));
    file->addSeparator();

    actionUndo=edit->addAction(tr("撤销"));
    actionRedo=edit->addAction(tr("恢复"));
    actionCut=edit->addAction(tr("剪切"));
    actionCopy=edit->addAction(tr("复制"));
    actionPast=edit->addAction(tr("粘贴"));
    actionUndo->setShortcut(QKeySequence("Ctrl+Z"));
    actionRedo->setShortcut(QKeySequence("Ctrl+Y"));
    actionCut->setShortcut(QKeySequence("Ctrl+X"));
    actionCopy->setShortcut(QKeySequence("Ctrl+C"));
    actionPast->setShortcut(QKeySequence("Ctrl+V"));

    //放大、缩小按钮
    actioncharbig=view->addAction(tr("放大"));
    actioncharbig->setShortcut(tr("Ctrl+="));
    actioncharsmall=view->addAction(tr("缩小"));
    actioncharsmall->setShortcut(tr("Ctrl+-"));

    //按钮点击
    connect(this->actionOpen,&QAction::triggered,this,&MainWindow::openFile);
    connect(this->actionSave,&QAction::triggered,this,&MainWindow::saveFile);
    //侧边栏
    btn_1=new QPushButton(this);
    btn_1->setStyleSheet("QPushButton{border-image:url(:/img/file_1.png);}QPushButton:hover{border-image:url(:/img/file.png);}");
    btn_1->resize(33,33);
    btn_1->move(14,45);
    btn_2=new QPushButton(this);
    btn_2->setStyleSheet("QPushButton{border-image:url(:/img/search_1.png);}QPushButton:hover{border-image:url(:/img/search.png);}");
    btn_2->resize(33,33);
    btn_2->move(14,95);
    btn_3=new QPushButton(this);
    btn_3->setStyleSheet("QPushButton{border-image:url(:/img/git_1.png);}QPushButton:hover{border-image:url(:/img/git.png);}");
    btn_3->resize(33,33);
    btn_3->move(14,155);
    btn_4=new QPushButton(this);
    btn_4->setStyleSheet("QPushButton{border-image:url(:/img/bug_1.png);}QPushButton:hover{border-image:url(:/img/bug.png);}");
    btn_4->resize(33,33);
    btn_4->move(14,215);
    btn_5=new QPushButton(this);
    btn_5->setStyleSheet("QPushButton{border-image:url(:/img/app_1.png);}QPushButton:hover{border-image:url(:/img/app.png);}");
    btn_5->resize(33,33);
    btn_5->move(14,275);

    //多窗口文件显示:第一个窗口
    file_1=new QPushButton(this);
    file_1->setStyleSheet(tr("QPushButton{border:0px;border-color:rgb(33,33,33);border-bottom:2px solid blue;background-color:rgb(33,33,33);color:white;font:bold;}"));
    file_1->setText("Untitled");
    file_1->setFont(QFont("等线",10));
    file_1->resize(140,25);
    file_1->move(250,39);
    connect(file_1,&QPushButton::clicked,this,&MainWindow::CodeAreaFocus);

    //多窗口文件显示:第二个窗口
    file_2=new QPushButton(this);
    file_2->setStyleSheet(tr("QPushButton{border:0px;border-color:rgb(33,33,33);border-bottom:2px solid blue;background-color:rgb(33,33,33);color:white;font:bold;}"));
    file_2->setText("Untitled");
    file_2->setFont(QFont("等线",10));
    file_2->resize(140,25);
    file_2->move(390,39);
    connect(file_2,&QPushButton::clicked,this,&MainWindow::SecondCodeFocus);

    //代码文本编辑区
    codeArea=new CodeEdit(this);
    codeArea->resize(geometry().width()-60,geometry().height()-90);
    codeArea->move(250,65);
    highlighter=new Highlighter(codeArea->document());

    //qss样式文件读取
    qssFile = new QFile(":/default.qss", this);
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
    myMenuBar->setGeometry(QRect(0,0,1920,35));
    file->resize(38,35);

    //状态栏
    statusBar()->setStyleSheet(styleSheet);
    statusBar()->setSizeGripEnabled(false);

    statuinform=new QPushButton(this);
    statuerror=new QPushButton(this);
    statuwarn=new QPushButton(this);
    statuend=new QPushButton(this);
    statumode=new QLabel(this);
    statucharcode=new QPushButton(this);
    statuspace=new QPushButton(this);
    statufeedback=new QPushButton(this);
    statuselect=new QPushButton(this);

    statuerror->setText("错误:");
    statuwarn->setText("警告:");
    statuinform->setText("通知");
    statufeedback->setText("反馈");
    statuend->setText("CRLF");
    statumode->setText("C++");
    statuspace->setText("空格:");
    statutorow->setText("行0,列0");
    statucharcode->setText("UTF-8");
    statuselect->setText("Win32");
    QFrame *frame=new QFrame(this);
    frame->setFrameShape(QFrame::NoFrame);

    QString *statubarstyle=new QString(tr("QPushButton{background-color: purple;color:white;border:0px}QLabel{color:white;}"));
    statuinform->setStyleSheet(*statubarstyle);
    statuerror->setStyleSheet(*statubarstyle);
    statuwarn->setStyleSheet(*statubarstyle);
    statuend->setStyleSheet(*statubarstyle);
    statutorow->setStyleSheet(*statubarstyle);
    statuspace->setStyleSheet(*statubarstyle);
    statumode->setStyleSheet(*statubarstyle);
    statufeedback->setStyleSheet(*statubarstyle);
    statucharcode->setStyleSheet(*statubarstyle);
    statuselect->setStyleSheet(*statubarstyle);

    ui->statusBar->addPermanentWidget(statuerror);
    ui->statusBar->addPermanentWidget(statuwarn);
    ui->statusBar->addPermanentWidget(statutorow);
    ui->statusBar->addPermanentWidget(statuspace);
    ui->statusBar->addPermanentWidget(statucharcode);
    ui->statusBar->addPermanentWidget(statuend);
    ui->statusBar->addPermanentWidget(statumode);
    ui->statusBar->addPermanentWidget(statuselect);
    ui->statusBar->addPermanentWidget(statufeedback);
    ui->statusBar->addPermanentWidget(statuinform);

    //转到行
    statutorow->setShortcut(QKeySequence("Ctrl+G"));
    connect(statutorow,&QPushButton::clicked,this,&MainWindow::lineedit);

    //换肤
    change=new QPushButton(this);
    change->setText("换肤");
    change->move(this->geometry().width()-200,0);
    connect(change,&QPushButton::clicked,this,&MainWindow::changetheme);

    //搜索栏
    searchpush->setShortcut(QKeySequence("Ctrl+F"));
    connect(searchpush,&QPushButton::clicked,this,&MainWindow::searchlineedit);

    //地址栏
    address=new QLabel(this);

    //字符编码集
    dialog=new QDialog(this);
    dialog->setWindowFlag(Qt::FramelessWindowHint);
    dialog->resize(150,1);
    dialoglayout=new QHBoxLayout(dialog);
    dialogbar=new QMenuBar(dialog);
    QAction *utf=dialogbar->addAction(tr("UTF-8"));
    QAction *GB=dialogbar->addAction(tr("GB"));
    dialoglayout->setMenuBar(dialogbar);
    connect(statucharcode,&QPushButton::clicked,this,&MainWindow::showcharmodedialog);
    connect(utf,&QAction::triggered,this,&MainWindow::doProcessTriggeredByUTF_8);
    connect(GB,&QAction::triggered,this,&MainWindow::doProcessTriggeredByGB18030);

    //语言显示标签 内嵌到void Mainwindow::openfile中

    //实现窗口文字的放大缩小
    connect(actioncharbig,&QAction::triggered,this,&MainWindow::bigger);
    connect(actioncharsmall,&QAction::triggered,this,&MainWindow::smaller);

    //显示最近打开的文件
    recentfile_dialog=new QDialog(this);
    recentfile_dialog->resize(700,300);
    connect(actionOpenRecent,&QAction::triggered,this,&MainWindow::recentshow);

    //状态栏:动态显示行列号
    connect(codeArea,SIGNAL(cursorPositionChanged()),this,SLOT(do_cursorChanged()));


    //资源管理器
    QLabel *resource=new QLabel(this);
    resource->setText("资源管理器");
    resource->setStyleSheet("QLabel{background-color:rgb(33,33,33);color:white;}");
    resource->move(60,40);
    resource->resize(190,25);

    m_resource_tree=new QTreeView(this);
    m_resource_tree->resize(190,this->geometry().height()-85);
    m_resource_tree->move(60,60);
    m_dir_model.setRootPath(QDir::currentPath());
    m_dir_model.setReadOnly(true);
    m_resource_tree->setModel(&m_dir_model);
    m_resource_tree->setRootIndex(m_dir_model.index(QDir::currentPath()));
    connect(m_resource_tree,SIGNAL(clicked(QModelIndex)),this,SLOT(UpdateCurrentTab(const QModelIndex&)));

    //集成文档查看器
    action_pdf=view->addAction("pdf查看器");
    connect(action_pdf,&QAction::triggered,this,&MainWindow::openpdf);

    //集成终端，实现简单编译功能
    actioncompile=debug->addAction("编译");
    connect(actioncompile,&QAction::triggered,this,&MainWindow::makecompile);

    //实现断点，简单调试功能
    action_debug=debug->addAction("调试");
    connect(action_debug,&QAction::triggered,this,&MainWindow::makedebug);

    //集成git
    action_git=debug->addAction("Git");
    connect(action_git,&QAction::triggered,this,&MainWindow::gitinit);

    //json保存简单配置：放在makejson函数中。

    //多窗口文件的显示
    secondcode=new CodeEdit(this);
    secondcode->resize(geometry().width(),geometry().height()-90);
    secondcode->move(250,65);
}

void MainWindow::setUpHighlighter(){
  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(20);
  this->codeArea->setFont(font);
  this->codeArea->setTabStopWidth(fontMetrics().width(QLatin1Char('9'))*4);
  //highlighter=new Highlighter(this->codeArea->document());
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(QColor(33,33,33));
    painter.setBrush(brush);
    painter.fillRect(QRect(0,35,60,1500),QBrush(brush));
    painter.fillRect(QRect(60,35,2000,30),QBrush(brush));
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->codeArea->resize(this->geometry().width()-60,this->geometry().height()-90);
    this->secondcode->resize(this->geometry().width()-60,this->geometry().height()-90);
    this->change->move(this->geometry().width()-200,0);
    this->m_resource_tree->resize(190,this->geometry().height()-85);
    this->address->resize(this->geometry().width()-250,35);
}


/////////////slots///////////////////
void MainWindow::openFile(){
    filename=QFileDialog::getOpenFileName(this,"打开文件",".","Text(*.cpp *.h *.txt *.py *.java *.c *.html)");
    if(filename.isEmpty())
        return;
    QStringList list=filename.split("/");
    title=list.at(list.length()-1);
    if(focus==1)
    {
        this->file_1->setText(title);
        this->codeArea->fileName=filename;
        this->codeArea->myFile->setFileName(filename);
        bool ret=this->codeArea->myFile->open(QIODevice::ReadWrite);
        if(!ret)
        {
            QMessageBox::warning(this,"文件失败","打开失败");
        }
        QTextStream stream(this->codeArea->myFile);
        if(charcode==1){
            this->codeArea->codeName="UTF-8";}
        else{
            this->codeArea->codeName="GB18030";
        }
        stream.setCodec(this->codeArea->codeName.toLocal8Bit().data());
        this->codeArea->setPlainText(stream.readAll());
        this->codeArea->myFile->close();

        //为显示地址栏，需将文本框重排版
        CodeMove(codeArea);

        //更改地址栏
        showaddress(filename);

        //设置高亮
        sethighlighter(codeArea);

        codeArea->setHidden(false);
        secondcode->setHidden(true);

    }
    else
    {
        this->file_2->setText(title);
        this->secondcode->fileName=filename;
        this->secondcode->myFile->setFileName(filename);
        bool ret=this->secondcode->myFile->open(QIODevice::ReadWrite);
        if(!ret)
        {
            QMessageBox::warning(this,"文件失败","打开失败");
        }
        QTextStream stream(this->secondcode->myFile);
        if(charcode==1){
            this->secondcode->codeName="UTF-8";}
        else{
            this->secondcode->codeName="GB18030";
        }
        stream.setCodec(this->secondcode->codeName.toLocal8Bit().data());
        this->secondcode->setPlainText(stream.readAll());
        this->secondcode->myFile->close();

        //为显示地址栏，需将文本框重排版
        CodeMove(secondcode);

        //更改地址栏
        showaddress(filename);

        //设置高亮
        sethighlighter(secondcode);

        codeArea->setHidden(true);
        secondcode->setHidden(false);
    }

    //将路径存入txt文件中
    SavePath();

    //语言模式
    LanguageLabel();
}
void MainWindow::sethighlighter(CodeEdit *codehighlighter){
    if(suffix=="py")
    {
        highlighterpython = new Highlighterpython(codehighlighter->document());
    }
    if(suffix=="c"||suffix=="cpp")
    {
        highlighter=new Highlighter(codehighlighter->document());
    }
}

void MainWindow::LanguageLabel()
{
    QStringList getsuffix=title.split(".");
    suffix=getsuffix.at(getsuffix.length()-1);
    if(suffix=="txt"){ statumode->setText("纯文本"); }
    if(suffix=="c"){ statumode->setText("C"); }
    if(suffix=="java"){ statumode->setText("Java"); }
    if(suffix=="html"){ statumode->setText("HTML"); }
    if(suffix=="py"){ statumode->setText("Python"); }
}
void MainWindow::SavePath()
{
    QString AppPath=QCoreApplication::applicationDirPath();
    AppPath.append("/address.exe");
    QFile file(AppPath);
    QTextStream *filestream=new QTextStream(&file);
    if(!file.exists())
    {
       count++;
       file.open(QIODevice::ReadWrite|QIODevice::Text);
       *filestream<<filename<<endl;
       file.close();
    }
    else
    {
       count++;
       file.open(QIODevice::Append|QIODevice::Text);
       *filestream<<filename<<endl;
       file.close();
    }
}
void MainWindow::saveFile()
{
    if(focus==1){
    if(this->codeArea->fileName.isEmpty())
    {
        QString filename=QFileDialog::getSaveFileName(this,"保存",".","*.txt *.cpp *.h *.py *.java *.c *.html");
        this->codeArea->fileName=filename;
    }
    this->codeArea->myFile->setFileName(this->codeArea->fileName);
    this->codeArea->myFile->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(this->codeArea->myFile);
    stream.setCodec(this->codeArea->codeName.toLocal8Bit().data());
    stream<<this->codeArea->toPlainText();
    stream.flush();
    this->codeArea->myFile->close();
    if(!this->codeArea->fileName.isEmpty())
        QMessageBox::information(this,"成功","保存成功！");
    }
    else
    {
        if(this->secondcode->fileName.isEmpty())
        {
            QString filename=QFileDialog::getSaveFileName(this,"保存",".","*.txt *.cpp *.h *.py *.java *.c *.html");
            this->secondcode->fileName=filename;
        }
        this->secondcode->myFile->setFileName(this->secondcode->fileName);
        this->secondcode->myFile->open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream(this->secondcode->myFile);
        stream.setCodec(this->secondcode->codeName.toLocal8Bit().data());
        stream<<this->secondcode->toPlainText();
        stream.flush();
        this->secondcode->myFile->close();
        if(!this->secondcode->fileName.isEmpty())
            QMessageBox::information(this,"成功","保存成功！");
    }
}
void MainWindow::lineedit()//输入要转到的行号
{
    skip=new QLabel(this);
    tolineedit=new QLineEdit(this);

    skip->resize(80,35);
    skip->setText("跳转到行:");
    skip->setStyleSheet("QLabel{background-color:rgb(33,33,33);color:white}");
    skip->move(this->size().width()/4,100);
    skip->show();

    tolineedit->setStyleSheet("QLineEdit{background-color:rgb(60,60,60);border:2px solid lightblue;color:white}");
    tolineedit->setGeometry(this->size().width()/4+80,100,this->size().width()/2,35);
    tolineedit->show();
    tolineedit->setFocus();
    connect(tolineedit,&QLineEdit::returnPressed,this,&MainWindow::to);
 }
void MainWindow::to()       //转到文本框对应的行
{
    s=tolineedit->text();
    QRegularExpression re;
    re.setPattern("\\d");
    QRegularExpressionMatch match;
    match=re.match(s,0,QRegularExpression::NormalMatch);
    if(match.hasMatch())
    {
        inte=s.toInt();
        QTextBlock block=codeArea->document()->findBlockByLineNumber(inte-1);
        if(block.isValid())
            codeArea->setTextCursor(QTextCursor(block));
        tolineedit->clear();
        skip->close();
        tolineedit->close();
    }
    else
    {
        QMessageBox::warning(0,"error","输入有误,请输入数字");
        tolineedit->clear();
        tolineedit->setFocus();
    }
    if(focus==1)
        codeArea->setFocus();
    else
        secondcode->setFocus();

}

//搜索框
void MainWindow::searchlineedit()
{
    search=new QLineEdit(this);
    search->setStyleSheet("QLineEdit{background-color:rgb(60,60,60);border:2px solid lightblue;color:white}");
    search->setGeometry(this->size().width()/4,100,this->size().width()/2,35);
    search->setPlaceholderText("搜索:");
    search->show();
    search->setFocus();
    connect(search,&QLineEdit::returnPressed,this,&MainWindow::searchclose);
}
void MainWindow::searchclose()
{
    tosearch=search->text();
    if(focus==1)
        searchfile(codeArea);
    else
        searchfile(secondcode);
    search->clear();
    search->close();
}
void MainWindow::searchfile(CodeEdit *searchArea)
{
    while(searchArea->find(tosearch,QTextDocument::FindBackward))
    {
        QTextCursor find_cursor=searchArea->textCursor();
        QTextCharFormat plainFormat(find_cursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);
        searchArea->mergeCurrentCharFormat(colorFormat);
    }
}

//更改主题
void MainWindow::changetheme()
{
    if(qssFile->fileName()==":/default.qss")
        qssFile->setFileName(":/RedYellow.qss");
    else qssFile->setFileName(":/default.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet =tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
}

//字符编码集槽
void MainWindow::showcharmodedialog()
{
    dialog->show();
    dialog->setStyleSheet("QDialog{background-color:black;}");
    QLabel *charmodelabel=new QLabel(dialog);
    charmodelabel->setText("选择字符编码");
    charmodelabel->move(0,35);
    charmodelabel->setStyleSheet("QLabel{color:white;}");
    charmodelabel->show();
}
void MainWindow::doProcessTriggeredByUTF_8()
{
    this->statucharcode->setText("UTF-8");
    charcode=1;
    dialog->close();
}
void MainWindow::doProcessTriggeredByGB18030()
{
    this->statucharcode->setText("GB18030");
    charcode=2;
    dialog->close();
}

//窗口文字放大、缩小槽
void MainWindow::bigger()
{
    charsize+=2;
    qDebug()<<charsize<<endl;
    this->setFont(QFont(tr("Microsoft YaHei"), charsize));
}
void MainWindow::smaller()
{
    charsize-=2;
    qDebug()<<charsize<<endl;
    this->setFont(QFont(tr("Consolas"), charsize));
}

//显示最近打开的文件
void MainWindow::recentshow()
{
    recentfile_dialog->show();
    recentfile_dialog->setStyleSheet("QDialog{background-color:black;}QLabel{background-color:black;color:white;}");
    QFile *recentpath=new QFile("D:\\qt\\build-QtCode-Desktop_Qt_5_13_2_MinGW_32_bit-Debug\\openfilepath.txt");
    recentpath->open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream *pathstream=new QTextStream(recentpath);
    QLabel *pathlabel=new QLabel(recentfile_dialog);
    pathlabel->setText(pathstream->readAll());
    pathlabel->show();
}

//动态显示行列号
void MainWindow::do_cursorChanged()
{
    int rowNum=codeArea->document()->blockCount();
    //获取光标所在行的行号
    const QTextCursor cursor=codeArea->textCursor();
    int colNum = cursor.columnNumber();
    //获取光标所在列的列号
    statutorow->setText(tr("行%1,列%2").arg(rowNum).arg(colNum));
    //在状态栏显示光标位置
}
void MainWindow::button_clicked()
{
    emit buttonclick();
}

//显示地址栏
void MainWindow::showaddress(QString path)
{
    address->resize(this->geometry().width()-250,35);
    address->setText(path);
    address->setStyleSheet("QLabel{background-color:rgb(33,33,33);color:white}");
    address->move(250,65);
    address->show();
}

//集成终端，实现简单编译功能
void MainWindow::makecompile()
{
    compilebool=false;
    if(focus==1)
    {
        if(this->codeArea->fileName.isEmpty())
        {
            QMessageBox::warning(0,"error","文件为空");
            savebool=false;
            return;
        }
        else{
        saveFile();
        savebool=true;
        }
    }
    else
    {
        if(this->secondcode->fileName.isEmpty())
        {
            QMessageBox::warning(0,"error","文件为空");
            savebool=false;
            return;
        }
        else{
        saveFile();
        savebool=true;
        }
    }
    QStringList getname=address->text().split("/");
    QStringList suffix=getname.at(getname.length()-1).split(".");
    compile.setProgram("cmd");
    compile.setArguments(QStringList()<<"/c"<<"gcc -g "+getname.at(getname.length()-1)+" -o "+suffix.at(0)+"\n");
    compile.start();
    compile.waitForStarted();
    compile.waitForReadyRead();
    strTemp=QString::fromLocal8Bit(compile.readAllStandardError());
    QMessageBox testMassage;
    if(strTemp==""){
        testMassage.setText("编译成功");
        testMassage.exec();
        compile.kill();
        compile.waitForFinished();
        compilebool=true;
    }
    else{
        testMassage.setText(strTemp);
        testMassage.exec();
        compile.kill();
        compile.waitForFinished();
        compilebool=false;
    }
}

//实现断点，简单调试功能
void MainWindow::makedebug()
{
    makecompile();
    makejson();
    if(savebool&&compilebool)
    {
        QStringList getname=address->text().split("/");
        QStringList suffix=getname.at(getname.length()-1).split(".");
        debugger.setProgram("gdb");
        debugger.start();
        qDebug()<<debugger.state()<<endl;
        if(debugger.waitForStarted(-1)){
        debugger.write(("exec-file "+suffix.at(0)+"\n").toLatin1());
        debugger.write(("file "+suffix.at(0)+"\n").toLatin1());
        }
        if(debugger.waitForBytesWritten()){
        newdebugwidget();
        }
    }
}
void MainWindow::newdebugwidget()
{
    QWidget *debugwidget=new QWidget();
    debugwidget->resize(500,500);
    debugwidget->setWindowTitle("调试窗口");
    debugwidget->show();

    textedit=new QTextEdit(debugwidget);
    textedit->show();
    textedit->resize(300,300);

    if(debugger.waitForReadyRead()){
    textedit->append(debugger.readAll());
    }
    debuglineedit=new QLineEdit(debugwidget);
    debuglineedit->move(0,300);
    debuglineedit->setFocus();

    debuglineedit->clear();
    debuglineedit->show();

    connect(debuglineedit,&QLineEdit::returnPressed,this,&MainWindow::breakpoint);
}
void MainWindow::breakpoint()
{
    QString gdb;
    gdb=debuglineedit->text();
    debugger.write((gdb+"\n").toLatin1());
    if(debugger.waitForReadyRead())
    {
        textedit->append(debugger.readAll());
    }
}

//多窗口显示
void MainWindow::CodeAreaFocus()
{
    codeArea->setHidden(false);
    secondcode->setHidden(true);
    codeArea->setFocus();
    focus=1;
    showaddress(codeArea->fileName);

}
void MainWindow::SecondCodeFocus()
{
    secondcode->setHidden(false);
    codeArea->setHidden(true);
    secondcode->setFocus();
    focus=2;
    showaddress(secondcode->fileName);
}
void MainWindow::CodeMove(CodeEdit *changearea)
{
    changearea->resize(geometry().width(),geometry().height()-120);
    changearea->move(250,95);
}

//git
void MainWindow::gitinit()
{
     git.setProgram("git-gui.exe");
     git.start();
     git.waitForStarted();
}

//pdf查看器
void MainWindow::openpdf()
{
    QMessageBox::warning(0,"error","我照着博客上教程的写了，但好像总是打不开。");
    QString cmd = "C:\\Program Files (x86)\\Adobe\\Acrobat Reader DC\\Reader\\AcroRd32.exe";
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = true;

        bool bRet = CreateProcess(
            NULL,
            (LPWSTR)cmd.toStdWString().c_str(),
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL, &si, &pi);

        Sleep(5000);

        WId wid = (WId)FindWindow(L"AcrobatSDIWindow", L"Adobe Acrobat Reader DC");

        QWindow *m_window;
        m_window = QWindow::fromWinId(wid);
        m_window->resize(300,300);
        m_window->setFlags(m_window->flags() | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

        QWidget *m_widget;
        m_widget=new QWidget(this);
        m_widget->resize(400,400);
        m_widget = QWidget::createWindowContainer(m_window, m_widget);
        m_widget->setMinimumSize(400, 300);
}

//json保存简单配置
void MainWindow::makejson()
{
    QJsonObject configuration{{"name","(gdb)启动"}};
    configuration.insert("type",statumode->text().append("dbg"));
    configuration.insert("request","launch");
    QStringList list=filename.split("/");
    QString programpath;
    QString cwd;
    for(int i=0;i<list.length()-2;++i)
    {
        cwd.append(list.at(i));
    }
    programpath=cwd;
    configuration.insert("program",programpath.append(".exe"));
    configuration.insert("arg","[]");
    configuration.insert("stopAtEntry","false");
    configuration.insert("cwd",cwd);
    QJsonDocument jsonDoc(configuration);
    QByteArray ba=jsonDoc.toJson();
    QFile file("result.json");
    if(!file.open(QIODevice::ReadWrite))
        QMessageBox::warning(0,"error","保存失败");
    else
    {
        file.write(ba);
        file.close();
    }    
}

//资源管理器
void MainWindow::UpdateCurrentTab(const QModelIndex&)
{
    m_dir_model.setRootPath(QDir::currentPath());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete highlighter;
}
