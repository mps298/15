#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    if (gameOn)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("New game"));
        msgBox.setText(tr("Are you sure?"));
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        msgBox.setButtonText(QMessageBox::No, tr("No"));
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::No) {    return; }
    }
    else
    {
        gameOn = true;
    }

    ui->fieldViewWidget->resetCells(ui->fieldViewWidget->getFieldSideLength());
    ui->fieldViewWidget->messCells();
}

void MainWindow::on_exitButton_clicked()
{
    qDebug()<<"gameon = "<<gameOn;
    if (gameOn)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Exit"));
        msgBox.setText(tr("Are you sure?"));
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes, tr("Yes"));
        msgBox.setButtonText(QMessageBox::No, tr("No"));
        msgBox.setDefaultButton(QMessageBox::No);

        if(msgBox.exec() == QMessageBox::No) {    return; }
    }

    close();
}

void MainWindow::gameOverSlot()
{
    if (gameOn)
    {
        gameOn = false;
        QMessageBox::information(this, tr("Game Over"), tr("Congratulations,\nYOU WON!"));
    }

    ui->fieldViewWidget->resetCells(ui->fieldViewWidget->getFieldSideLength());
}

void MainWindow::on_resizeButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Resize"));
    msgBox.setText(tr("Change field size"));
    msgBox.setIcon(QMessageBox::NoIcon);

    QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);
    QPushButton *button_4 = msgBox.addButton(tr("4x4"), QMessageBox::ActionRole);
    QPushButton *button_5 = msgBox.addButton(tr("5x5"), QMessageBox::ActionRole);
    QPushButton *button_8 = msgBox.addButton(tr("8x8"), QMessageBox::ActionRole);
    QPushButton *button_10 = msgBox.addButton(tr("10x10"), QMessageBox::ActionRole);


    switch (ui->fieldViewWidget->getFieldSideLength()) {
        case 4: button_4->setDisabled(true); break;
        case 5: button_5->setDisabled(true); break;
        case 8: button_8->setDisabled(true); break;
        case 10: button_10->setDisabled(true); break;

    default:
        break;
    }

    msgBox.exec();

    if (msgBox.clickedButton()==button_4) { ui->fieldViewWidget->setFieldSideLength(4); }
    else if (msgBox.clickedButton()==button_5) { ui->fieldViewWidget->setFieldSideLength(5); }
    else if (msgBox.clickedButton()==button_8) { ui->fieldViewWidget->setFieldSideLength(8); }
    else if (msgBox.clickedButton()==button_10) { ui->fieldViewWidget->setFieldSideLength(10); }
    else if (msgBox.clickedButton()==cancelButton)  { return; }
    else { return; }

    ui->fieldViewWidget->resetCells(ui->fieldViewWidget->getFieldSideLength());
    gameOn = false;
}


