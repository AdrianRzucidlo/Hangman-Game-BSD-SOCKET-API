#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
using namespace std;
string zuzyteliterki;
int wasinlobby;
int mojepunkty;

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
    mojepunkty = 0;
    wasinlobby = 0;
    if(sock)
            delete sock;
    sock = new QTcpSocket(this);
    zuzyteliterki = "";
    sock->connectToHost(ui->lineEdit_3->text(),ui->spinBox->value());
    connect(sock, &QTcpSocket::connected, this, &MainWindow::socketConnected);
    connect(sock, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnected);
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
    if(zuzyteliterki.size() != 0)
    {
        if(zuzyteliterki.find(str[0]) != string::npos)
        {
            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Ta literka juz byla uzyta!");
            return;
        }
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
    ui->lineEdit_3->setEnabled(false);
    ui->spinBox->setEnabled(false);
}

void MainWindow::socketReadable(){

    QByteArray ba = sock->readAll();
    string s = (QString::fromUtf8(ba).trimmed()).toStdString();
    s.pop_back();
    if(s =="100") //przyjeto polaczenie
    {
        auto txt = ui->lineEdit->text().trimmed();
        if(txt.isEmpty())
            return;
        sock->write((txt).toUtf8());
        return;
    }
    if(s =="101") // gra jest w lobby
    {
        wasinlobby = 1;
        Polaczono();
        return;
    }
    if(s =="401") //zla nazwa, wypad
    {
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append("Podano nieprawidlowa nazwe uzytkownika, sprobuj ponownie!");
        sock->disconnect();
        return;
    }
    if(s == "444")
    {
        ui->textBrowser_2->append("Osiagnieto max graczy.");
        sock->disconnect();
    }
    if(s == "201")
    {
        mojepunkty++;
    }
    else{
        vector<string> vector = splits(s,"/");
        string code = vector[0];
        if(wasinlobby == 0)
        {
            Polaczono();
        }
        if(code == "102") // rozgrywka
        {

            ui->pushButton_2->setEnabled(true);
            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Polaczono z gra! Masz 15 sekund na wybor literki!");
            if(vector.size() == 4)
            {
                ObsluzRunde(vector[2],vector[3],vector[1]);
        }
        }
        if(code  == "502"){//przegrana

            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Tym razem druga druzyna byla lepsza! Przegraliscie!");
            ObsluzKoniecGry(vector[1],vector[2]);
            return;
        }
        if(code  == "501"){//wygrana

            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("ZWYCIESTWO!! BRAWO!!");
            ObsluzKoniecGry(vector[1],vector[2]);
            return;
        }
        if(code == "202"){ //wybrano dobra
            ui->pushButton_2->setEnabled(true);
            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Udalo wam sie wybrac dobra literke!Masz 15 sekund na wybor kolejnej!");
            if(vector.size() == 4)
            {
                ObsluzRunde(vector[2],vector[3],vector[1]);
            }

        }
        if(code == "302")//wybrano zla
        {
            ui->pushButton_2->setEnabled(true);

            ui->textBrowser_2->clear();
            ui->textBrowser_2->append("Nastepnym razem wam sie uda!Masz na to 15 sekund!");
            if(vector.size() == 4)
            {
                ObsluzRunde(vector[2],vector[3],vector[1]);
            }
        }
    }
}

void MainWindow::socketDisconnected(){

    ui->textBrowser_2->append("Rozlaczono z serwerem gry!");
    ui->textBrowser_2->append("Podejmij nowa probe polaczenia!");
    ui->lineEdit->setEnabled(true);
    ui->dolaczButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->z1->setVisible(false);
    ui->z2->setVisible(false);
    ui->z3->setVisible(false);
    ui->z4->setVisible(false);
    ui->z5->setVisible(false);
    ui->z6->setVisible(false);
    ui->z7->setVisible(false);
    ui->z8->setVisible(false);
    ui->lineEdit_3->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->textBrowser_2->setEnabled(true);
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

void MainWindow::Polaczono()
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
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::ObsluzRunde(string dobre, string zle,string haslo)
{
    string dobreliterki = dobre;
    string zleliterki = zle;
    zleliterki.erase(remove(zleliterki.begin(),zleliterki.end(),'^'),zleliterki.end());
    rysujwisielca(zleliterki.size());
    zleliterki.erase(remove(zleliterki.begin(),zleliterki.end(),'`'),zleliterki.end());
    dobreliterki.erase(remove(dobreliterki.begin(),dobreliterki.end(),'^'),dobreliterki.end());
    QString zakrytehaslo =  QString::fromStdString(zakryjhaslo(haslo,dobreliterki));
    string uzyteliterki = dobreliterki + zleliterki;
    zuzyteliterki = uzyteliterki;
    QString quzyteliterki = QString::fromStdString(uzyteliterki);
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(quzyteliterki);
    ui->textBrowser_3->clear();
    ui->textBrowser_3->append(zakrytehaslo);
    rysujwisielca(zleliterki.size());
}

void MainWindow::ObsluzKoniecGry(string rankingNasi,string rankingPrzeciwnik)
{
    QString qrankingNasi = QString::fromStdString(rankingNasi);
    ui->textBrowser_2->append("Nasz najlepszy zawodnik i jego punkty:");
    ui->textBrowser_2->append(qrankingNasi);
    QString qrankingPrzeciwnik = QString::fromStdString(rankingPrzeciwnik);
    ui->textBrowser_2->append("Przeciwny najlepszy zawodnik i jego punkty:");
    ui->textBrowser_2->append(qrankingPrzeciwnik);
    ui->textBrowser_2->append("Moje punkty:");
    ui->textBrowser_2->append(QString::number(mojepunkty));
    ui->lineEdit->setEnabled(true);
    ui->dolaczButton->setEnabled(true);
}
