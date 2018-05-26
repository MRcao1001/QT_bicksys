#include "userwindow.h"
#include "ui_userwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QIODevice>
#include <QDateTime>


extern QString name;
extern QString phone_2;
extern QString password;
extern QString bick;
extern QString balance;
extern QString time_0;


QString strAll;
QString chName ;
QString chBick ;
QString chBalance ;
QString nowbl = balance;

userwindow::userwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userwindow)
{
    ui->setupUi(this);
  if (readFromFile() == -1)//在构造函数中调用读取文件操作
   {
      QMessageBox::critical(this,"发生错误","数据出错，请重启程序");
      this->close();
   }


    gettime();
    ui->label_name->setText(name);
    ui->label_bick->setText(bick);
    ui->label_balance->setText(balance);
}

userwindow::~userwindow()
{
    delete ui;
}

long long userwindow::gettime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyyMMddhhmmss");
    long long time = current_date.toLongLong();
    return time;

}


int userwindow::readFromFile()
{
    QFile file("user.dat");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream stream(&file);
    strAll=stream.readAll();
    file.close();

    return 1;
}

int userwindow::upinfo()
{
    ui->label_bick->setText(bick);
    ui->label_balance->setText(nowbl);
}


int userwindow::getbick(QString name)
{
    QString n;//name
    QString p;//phone
    QString w;//words
    QString b;//bick
    QString m;//money
    double balanceNum = balance.toDouble();
    long long timenow = gettime();
    QString timetostring = QString::number(timenow,10);
    //qDebug()<<timetostring;
    QFile file("user.dat");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream strem(&file);
    QStringList strList = strAll.split("\n");
    for(int i =0;i <strList.count();i++)
    {
        if(strList.at(i).contains(name+" "+phone_2+" "+password+" "+bick+" "+balance))
        {
            QString tempStr=strList.at(i);
//            balanceNum =balanceNum-10;
//            QString bl = QString("%1").arg(balanceNum);
            tempStr.replace(0,tempStr.length(),name+" "+phone_2+" "+password+" "+"激情山地车"+" "+balance+" "+timetostring);
            //qDebug()<<"\n"<<tempStr;
            strem<<tempStr<<'\n';
            continue;
        }
        if(i == strList.count()-1)
        {
            strem<<strList.at(i);
            //qDebug()<<"OK";
        }
        else
        {
            strem<<strList.at(i)<<'\n';
            //qDebug()<<"OK";
        }

    }
    file.close();
    return 1;
}
int userwindow::getbick_2(QString name,QString bicktype)
{
    QString n;//name
    QString p;//phone
    QString w;//words
    QString b;//bick
    QString m;//money
    double balanceNum = balance.toDouble();
    long timenow = gettime();
    QString timetostring = QString::number(timenow,10);
    QFile file("user.dat");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream strem(&file);
    QStringList strList = strAll.split("\n");
    for(int i =0;i <strList.count();i++)
    {
        if(strList.at(i).contains(name+" "+phone_2+" "+password+" "+bick+" "+balance))
        {
            QString tempStr=strList.at(i);
//            balanceNum =balanceNum-10;
//           QString bl = QString("%1").arg(balanceNum);
            //qDebug()<<balanceNum;
            tempStr.replace(0,tempStr.length(),name+" "+phone_2+" "+password+" "+bicktype+" "+balance+" "+timetostring);
            //qDebug()<<"\n"<<tempStr;
            strem<<tempStr<<'\n';
            continue;
        }
        if(i == strList.count()-1)
        {
            strem<<strList.at(i);
            qDebug()<<"OK";
        }
        else
        {
            strem<<strList.at(i)<<'\n';
            qDebug()<<"OK";
        }

    }
    file.close();
    return 1;
}
//click函数
void userwindow::on_but_sup_clicked()
{
    QString name = ui->label_name->text();
    double balancenow = balance.toInt();
    if(balancenow < 20)
    {
        QMessageBox::critical(this,"提示","如果您是第一次租车，请先充值300元押金，可以去柜台退还，如果不是请充值使余额大于300元！");
    }
    else if(bick != "暂未租车")
    {
        QMessageBox::critical(this,"提示","您还没有还车，您正在租用"+bick+",请先点击立即还车再租用新的车辆吧");

    }
    else if(getbick(name))
    {
        bick = "激情山地车";
        qDebug()<<"success";
        nowbl = balance;
        upinfo();
        QMessageBox::critical(this,"租车成功","您已成功租用激情山地车，4元每小时，激情，从骑行开始");

    }

}
void userwindow::on_but_chi_clicked()
{
    QString name = ui->label_name->text();
    QString newbick = "安全儿童车";
    double balancenow = balance.toInt();
    if(balancenow < 20)
    {
        QMessageBox::critical(this,"提示","如果您是第一次租车，请先充值300元押金，可以去柜台退还，如果不是请充值使余额大于300元！");
    }
    else if(bick != "暂未租车")
    {
        QMessageBox::critical(this,"提示","您还没有还车，您正在租用"+bick+",请先点击立即还车再租用新的车辆吧");

    }
    else if(getbick_2(name,newbick))
    { 
        bick = "安全儿童车";
        nowbl = balance;
        qDebug()<<"success";
        upinfo();
        QMessageBox::critical(this,"租车成功","您已成功租用安全儿童车，3元每小时，请照顾好骑行的宝宝哦");

    }

}
void userwindow::on_but_love_clicked()
{
    QString name = ui->label_name->text();
    QString newbick = "浪漫情侣车";
    double balancenow = balance.toInt();
    if(balancenow < 20)
    {
        QMessageBox::critical(this,"提示","如果您是第一次租车，请先充值300元押金，可以去柜台退还，如果不是请充值使余额大于300元！");
    }
    else if(bick != "暂未租车")
    {
        QMessageBox::critical(this,"提示","您还没有还车，您正在租用"+bick+",请先点击立即还车再租用新的车辆吧");

    }
    else if(getbick_2(name,newbick))
    {
        bick = "浪漫情侣车";
        nowbl = balance;
        qDebug()<<"success";
        upinfo();
        QMessageBox::critical(this,"租车成功","您已成功租用浪漫情侣车，5元每小时，请尽享甜蜜之旅");

    }

}
void userwindow::on_but_nom_clicked()
{
    QString name = ui->label_name->text();
    QString newbick = "健康小单车";
    double balancenow = balance.toInt();
    if(balancenow < 20)
    {
        QMessageBox::critical(this,"提示","如果您是第一次租车，请先充值300元押金，可以去柜台退还，如果不是请充值使余额大于300元！");
    }
    else if(bick != "暂未租车")
    {
        QMessageBox::critical(this,"提示","您还没有还车，您正在租用"+bick+",请先点击立即还车再租用新的车辆吧");

    }
    else if(getbick_2(name,newbick))
    {
        bick = "健康小单车";
        nowbl = balance;
        upinfo();
        qDebug()<<"success";
        QMessageBox::critical(this,"租车成功","您已成功租用健康小单车，3元每小时，请尽享健康之旅");

    }

}


