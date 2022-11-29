#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_login_clicked();

    void on_button_register_clicked();

    void on_UI_Password_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void connect();
    bool ConnectionIsOk = false;
    void retryConnection();
    void loginError(QString errString);
    void createSave(const qint32 school_id, const qint32 lvl1, const qint32 lvl2);
    QString savePath{"./game/"};
    void uploadSave();
    qint32 schoolID{ 0 }, lvl1{ 0 }, lvl2{ 0 };
};
#endif // MAINWINDOW_H
