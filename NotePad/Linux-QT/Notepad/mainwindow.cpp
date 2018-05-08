#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>    //text input and output
#include <QString>
#include <QFileDialog>   //dialog action
#include <QUndoCommand>
#include <QClipboard>   //baisc notepad action
#include <QMessageBox>  //message display
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setCentralWidget (ui->editor);//widget
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionUndo_triggered()
{
    ui ->editor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->editor->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->editor->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->editor->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->editor->paste();
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog ::getOpenFileName(this , "choose a file" , "/home/gc2017gc/");
    ui->statusBar->showMessage(fileName);
    QFile file(fileName) ; //Qfile
    bool ok=file.open(QFile::ReadOnly | QFile::Text) ;// judge if the filename read successfully
    if(ok)
    {
        QTextStream input (&file) ;// QTextStream: input or output
        ui->editor->setPlainText(input.readAll());
        file.close();
    }
    else
    {
        QMessageBox::information(this,"open failed","Cannelled please try again!!!");
        return ;
    }

}


void MainWindow::on_actionSave_as_triggered()
{

     fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");
     QFile file(fileName) ;
     bool ok=file.open(QFile::WriteOnly | QFile::Text) ;
     if(ok)
     {
         QTextStream out(&file);
         out << ui->editor->toPlainText();
         file.flush() ;
         file.close() ;
     }
     else
     {
         QMessageBox::information(this,"save as failed","Cannelled please try again!!");
         return ;
     }


}

void MainWindow::on_actionNew_triggered()
{

     if (! ui->editor->toPlainText().isEmpty())
     {
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this , "save" , "Save changes to document before closing?" , QMessageBox::Yes|QMessageBox::No  ) ;
          if(reply == QMessageBox::Yes)
          {
              if(fileName==NULL)
                  fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");

              QFile file(fileName) ;
              bool ok=file.open(QFile::WriteOnly | QFile::Text) ;
              if(ok)
              {
                  QTextStream out(&file);
                  out << ui->editor->toPlainText();
                  file.flush() ;
                  file.close() ;
              }
              else
              {
                  QMessageBox::information(this,"new failed","Cancelled please try again!!");
                  return ;
              }
          }
     }
     ui->editor->clear();
}


void MainWindow::on_actionSave_triggered()
{
    if(fileName==NULL)
        fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");

    QFile file(fileName) ;
    bool ok=file.open(QFile::WriteOnly | QFile::Text) ;
    if(ok)
    {
        QTextStream out(&file);
        out << ui->editor->toPlainText();
        file.flush() ;
        file.close() ;
    }
    else
    {
        QMessageBox::information(this,"save failed","Cannelled please try again!!");
        return ;
    }
}


void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this,"GC'pad","thanks for using");
}