//充值
int userwindow::getmoney(QString name, QString balance_2)
{
    QString money = balance;
    long long moneytolong = balance.toLongLong();
    long long balance_2tolong = balance_2.toLongLong();
    long balancenow = moneytolong + balance_2tolong;
    QString balancenowtostring = QString::number(balancenow,10);
    qDebug()<< balancenowtostring;
    nowbl = balancenowtostring;
    upinfo();
    QFile file("user.dat");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream strem(&file);
    QStringList strList = strAll.split("\n");
    for(int i =0;i <strList.count();i++)
    {
        if(strList.at(i).contains(name+" "+phone_2+" "+password+" "+bick+" "+balance))
        {
            QString tempStr=strList.at(i);
            tempStr.replace(0,tempStr.length(),name+" "+phone_2+" "+password+" "+bick+" "+balancenowtostring+" "+time_0);
            //qDebug()<<"\n"<<tempStr;
            strem<<tempStr<<'\n';
            continue;
        }
        if(i == strList.count()-1)
        {
            strem<<strList.at(i);
            qDebug()<<"OK";
        }
        else
        {
            strem<<strList.at(i)<<'\n';
            qDebug()<<"OK";
        }

    }
    file.close();
    return 1;
}
void userwindow::on_pushButton_clicked()
{
    QString name = ui->label_name->text();
    QString balance_2 = ui->lineEdit->text();
    double bl = balance.toDouble();
    int blinput = balance_2.toInt();
    if(balance_2 == NULL)
    {
        QMessageBox::critical(this,"提示","充值金额不能为空");
    }
    else if(getmoney(name,balance_2))
    {
        QMessageBox::critical(this,"提示","充值成功！");
        qDebug()<<"success";
    }

}

