#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QProcess>
#include <tchar.h>
#include <QSqlTableModel>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect();
    ui->button_login->setEnabled(false);
    ui->button_register->setEnabled(false);
}

MainWindow::~MainWindow()
{
    uploadSave();
    delete ui;
}

/**
 * @brief MainWindow::connect : Open a connection to database.
*/
void MainWindow::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("161.35.189.167");
        db.setConnectOptions("");
        db.setPort(3306);
        db.setDatabaseName("");
        db.setUserName("");
        db.setPassword("");
        ConnectionIsOk = db.open();
        if(!ConnectionIsOk)
        {
            qDebug() << db.lastError();
            retryConnection();
        }
}

/**
 * @brief MainWindow::retryConnection : Display a textbox if the connection to the database fails and ask the user if they want to retry.
 */
void MainWindow::retryConnection()
{
    QMessageBox ErrorBox;
    ErrorBox.setText("Unable to connecto to server");
    ErrorBox.setInformativeText("Do you want to retry?");
    ErrorBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
    ErrorBox.setDefaultButton(QMessageBox::Retry);
    int ButtonSelection = ErrorBox.exec();

    if(ButtonSelection == QMessageBox::Retry)
    {
        connect();
    }
}

/**
 * @brief MainWindow::loginError : Display an error when login failed.
 * @param errString
 */
void MainWindow::loginError(QString errString)
{
    QMessageBox ErrorBox;
    ErrorBox.setText("An error has occured while " + errString);
    ErrorBox.setInformativeText("Please try again.");
    ErrorBox.exec();
}

void MainWindow::createSave(const qint32 school_id, const qint32 lvl1, const qint32 lvl2)
{
    QDir dir;

    if(!dir.exists(savePath))
    {
        dir.mkdir(savePath);
    }

    QFile saveData(savePath + "save.dat");
    saveData.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&saveData);
    stream << school_id << "\n"
           << lvl1 << "\n"
           << lvl2;
    saveData.close();
}

void MainWindow::uploadSave()
{
    QFile saveData(savePath + "save.dat");
    if(saveData.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!saveData.atEnd())
        {
            schoolID = saveData.readLine().toInt();
            lvl1 = saveData.readLine().toInt();
            lvl2 = saveData.readLine().toInt();
        }
    }

    saveData.close();

    QDir dir;
    dir.remove(savePath + "save.dat");

    QSqlQuery q;
    q.prepare("UPDATE users SET Level_1 = :lvl1, Level_2 = :lvl2 WHERE school_id = :id");
    q.bindValue(":lvl1", lvl1);
    q.bindValue(":lvl2", lvl2);
    q.bindValue(":id", schoolID);

    if(q.exec())
    {
        qDebug() << q.size();
    }
}
/**
 * @brief MainWindow::on_button_login_clicked : Main function used when a user attempts to login.
 */
void MainWindow::on_button_login_clicked()
{
    if(!ConnectionIsOk)
    {
        retryConnection();
    }
    qint32 username = ui->UI_Username->text().toInt();
    QString password = ui->UI_Password->text();

    // Upload the current save to prevent save data from being lost from the previous user.
    uploadSave();

    // Prepare a sanitized statement to prevent SQL Injection
    QSqlQuery q;
    q.prepare("SELECT FirstName, PermissionLevel, Level_1, Level_2 FROM users WHERE school_id = :username AND password = :password");
    q.bindValue(":username", username);
    q.bindValue(":password", password);

    // Execute the statement and check if the username and password is valid.
    // If the credentials are not valid throw an error.
    // If the user is a student start the game, if they are a teacher open the admin screen.
    if(q.exec())
    {
        q.first();
        if(q.size() > 0 && q.value(1) == "student")
        {
             q.first();
            // qDebug() << q.value(0);
            // qDebug() << q.value(1);

             createSave(username, q.value(2).toInt(), q.value(3).toInt());

             QProcess::startDetached("cmd.exe", QStringList("/c cd ./game && app.exe"));

             ui->UI_Password->clear();
        }

        else if(q.size() > 0 && q.value(1) == "teacher")
        {
            ui->UI_Password->clear();

            QSqlTableModel *model = new QSqlTableModel;
               model->setTable("users");
               model->setEditStrategy(QSqlTableModel::OnFieldChange);
               model->select();
               model->setHeaderData(0, Qt::Horizontal, tr("School ID"));
               model->setHeaderData(1, Qt::Horizontal, tr("Lastname"));
               model->setHeaderData(2, Qt::Horizontal, tr("Firstname"));
               model->setHeaderData(3, Qt::Horizontal, tr("Password"));
               model->setHeaderData(4, Qt::Horizontal, tr("Permission Level"));
               model->setHeaderData(5, Qt::Horizontal, tr("Level 1"));
               model->setHeaderData(6, Qt::Horizontal, tr("Level 2"));


               QTableView *view = new QTableView;
               view->setWindowTitle("Climate Stompers - My Class");
               view->setFixedSize(1080, 1080);
               view->setModel(model);
               view->hideColumn(3); // don't show the ID
               view->show();
        }

        else
        {
            loginError("logging in.");
        }
    }
}

/**
 * @brief MainWindow::on_button_register_clicked : Main function used for registering
 */
void MainWindow::on_button_register_clicked()
{
    if(!ConnectionIsOk)
    {
        retryConnection();
    }
	
	uploadSave();
	
    qint32 username = ui->UI_Username->text().toInt();
    QString password = ui->UI_Password->text();

    // Prepare sanitized statement
    QSqlQuery q;
    q.prepare("SELECT school_id FROM users where school_id = :username");
    q.bindValue(":username", username);

    // Execute statement and return an error if the username(school id) already exists.
    if(q.exec())
    {
        if(q.size() > 0)
        {
            loginError("registering. A user with that ID already exists.");
        }
        else
        {
            q.prepare("INSERT INTO users(school_id, password) VALUES(:username, :password)");
            q.bindValue(":username", username);
            q.bindValue(":password", password);
            q.exec();
            ui->UI_Password->clear();
            //qDebug() << q.lastError().databaseText();

            createSave(username, 0, 0);
            QProcess::startDetached("cmd.exe", QStringList("/c cd ./game && app.exe"));
        }
    }

}


/**
 * @brief MainWindow::on_UI_Password_textChanged : Disable login and register buttons if the username OR password field is blank.
 * @param arg1
 */
void MainWindow::on_UI_Password_textChanged(const QString &arg1)
{
   if(ui->UI_Password->text().isEmpty() || ui->UI_Username->text().isEmpty())
    {
        ui->button_login->setEnabled(false);
        ui->button_register->setEnabled(false);
    }
    else
   {
        ui->button_login->setEnabled(true);
        ui->button_register->setEnabled(true);
   }

}

