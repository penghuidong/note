#include "MainWindow.h"
#include <QMenu>
#include <QToolBar>
#include <QIcon>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow()
{
    setWindowTitle("NotePad - [ New ]");
    setAcceptDrops(true);
    m_filePath = "";
    m_isTextChanged = false;

}

MainWindow* MainWindow::NewInstance()
{
    MainWindow* ret = new MainWindow();
    if( (ret==NULL) || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }
    ret->resize(800, 600);
    return ret;
}

bool MainWindow::construct()
{
    bool ret = true;

    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();
    ret = ret && initMainEdit();

    return ret;
}


bool MainWindow::initMainEdit()
{
    bool ret = true;

    mainEditor.setParent(this);
    connect(&mainEditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    setCentralWidget(&mainEditor);
    mainEditor.setAcceptDrops(false);

    return ret;
}

bool MainWindow::initMenuBar()
{
    bool ret = true;
    QMenuBar* mb = menuBar();

    ret = ret && initFileMenu(mb);
    ret = ret && initEditMenu(mb);
    ret = ret && initFormatMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);

    return ret;
}

bool MainWindow::initToolBar()
{
    bool ret = true;
    QToolBar* toolBar = addToolBar("Tool Bar");
    ret = ret && (toolBar!=NULL);

    initFileToolBar(toolBar);
    initEditToolBar(toolBar);
    initFormatToolBar(toolBar);
    initViewToolBar(toolBar);

    return ret;
}

bool MainWindow::initStatusBar()
{
    bool ret = true;
    QStatusBar* sb = statusBar();
    ret = ret && (sb!=NULL);
    if(ret)
    {
        statusLbl.setMinimumWidth(200);
        statusLbl.setAlignment(Qt::AlignCenter);
        statusLbl.setText("Ln:1 Col:1");

        QLabel* label = new QLabel("By Phd");
        label->setMinimumWidth(150);
        label->setAlignment(Qt::AlignCenter);

        //sb->addPermanentWidget(new QLabel()); //add separator
        sb->addPermanentWidget(&statusLbl);
        sb->addPermanentWidget(label);
    }

    return ret;
}

bool MainWindow::initFileMenu(QMenuBar *mb)
{
    QMenu* FileMenu = new QMenu("File(&F)", mb);
    bool ret = (FileMenu!=NULL);

    if(ret)
    {
        QAction* action  = NULL;

        ret = ret && makeAction(action, mb,"New(&N)", Qt::CTRL+Qt::Key_N);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileNew()));
            FileMenu->addAction(action);
        }

        ret = ret && makeAction(action, mb,"Open(&O)", Qt::CTRL+Qt::Key_O);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileOpen()));
            FileMenu->addAction(action);
        }

        ret = ret && makeAction(action, mb,"Save(&S)", Qt::CTRL+Qt::Key_S);
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSave()));
            FileMenu->addAction(action);
        }

        ret = ret && makeAction(action, mb,"Save as(&A)");
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
            FileMenu->addAction(action);
        }

        FileMenu->addSeparator();

        ret = ret && makeAction(action, mb, "Page Setup(&U)");
        if(ret)
            FileMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Print(&P)", Qt::CTRL+Qt::Key_P);
        if(ret)
            FileMenu->addAction(action);

        FileMenu->addSeparator();

        ret = ret && makeAction(action, mb, "Exit(&X)", Qt::CTRL+Qt::Key_X);
        if(ret)
            FileMenu->addAction(action);
    }
    if(ret)
        mb->addMenu(FileMenu);
    else
        delete FileMenu;

    return ret;
}

bool MainWindow::makeAction(QAction*& action,QWidget* parent, QString text, int key)
{
    bool ret = true;
    action = new QAction(text, parent);

    if(action!=NULL)
        action->setShortcut(QKeySequence(key));
    else
        ret = false;

    return ret;
}

bool MainWindow::makeAction(QAction*& action, QWidget *parent, QString tip, QString iconPath)
{
    bool ret = true;
    action  = new QAction(tip,parent);

    if(action!=NULL)
        action->setIcon(QIcon(iconPath));
    else
        ret = false;

    return ret;
}

bool MainWindow::initFileToolBar(QToolBar* tb)
{
    bool ret = true;

    if(ret)
    {
        QAction* action = NULL;
        ret = ret && makeAction(action, tb, "New", ":/res/pic/new.png");
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileNew()));
            tb->addAction(action);
        }
        ret = ret && makeAction(action, tb, "Open", ":/res/pic/open.png");
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileOpen()));
            tb->addAction(action);
        }
        ret = ret && makeAction(action, tb, "Save", ":/res/pic/save.png");
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSave()));
            tb->addAction(action);
        }
        ret = ret && makeAction(action, tb, "Save As", ":/res/pic/saveas.png");
        if(ret)
        {
            connect(action, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
            tb->addAction(action);
        }
        ret = ret && makeAction(action, tb, "Print", ":/res/pic/print.png");
        if(ret)
            tb->addAction(action);

        tb->addSeparator();
    }
    return ret;
}


