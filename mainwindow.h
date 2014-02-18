#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void DoThings();
    void ChangeText();
    void clickButton();
    void enableButton(QString s);

private:
    Ui::MainWindow *ui;

    QGroupBox *mainWidget;
    QVBoxLayout *mainLayout;
    QGroupBox *topWidget;
    QGroupBox *botWidget;
    QHBoxLayout *topLayout;
    QLabel *label1;
    QLineEdit *text1;
    QPushButton *button1;
    QHBoxLayout *botLayout;
    QLabel *label2;
    QPlainTextEdit *text2;

    QNetworkAccessManager qnam;
    QNetworkReply *reply;

    bool isBusy;
};

#endif // MAINWINDOW_H
