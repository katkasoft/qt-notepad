#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <QApplication>

using namespace std;
QString filename = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    stringstream ss;
    string line;
    filename = QFileDialog::getOpenFileName(this, tr("Open file"), "~", tr("Any files (*.*)"));
    if (!filename.isEmpty()) {
        ifstream file (filename.toStdString());
        if (file.is_open()) {
            while (getline(file, line)) {
                ss << line << '\n';
            }
            file.close();
            QString content = QString::fromStdString(ss.str());
            ui->textEdit->setText(content);
        } else {
            QMessageBox::critical(this, "error", "Unable to open file");
        }
    }
}


void MainWindow::on_actionAbout_notepad_triggered()
{
    QMessageBox::about(this, "About notepad", "Notepad v0.1.0\nA simple and fast notepad.");
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}


void MainWindow::on_actionSave_triggered()
{
    if (filename == "") {
        filename = QFileDialog::getSaveFileName(this, tr("Save file"), "~", tr("Any files (*.*"));
    }
    if (!filename.isEmpty()) {
        ofstream file (filename.toStdString());
        if (file.is_open()) {
            QString text = ui->textEdit->toPlainText();
            file << text.toStdString();
            file.close();
        } else {
            QMessageBox::critical(this, "error", "Unable to save file");
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}



void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionSelect_all_triggered()
{
    ui->textEdit->selectAll();
}

