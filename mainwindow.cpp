#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegExp>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Window"));
    mainWidget = new QGroupBox;
    mainLayout = new QVBoxLayout;
    topWidget = new QGroupBox;
    botWidget = new QGroupBox;
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(botWidget);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    //Setup group 1
    topLayout = new QHBoxLayout;
    label1 = new QLabel(tr("Input"));
    text1 = new QLineEdit(tr("Default Text"));
    button1 = new QPushButton(tr("Test"));
    connect(button1, SIGNAL(clicked()), this, SLOT(DoThings()));
    topLayout->addWidget(label1);
    topLayout->addWidget(text1);
    topLayout->addWidget(button1);
    topWidget->setLayout(topLayout);

    //Setup group 2
    botLayout = new QHBoxLayout;
    label2 = new QLabel(tr("Output"));
    text2 = new QPlainTextEdit(tr("Default Text"));
    botLayout->addWidget(label2);
    botLayout->addWidget(text2);
    botWidget->setLayout(botLayout);

    connect(button1, SIGNAL(clicked()), this, SLOT(clickButton()));
    connect(text1, SIGNAL(returnPressed()), this, SLOT(clickButton()));
    connect(text1, SIGNAL(textChanged(QString)), this, SLOT(enableButton(QString)));

    adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DoThings()
{
    QString url = "http://www.csse.monash.edu.au/~jwb/cgi-bin/wwwjdic.cgi?1ZUJ" + text1->text();
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), this, SLOT(ChangeText()));
}

void MainWindow::ChangeText()
{
    QString filter = reply->readAll();
    filter = filter.mid( filter.indexOf("<pre>")+6, filter.indexOf("</pre>") - filter.indexOf("<pre>")-6 );
    text2->clear();
    reply->deleteLater();
    reply = 0;

    QRegExp regex("(.+)\\n$");
    regex.setMinimal(true);

    if (regex.isValid())
        text2->appendPlainText("Valid\n");
    regex.indexIn(filter);
    text2->appendPlainText(QString("%1").arg(regex.captureCount()));

    for (int i = 0; i < regex.capturedTexts().length(); i++)
        text2->appendPlainText(">>" + QString("%1").arg(i) + ">>" + regex.capturedTexts()[i] + "\n");

    text2->appendPlainText(filter);




    //text2->setPlainText(filter);
    isBusy = false;
}

void MainWindow::clickButton()
{
    if (!isBusy)
    {
        isBusy = true;
        button1->setDisabled(true);
        DoThings();
    }
}

void MainWindow::enableButton(QString s)
{
    if (!isBusy)
        button1->setEnabled( !(s.isEmpty()) );
}