//还车
void userwindow::on_pushButton_2_clicked()
{
    QString name = ui->label_name->text();
    QString newbick = "暂未租车";
    double balancenow = balance.toInt();
    if(bick == "暂未租车")
    {
        QMessageBox::critical(this,"提示","您还没有租车，选择您喜欢的车型开始城行无忧吧");

    }
    else if(returnbick(name,newbick))
    {
        bick = "暂未租车";
        balancenow =balancenow-10;
        balance = QString("%1").arg(balancenow);
        upinfo();

        qDebug()<<"success";
    }
}

//还车函数
int userwindow::returnbick(QString name,QString bicktype)
{
    long long balanceNum = balance.toLongLong();
    long long timenow = gettime();
    QString pasttime = time_0;
    long long pasttimetolong = pasttime.toLongLong();
    long long usetime = timenow - pasttimetolong;
        long long usetime_2 = usetime/10;
    QString usetimtostring = QString::number(usetime_2,10);
    long long usebalance;
    QString typeofbick =ui->label_bick->text();
    qDebug()<<typeofbick;
    if(typeofbick == "激情山地车")
    {
        usebalance = (usetime / 10)*4;
    }
    else if(typeofbick == "安全儿童车")
    {
        usebalance = (usetime / 10)*3;
    }
    else if(typeofbick == "浪漫情侣车")
    {
        usebalance = (usetime / 10)*5;
    }
    else
    {
        usebalance = (usetime / 10)*2;
    }

    QString usebalancetostring = QString::number(usebalance,10);
    long long balancenow = balanceNum - usebalance;
    QString balancenowtostring = QString::number(balancenow,10);
    nowbl = balancenowtostring;
    QFile file("user.dat");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    QTextStream strem(&file);
    QStringList strList = strAll.split("\n");
    for(int i =0;i <strList.count();i++)
    {
        if(strList.at(i).contains(name+" "+phone_2+" "+password+" "+bick+" "+balance))
        {
            QString tempStr=strList.at(i);
            balanceNum =balanceNum-10;
            QString bl = QString("%1").arg(balanceNum);
            //qDebug()<<balanceNum;
            tempStr.replace(0,tempStr.length(),name+" "+phone_2+" "+password+" "+bicktype+" "+balancenowtostring+" "+"00000000");
            //qDebug()<<"\n"<<tempStr;
            strem<<tempStr<<'\n';
            continue;
        }
        if(i == strList.count()-1)
        {
            strem<<strList.at(i);
            qDebug()<<"OK";
        }
        else
        {
            strem<<strList.at(i)<<'\n';
            qDebug()<<"OK";
        }

    }
    QMessageBox::critical(this,"提示","成功还车!租用时间"+usetimtostring+"小时（5秒为一个小时），扣除费用"+usebalancetostring+"元");
    file.close();
    return 1;
}


