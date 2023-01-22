#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
using namespace std;
string zuzyteliterki;
QString qzuzyteliterki;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->dolaczButton, &QPushButton::clicked, this, &MainWindow::dolaczBtnHit);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::sendBtnHit);
}

MainWindow::~MainWindow()
{
    if(sock)
        sock->close();
    delete ui;
}
void MainWindow::dolaczBtnHit(){
    if(sock)
            delete sock;
    sock = new QTcpSocket(this);
    zuzyteliterki = "";
    sock->connectToHost("127.0.0.1", 8080);
    connect(sock, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    connect(sock, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
    //connect(sock, &QTcpSocket::errorOccurred, this, &MyWidget::socketError);
    connect(sock, &QTcpSocket::readyRead, this, &MainWindow::socketReadable);
}

void MainWindow::sendBtnHit(){
    auto txt = ui->lineEdit_2->text().trimmed();
    auto str = txt.toStdString();
    if(str.size() != 1 || !islower(str[0]))
    {
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Literka musi byc jednym znakiem[a-z]!");
        return;
    }
    if(zuzyteliterki.find(str[0]) != string::npos)
    {
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Ta literka juz byla uzyta!");
        return;
    }
    string runda = to_string(zuzyteliterki.size()+1);
    string komunikat = "115/" + str + "/"+runda;
    QString qkomunikat = QString::fromStdString(komunikat);
    sock->write(qkomunikat.toUtf8());
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append("Wyslano literke!");
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::socketConnected(){
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append("Laczenie z serwerem gry...");
}

void MainWindow::socketReadable(){
    QByteArray ba = sock->readAll();
    if(QString::fromUtf8(ba).trimmed()=="100") //przyjeto polaczenie
{
        auto txt = ui->lineEdit->text().trimmed();
        if(txt.isEmpty())
            return;
        sock->write((txt).toUtf8());
        return;
    }
    if(QString::fromUtf8(ba).trimmed()=="101") // gra jest w lobby
{
        ui->z1->setVisible(false);
        ui->z2->setVisible(false);
        ui->z3->setVisible(false);
        ui->z4->setVisible(false);
        ui->z5->setVisible(false);
        ui->z6->setVisible(false);
        ui->z7->setVisible(false);
        ui->z8->setVisible(false);
        ui->groupBox->setEnabled(true);
        ui->lineEdit->setEnabled(false);
        ui->dolaczButton->setEnabled(false);
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Polaczono z gra! Oczekiwanie na pozostalych uczestnikow...");
        return;
    }
    if(QString::fromUtf8(ba).trimmed()=="401") //zla nazwa, wypad
{
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Podano nieprawidlowa nazwe uzytkownika, sprobuj ponownie!");
        sock->disconnect();
        return;
    }
    if(QString::fromUtf8(ba).trimmed() == "202"){//wygrana

        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("ZWYCIESTWO!! BRAWO!!");
        ui->lineEdit->setEnabled(true);
        ui->dolaczButton->setEnabled(true);
        return;
    }
    if(QString::fromUtf8(ba).trimmed() == "302"){//przegrana

        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Tym razem druga druzyna byla lepsza! Sprobuj ponownie!");
        ui->lineEdit->setEnabled(true);
        ui->dolaczButton->setEnabled(true);
        return;
    }
    else{
        vector<string> vector = splits(QString::fromUtf8(ba).trimmed().toStdString(),"/");
        string code = vector[0];
        string haslo;
        string dobreliterki;
        string zleliterki;
        string uzyteliterki;
        QString quzyteliterki;
        QString zakrytehaslo;
        if(code == "102") // gra zaczyna sie
        {
            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Polaczono z gra! Masz 15 sekund na wybor literki!");
            haslo = vector[1];
            if(vector.size() == 4)//gra juz trwa
            {
                dobreliterki = vector[2];
                zleliterki = vector[3];
                zleliterki.erase(remove(zleliterki.begin(),zleliterki.end(),'^'),zleliterki.end());
                dobreliterki.erase(remove(dobreliterki.begin(),dobreliterki.end(),'^'),dobreliterki.end());
                zakrytehaslo =  QString::fromStdString(zakryjhaslo(haslo,dobreliterki));
                uzyteliterki = dobreliterki + zleliterki;
                zuzyteliterki = uzyteliterki;
                quzyteliterki = QString::fromStdString(uzyteliterki);
                ui->textBrowser_4->clear();
                ui->textBrowser_4->append(quzyteliterki);
                ui->textBrowser_3->clear();
                ui->textBrowser_3->append(zakrytehaslo);
                rysujwisielca(zleliterki.size());
        }
        }
        if(code == "201"){ //wybrano dobra

            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Udalo wam sie wybrac dobra literke!Masz 15 sekund na wybor kolejnej!");
            haslo = vector[1];
            if(vector.size() == 4)
            {
                dobreliterki = vector[2];
                zleliterki = vector[3];
                zleliterki.erase(remove(zleliterki.begin(),zleliterki.end(),'^'),zleliterki.end());
                dobreliterki.erase(remove(dobreliterki.begin(),dobreliterki.end(),'^'),dobreliterki.end());
                zakrytehaslo =  QString::fromStdString(zakryjhaslo(haslo,dobreliterki));
                uzyteliterki = dobreliterki + zleliterki;
                zuzyteliterki = uzyteliterki;
                quzyteliterki = QString::fromStdString(uzyteliterki);
                ui->textBrowser_4->clear();
                ui->textBrowser_4->append(quzyteliterki);
                ui->textBrowser_3->clear();
                ui->textBrowser_3->append(zakrytehaslo);
                rysujwisielca(zleliterki.size());
            }

        }
        if(code == "301"){//wybrano zla

            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Nastepnym razem wam sie uda!Masz na to 15 sekund!");
            haslo = vector[1];
            if(vector.size() == 4)
            {
                dobreliterki = vector[2];
                zleliterki = vector[3];
                zleliterki.erase(remove(zleliterki.begin(),zleliterki.end(),'^'),zleliterki.end());
                dobreliterki.erase(remove(dobreliterki.begin(),dobreliterki.end(),'^'),dobreliterki.end());
                zakrytehaslo =  QString::fromStdString(zakryjhaslo(haslo,dobreliterki));
                uzyteliterki = dobreliterki + zleliterki;
                zuzyteliterki = uzyteliterki;
                quzyteliterki = QString::fromStdString(uzyteliterki);
                ui->textBrowser_4->clear();
                ui->textBrowser_4->append(quzyteliterki);
                ui->textBrowser_3->clear();
                ui->textBrowser_3->append(zakrytehaslo);
                rysujwisielca(zleliterki.size());
        }
        }
    }
    setTimerForSendButton();
}

void MainWindow::socketDisconnected(){

    ui->textBrowser_2->clear();
    ui->textBrowser_2->append("Rozlaczono z serwerem gry!");
    ui->textBrowser_2->append("Podejmij nowa probe polaczenia!");
    ui->groupBox->setEnabled(false);
    ui->lineEdit->setEnabled(true);
    ui->dolaczButton->setEnabled(true);
    ui->z1->setVisible(false);
    ui->z2->setVisible(false);
    ui->z3->setVisible(false);
    ui->z4->setVisible(false);
    ui->z5->setVisible(false);
    ui->z6->setVisible(false);
    ui->z7->setVisible(false);
    ui->z8->setVisible(false);
}

vector<string> MainWindow::splits(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

string MainWindow::zakryjhaslo(const string& s,const string& odkryte)
{
    string result = s;
    for(string::iterator it = result.begin();it != result.end();++it)
    {
        if(odkryte.find(*it)==string::npos)
        {
            *it = '_';
        }
    }
    return result;
}

void MainWindow::rysujwisielca(int i)
{
    switch(i)
    {
    case 1:
    ui->z1->setVisible(true);
        break;
    case 2:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
        break;
    case 3:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
        break;
    case 4:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
    ui->z4->setVisible(true);
        break;
    case 5:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
    ui->z4->setVisible(true);
    ui->z5->setVisible(true);
        break;
    case 6:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
    ui->z4->setVisible(true);
    ui->z5->setVisible(true);
    ui->z6->setVisible(true);
        break;
    case 7:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
    ui->z4->setVisible(true);
    ui->z5->setVisible(true);
    ui->z6->setVisible(true);
    ui->z7->setVisible(true);
        break;
    case 8:
    ui->z1->setVisible(true);
    ui->z2->setVisible(true);
    ui->z3->setVisible(true);
    ui->z4->setVisible(true);
    ui->z5->setVisible(true);
    ui->z6->setVisible(true);
    ui->z7->setVisible(true);
    ui->z8->setVisible(true);
        break;

    }
}

void MainWindow::setTimerForSendButton()
{
    ui->pushButton_2->setEnabled(true);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [&]{
        timer->deleteLater();
        timer=nullptr;
        ui->pushButton_2->setEnabled(false);
    });
    timer->start(15000);
}