bool MainWindow::initEditToolBar(QToolBar* tb)
{
    bool ret = (tb!=NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action, tb, "Cut", ":/res/pic/cut.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Copy", ":/res/pic/copy.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Paste", ":/res/pic/paste.png");
        if(ret)
            tb->addAction(action);

        tb->addSeparator();

        ret = ret && makeAction(action, tb,"Undo", ":/res/pic/undo.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Redo", ":/res/pic/redo.png");
        if(ret)
            tb->addAction(action);

        tb->addSeparator();

        ret = ret && makeAction(action, tb, "Find", ":/res/pic/find.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Replace", ":/res/pic/replace.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Goto", ":/res/pic/goto.png");
        if(ret)
            tb->addAction(action);

        tb->addSeparator();
    }

    return ret;
}


bool MainWindow::initFormatToolBar(QToolBar* tb)
{
    bool ret = (tb!=NULL);

    if(ret)
    {
        QAction* action = NULL;
        ret = ret && makeAction(action, tb,"Auto Wrap", ":/res/pic/wrap.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Font", ":/res/pic/font.png");
        if(ret)
            tb->addAction(action);
        tb->addSeparator();
    }

    return ret;
}

bool MainWindow::initViewToolBar(QToolBar* tb)
{
    bool ret = (tb!=NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action, tb,"Tool Bar", ":/res/pic/tool.png");
        if(ret)
            tb->addAction(action);
        ret = ret && makeAction(action, tb, "Status Bar", ":/res/pic/status.png");
        if(ret)
            tb->addAction(action);
    }

    return ret;
}

bool MainWindow::initEditMenu(QMenuBar *mb)
{
    QMenu* EditMenu = new QMenu("Edit(&E)", mb);
    bool ret =  (EditMenu!=NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action, mb, "Undo(&U)", Qt::CTRL + Qt::Key_Z );
        if(ret)
            EditMenu->addAction(action);

        EditMenu->addSeparator();

        ret = ret && makeAction(action, mb, "Cut(&T)", Qt::CTRL + Qt::Key_X);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Copy(&C)", Qt::CTRL + Qt::Key_C);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb,"Paste(&P)", Qt::CTRL + Qt::Key_V);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Delete(&L)", QKeySequence::Delete);
        if(ret)
            EditMenu->addAction(action);

        EditMenu->addSeparator();

        ret = ret && makeAction(action, mb, "Find(&F)", Qt::CTRL + Qt::Key_F);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Find Next(&N)", QKeySequence::FindNext);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Replace(&R)", Qt::CTRL + Qt::Key_H);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Goto(&G)", Qt::CTRL + Qt::Key_G);
        if(ret)
            EditMenu->addAction(action);

        EditMenu->addSeparator();

        ret = ret && makeAction(action, mb, "All(&A)", Qt::CTRL + Qt::Key_A);
        if(ret)
            EditMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Time/Date(&D)", QKeySequence::Refresh);
        if(ret)
            EditMenu->addAction(action);
    }

    if(ret)
        mb->addMenu(EditMenu);
    else
        delete EditMenu;

    return ret;
}

bool MainWindow::initFormatMenu(QMenuBar* mb)
{
    bool ret = true;
    QMenu* FormatMenu = new QMenu("Format(&O)",mb);
    ret = ret && (FormatMenu!=NULL);

    if(ret)
    {
        QAction* action = NULL;
        ret = ret && makeAction(action,mb, "Auto Wrap(W)");
        if(ret)
            FormatMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Font(F)");
        if(ret)
            FormatMenu->addAction(action);
    }

    if(ret)
        mb->addMenu(FormatMenu);
    else
        delete FormatMenu;

    return ret;
}

bool MainWindow::initViewMenu(QMenuBar* mb)
{
    bool ret = true;
    QMenu* ViewMenu = new QMenu("View(&V)", mb);

    ret = ret && (ViewMenu!=NULL);

    if(ret)
    {
        QAction* action = NULL;
        ret = ret && makeAction(action,mb, "Status Bar(S)");
        if(ret)
            ViewMenu->addAction(action);

        ret = ret && makeAction(action, mb, "Tool Bar(T)");
        if(ret)
            ViewMenu->addAction(action);
    }

    if(ret)
        mb->addMenu(ViewMenu);
    else
        delete ViewMenu;
    return ret;
}

bool MainWindow::initHelpMenu(QMenuBar *mb)
{
    bool ret = true;
    QMenu* HelpMenu = new QMenu("Help(&H)", mb);

    ret = ret && (HelpMenu!=NULL);
    if(ret)
    {
        QAction* action = NULL;
        ret = ret && makeAction(action,mb, "View Help(H)");
        if(ret)
            HelpMenu->addAction(action);

        HelpMenu->addSeparator();

        ret = ret && makeAction(action,mb, "About(A)");
        if(ret)
            HelpMenu->addAction(action);

    }

    if(ret)
        mb->addMenu(HelpMenu);
    else
        delete HelpMenu;

    return ret;
}

MainWindow::~MainWindow(){}
