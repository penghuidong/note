#include "MainWindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QMap>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QList>
#include <QUrl>
#include <QFileInfo>

void MainWindow::showErrorMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("Error");
    msg.setText(message);
    msg.setIcon(QMessageBox::Critical);
    msg.setStandardButtons(QMessageBox::Ok);

    msg.exec();
}

int MainWindow::showQueryMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("Query");
    msg.setText(message);
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    return msg.exec();
}

QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode, QString title)
{
    QFileDialog dialog(this);
    QString ret = "";
    QStringList fliters;
    QMap<QString, QString> map;
    const char* fliterArray[][2] = {
        {"Text Files (*.txt)", ".txt"},
        {"All Files (*)", "*"},
        {NULL, NULL}
    };

    for(int i=0; fliterArray[i][0]!=NULL; i++)
    {
        fliters.append(fliterArray[i][0]);
        map.insert(fliterArray[i][0], fliterArray[i][1]);
    }

    dialog.setWindowTitle(title);
    dialog.setAcceptMode(mode);
    dialog.setFilters(fliters);

    if(mode==QFileDialog::AcceptOpen)
        dialog.setFileMode(QFileDialog::ExistingFiles);
    if(dialog.exec()==QFileDialog::Accepted)
    {
        ret = dialog.selectedFiles()[0];
        if(mode == QFileDialog::AcceptSave)
        {
            QString postFix = map[dialog.selectedFilter()];
            if((postFix!="*") && !ret.endsWith(postFix))
                ret = ret + postFix;
        }
    }

    return ret;
}


void MainWindow::preEditorChange()
{
    if( m_isTextChanged )  //!!!!!!!
    {
        int r = showQueryMessage("Do you want to save the changes to file?");
        switch(r)
        {
        case QMessageBox::Yes:
            saveCurrentData(m_filePath);
            break;
        case QMessageBox::No:
            m_isTextChanged = false;
            break;
        case QMessageBox::Cancel:
            break;
        }
    }
}

void MainWindow::openFileToEditor(QString path)
{
    if(path!="")
    {
        qDebug() << path;
        QFile file(path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            mainEditor.setPlainText(QString(file.readAll()));
            file.close();
            m_filePath = path;
            m_isTextChanged = false;
            setWindowTitle("NotePad - [ " + m_filePath + " ]");
        }
    }
}

QString MainWindow::saveCurrentData(QString path)
{
    QString ret = path;

    if(ret=="")
        ret = showFileDialog(QFileDialog::AcceptSave, "Save");

    if(ret!="")
    {
        QFile file(ret);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&file);
            out << mainEditor.toPlainText();
            file.close();
            setWindowTitle(QString("NotePad - [ ") + ret + " ]" );
            m_isTextChanged = false;
        }
        else
        {
            showErrorMessage(QString("Save file error! \n\n") + "\"" + ret + "\"");
            ret = "";
        }
    }

    return ret;
}

void MainWindow::onFileNew()
{
    preEditorChange();

    if( !m_isTextChanged )
    {
        mainEditor.clear();
        setWindowTitle("NotePad - [ New ]");
        m_filePath = "";
        m_isTextChanged = false;
    }
}

void MainWindow::onFileOpen()
{
    QString path = showFileDialog(QFileDialog::AcceptOpen, "Open");

    if(path!="")
    {
        QFile file(path);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            mainEditor.setPlainText(file.readAll()); //tang use setPlainText(QString(file.readAll()))
            file.close();
            m_filePath = path;
            setWindowTitle("NotePad - [" + m_filePath + " ]");
        }
        else
        {
            showErrorMessage(QString("Open file error! \n\n") + "\"" + path + "\"");
        }
    }
}

void MainWindow::onFileSave()
{
    QString path = saveCurrentData(m_filePath);

    if(path!="")
        m_filePath = path;
}

void MainWindow::onFileSaveAs()
{
    QString path = saveCurrentData();

    if(path!="")
        m_filePath = path;
}

void MainWindow::onTextChanged()
{
    if( !m_isTextChanged )
        setWindowTitle("*" + windowTitle());

    m_isTextChanged = true;
}


void MainWindow::closeEvent(QCloseEvent *cv)
{
    qDebug() << "void MainWindow::closeEvent(QCloseEvent *cv)" ;
    preEditorChange();

    if( !m_isTextChanged )
        QMainWindow::closeEvent(cv);
    else
        cv->ignore();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *dee)
{
    qDebug() << "void MainWindow::dragEnterEvent(QDragEnterEvent *dee)";
    if(dee->mimeData()->hasUrls())
        dee->acceptProposedAction();
    else
        dee->ignore();
}

void MainWindow::dropEvent(QDropEvent *dv)
{
    qDebug() << "void MainWindow::dropEvent(QDropEvent *dv)";
    if(dv->mimeData()->hasUrls())
    {
        QList<QUrl> list = dv->mimeData()->urls();
        QString path = list[0].toLocalFile();
        QFileInfo finfo(path);

        if(finfo.isFile())
        {
            preEditorChange();
            if(!m_isTextChanged)
                openFileToEditor(path);
        }
    }
    else
        dv->ignore();
}

