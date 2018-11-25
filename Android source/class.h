#ifndef CLASS_H
#define CLASS_H
#include<stack>
#include<queue>
#include<string>
#include<cmath>
#include <QWidget>
#include<QApplication>
#include<QGridLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QKeyEvent>

extern long double ans;
extern bool reset;


class Button:public QPushButton{
    Q_OBJECT
protected:
    QString symbol;
public:
    Button(const QIcon &icon, const QString &text, QLineEdit *parent,QString _symbol);
public slots:
    void receiveClick();

signals:
    void sendClick(QString);
};

class DoubleButton:public Button{
    Q_OBJECT
public:
    DoubleButton(const QIcon &icon, const QString &text, QLineEdit *parent,QString _symbol);
signals:
    void sendDoubleClick(QString);
protected:
    void mouseDoubleClickEvent(QMouseEvent*) override;
};


class Eval:public QLabel{
    Q_OBJECT
public:
    Eval(const QString &text, QWidget *parent = nullptr);
public slots:
    void calculate(QString qstr);

};

class Expression:public QLineEdit{
    Q_OBJECT
public:
    Expression(const QString &contents, QWidget *parent = nullptr);
public slots:
    void action(QString s);
    void check(QString);
    void complete();
    void receiveDoubleClick(QString);
signals:
    void calculate(QString);
    void backnext(QString);
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

class Window:public QWidget{
    Eval* eval;
    Expression* expr;
public:
    Window();
};


class CalculateWork{
public:
    class Note{
    public:
        Note(char op){
            isoperand=false;
            this->op=op;
        }
        Note(long double num){
            isoperand=true;
            this->num=num;
        }
        bool isoperand;
        char op=0;
        long double num=0;

    };

    static size_t findParenRight(std::string str,size_t pos);

    static int order(const char c){
        if(c=='('||c==')') return 0;
        if(c=='+'||c=='-') return 1;
        if(c=='*'||c=='/') return 2;
        if(c=='^'||c=='l') return 3;
        else return -1;
    }

    static long double calculate(char c,long double num1,long double num2);
    static long double calculator(std::string str);

};

class DataNode{
public:
    DataNode(QString _expression,QString _result,DataNode* _prev,DataNode* _next);
QString expression;
QString result;
DataNode* prev;
DataNode* next;
};

class Data{
public:
    DataNode* first=nullptr;
    DataNode* last=nullptr;
    DataNode* current=nullptr;
    int num=0;
    void push(QString _expression, QString _result);
    void gonext();
    void goprev();
};
extern Data history;




















#endif // CLASS_H
