#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QPlainTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit mainEditor;
    QLabel statusLbl;
    QString m_filePath;
    bool m_isTextChanged;

    MainWindow();
    MainWindow(const MainWindow&);
    MainWindow& operator = (const MainWindow&);
    
    bool construct();
    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initMainEdit();

    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFormatMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);

    bool initFileToolBar(QToolBar* tb);
    bool initEditToolBar(QToolBar* tb);
    bool initFormatToolBar(QToolBar* tb);
    bool initViewToolBar(QToolBar* tb);


    bool makeAction(QAction*& action, QWidget* parent, QString text, int key =0);
    bool makeAction(QAction*& action, QWidget* parent, QString tip, QString iconPath);

    QString showFileDialog(QFileDialog::AcceptMode mode, QString title);
    void showErrorMessage(QString message);
    int showQueryMessage(QString message);
    void preEditorChange();
    QString saveCurrentData(QString path = "");
    void openFileToEditor(QString path);

protected:
    void closeEvent(QCloseEvent *cv);
    void dropEvent(QDropEvent *dv);
    void dragEnterEvent(QDragEnterEvent *dee);

private slots:
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onFileNew();
    void onTextChanged();

public:
    static MainWindow* NewInstance();
    ~MainWindow();
};

#endif // MAINWINDOW_H
