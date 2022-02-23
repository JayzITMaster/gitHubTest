#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // takes up screen space
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    // clears text from notepad
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open the file"); // to allow user to open the selected text file they want
    QFile file(filename); // object for reading and writing files
    currentFile = filename; // stores current file name
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) // open file for read only purpose
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString()); //  error message to warn the user
        return;
    }
    setWindowTitle(filename); // declares the title of the file
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this,"Save as"); // to allow user to save file within the system
   QFile file(fileName); // object for reading and writing files
   if(!file.open(QFile::WriteOnly | QFile::Text)) // open file for read only purpose
   {
       QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString()); // error message to warn the user
       return;
   }
   currentFile = fileName; // stores current file name
   setWindowTitle(fileName); // declares the title of the file
   QTextStream out(&file); // creates interface for writing Q text stream
   QString text = ui->textEdit->toPlainText(); // copy text widget and converting it back to plain text
   out << text; // output to file
   file.close(); // close file
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer; // to interact with a printer thats on the current network
    printer.setPrinterName("Printer Name"); // declare printer name
    QPrintDialog qDialog(&printer, this); // to select the printer that the user want to use

    if(qDialog.exec() == QDialog::Rejected) // error message if user can't access printer
    {
        QMessageBox::warning(this, "Warning","Cannot Access printer");
        return;
    }
    ui->textEdit->print(&printer); // gives the program access to the printer
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit(); // terminate notepad program
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy(); // copies text from notepad
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste(); // paste text on notepad
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut(); // cuts out selected text
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo(); // undo's a text
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo(); // redo a proccess
}

