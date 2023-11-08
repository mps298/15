#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    bool gameOn = false;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();
    void on_exitButton_clicked();
    void gameOverSlot();
    void on_resizeButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
