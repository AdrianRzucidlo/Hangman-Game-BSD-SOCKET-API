#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    std::vector<std::string> splits(std::string s, std::string delimiter);
    QTcpSocket * sock {nullptr};
    QTimer * timer{nullptr};
    void dolaczBtnHit();
    void sendBtnHit();
    void socketConnected();
    void socketDisconnected();
    void socketReadable();
    std::string zakryjhaslo(const std::string& s,const std::string& odkryte);
    void rysujwisielca(int i);
    void setTimerForSendButton();
    void Polaczono();
    void ObsluzRunde(std::string dobre, std::string zle,std::string haslo);
    void ObsluzKoniecGry(std::string rankingNasi,std::string rankingPrzeciwnik);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
