#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    init();
    setCurrentFile(QString());
}

MainWindow::MainWindow(const QString &fileName)
{
    init();
    loadFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        event->accept();
}

void MainWindow::newFile()
{
    MainWindow *other = new MainWindow;
    other->tile(this);
    other->show();
}

void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        QString program = "./exe/main.exe";
        QStringList arguments;
        arguments<<fileName;
        QProcess *ByClq=new QProcess();
        ByClq->start(program,arguments);
        stateFileName=1;
        openFile(fileName);
        stateFileName=0;
        char pre[]="pre";
        char lex[]=".lex";
        int i=1;
        while(i=0) i++;
        openFile(name2lex(fileName,lex));
        openFile(name2pre(fileName,pre));
        openFile(name2lex(fileName,lex));
     }
}

void MainWindow::openFile(const QString &fileName)
{
    MainWindow *existing = findMainWindow(fileName);
    if (existing) {
        existing->show();
        existing->raise();
        existing->activateWindow();
        return;
    }

    if (isUntitled && textEdit->document()->isEmpty() && !isWindowModified()) {
        loadFile(fileName);
        return;
    }

    MainWindow *other = new MainWindow(fileName);
    if (other->isUntitled) {
        delete other;
        return;
    }
    other->tile(this);
    other->show();
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About designer"),
            tr("The <b>ByCLQ</b> is designed<br>"
               "           by <b>Liqing Cao<b>"));
}

void MainWindow::documentWasModified()
{
    setWindowModified(true);
}

void MainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose);

    isUntitled = true;

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::tile(const QMainWindow *previous)
{
    if (!previous)
        return;
    int topFrameWidth = previous->geometry().top() - previous->pos().y();
    if (!topFrameWidth)
        topFrameWidth = 40;
    const QPoint pos = previous->pos() + 2 * QPoint(topFrameWidth, topFrameWidth);
    if (QApplication::desktop()->availableGeometry(this).contains(rect().bottomRight() + pos))
        move(pos);
}

//! [implicit tr context]
void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
//! [implicit tr context]
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    fileMenu->addSeparator();

    QMenu *recentMenu = fileMenu->addMenu(tr("Recent..."));
    connect(recentMenu, &QMenu::aboutToShow, this, &MainWindow::updateRecentFileActions);
    recentFileSubMenuAct = recentMenu->menuAction();

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = recentMenu->addAction(QString(), this, &MainWindow::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }

    recentFileSeparator = fileMenu->addSeparator();

    setRecentFilesVisible(MainWindow::hasRecentFiles());

    QAction *closeAct = fileMenu->addAction(tr("&Close"), this, &QWidget::close);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Close this window"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::loadFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      /* QMessageBox::warning(this, tr("ByCLQ"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));*/
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::setRecentFilesVisible(bool visible)
{
    recentFileSubMenuAct->setVisible(visible);
    recentFileSeparator->setVisible(visible);
}

static inline QString recentFilesKey() { return QStringLiteral("recentFileList"); }
static inline QString fileKey() { return QStringLiteral("file"); }

static QStringList readRecentFiles(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

static void writeRecentFiles(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(fileKey(), files.at(i));
    }
    settings.endArray();
}

bool MainWindow::hasRecentFiles()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

void MainWindow::prependToRecentFiles(const QString &fileName)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    setRecentFilesVisible(!recentFiles.isEmpty());
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = MainWindow::strippedName(recentFiles.at(i));
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

void MainWindow::openRecentFile()
{
    if (const QAction *action = qobject_cast<const QAction *>(sender()))
    {
        QString program = "./exe/main.exe";
        QStringList arguments;
        arguments<<action->data().toString();
        QProcess *ByClq=new QProcess();
        ByClq->start(program,arguments);
        stateFileName=1;
        openFile(action->data().toString());
        stateFileName=0;
        char pre[]="pre";
        char lex[]=".lex";
        openFile(name2lex(action->data().toString(),lex));
        openFile(name2pre(action->data().toString(),pre));
        openFile(name2lex(action->data().toString(),lex));
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    static int sequenceNumber = 1;

    isUntitled = fileName.isEmpty();
    if (isUntitled) {
        curFile = tr("document%1.txt").arg(sequenceNumber++);
    } else {
        curFile = QFileInfo(fileName).canonicalFilePath();
    }

    textEdit->document()->setModified(false);
    setWindowModified(false);

    if ((!isUntitled && windowFilePath() != curFile))
    {
        if(stateFileName==1)
        MainWindow::prependToRecentFiles(curFile);
    }

    setWindowFilePath(curFile);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

MainWindow *MainWindow::findMainWindow(const QString &fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin && mainWin->curFile == canonicalFilePath)
            return mainWin;
    }

    return 0;
}

/** name2pre得到 pre的文件名**/
QString MainWindow::name2pre(const QString oldname,char *pre){
    int i,j=0;
    QByteArray ba=oldname.toLatin1();
    char *name = ba.data();
    i=strlen(name);
    char * prename= (char *)malloc(i+strlen(pre)+6);//分配空间，+1即可
    if (prename==NULL)
    {
        exit(OVERFLOW);
    }
    while(--i){
        if(name[i]=='\\'||name[i]=='/')
            break;
    }
    if(i!=0)
    {
        j=i+1;
    }
    while(i){
        prename[i]=name[i];
        i--;
    }
    prename[i]=name[i];
    prename[j]='\0';
    strcat(prename,pre);
    strcat(prename,&(name[j]));
    QString result=QString(QLatin1String(prename));
    return result;
}

/** name2lex 得到后缀文件名 **/
QString MainWindow::name2lex(const QString oldname,char *aim){
    int i,j=0;
    QByteArray ba=oldname.toLatin1();
    char *name = ba.data();
    i=strlen(name);
    char *aimname= (char *)malloc(i+strlen(aim)+6);
    if (aimname==NULL)
    {
        exit(OVERFLOW);
    }
    j=i;
    while(--i){
        if(name[i]=='\\'||name[i]=='/')
        {
            break;
        }
        if(name[i]=='.')
        {
            j=i;
            break;
        }
    }
    i=j-1;
    while(i){
        aimname[i]=name[i];
        i--;
    }
    aimname[i]=name[i];
    aimname[j]='\0';
    strcat(aimname,aim);
    QString result=QString(QLatin1String(aimname));
    return result;
}
