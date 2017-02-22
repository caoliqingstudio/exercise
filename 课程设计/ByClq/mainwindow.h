#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QProcess>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition with macro]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
//! [class definition with macro]
    explicit MainWindow(const QString &fileName);

    void tile(const QMainWindow *previous);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    void updateRecentFileActions();
    void openRecentFile();
    void about();
    void documentWasModified();

private:
    enum { MaxRecentFiles = 5 };

    QString name2pre(const QString oldname,char *pre);
    QString name2lex(const QString oldname,char *aim);
    void init();
    void createActions();
    void createStatusBar();
    void readSettings();
    void openFile(const QString &fileName);
    void loadFile(const QString &fileName);
    static bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    void setRecentFilesVisible(bool visible);
    void setCurrentFile(const QString &fileName);
    static QString strippedName(const QString &fullFileName);
    MainWindow *findMainWindow(const QString &fileName) const;

    QTextEdit *textEdit;

    QAction *recentFileActs[MaxRecentFiles];
    QAction *recentFileSeparator;
    QAction *recentFileSubMenuAct;

    QString curFile;
    bool stateFileName;
    bool isUntitled;
};

#endif
