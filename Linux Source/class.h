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
/*GLOBAL VARIABLE ans
storing the result of the previous expression
*/
extern long double ans;
/*GLOBAL BOOLEAN VARIABLE state
-Each time editing the expression finished(e.g. press Enter/Return,..),it switch to true
-Each time expression has any changed,or user want to modify the expression
by clicking to the expression area,or press Key_Up,.. it switchs to false;
-State decides the behavior of any operation
e.g. When user inputs an expression and press Return,this time,state=true;
    +if user click button '-' then click button '9' then the expression area will display "Ans-9",it mean take the previous result as Ans,then minus 9
    +if user click the expression area,move the cursor any where,then input something,it will insert to the expression at the cursor position
*/
extern bool state;

//NORMAL BUTTON(e.g. number1-9,plus,minus,..)
class Button:public QPushButton{
    Q_OBJECT
protected:
    QString symbol;
public:
    Button(const QIcon& icon, const QString& text, QLineEdit* parent,QString _symbol);
public slots:
    void receiveClick();
signals:
    void sendClick(QString);
};

//BUTTON ACCEPT DOUBLE-CLICK EVENT(e.g. sin|arcsin,tan|arctan,..)
class DoubleButton:public Button{
    Q_OBJECT
public:
    DoubleButton(const QIcon& icon, const QString& text, QLineEdit* parent,QString _symbol);
signals:
    void sendDoubleClick(QString);
protected:
    void mouseDoubleClickEvent(QMouseEvent*) override;
};

//AREA FOR DISPLAYING THE RESULT
class Eval:public QLabel{
    Q_OBJECT
public:
    Eval(const QString& text, QWidget* parent = nullptr);
public slots:
    void calculate(QString qstr);
};

//AREA FOR MODIFYING THE EXPRESSION,RECEIVING SIGNAL BOTH FROM KEYBOARD AND BUTTON
class Expression:public QLineEdit{
    Q_OBJECT
public:
    Expression(const QString& contents, QWidget* parent = nullptr);
public slots:
    void action(QString s);
    void check(QString);
    void complete();
    void receiveDoubleClick(QString);
signals:
    void calculate(QString);
    void backnext(QString);
protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

//MAIN WINDOWN,CONTAINING EVERYTHING
class Window:public QWidget{
    Eval* eval;
    Expression* expr;
public:
    Window();
};

//UTILITY CLASS,CONTAINING STATIC MEMBERS FOR THE CALCULATING WORK
class CalculatingWork{
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
    //calculate the expression in form of a string
    static long double calculator(std::string str);

};

//CLASS FOR STORING ANY EXPRESSIONS AND RESULTS WHICH HAD BEEN CALCULATED

/*CLASS FOR STORING ANY EXPRESSIONS AND RESULTS WHICH HAD BEEN CALCULATED
 *THIS IS BASED ON DOUBLE-LINKED LIST DATA STRUCTURE*/
class Data{

    //A NODE
    class DataNode{
    public:
        DataNode(QString _expression,QString _result,DataNode* _prev,DataNode* _next);
    QString expression; //storing the expression
    QString result; //storing the result of the expression
    DataNode* prev;
    DataNode* next;
    };

public:
    DataNode* first=nullptr;
    DataNode* last=nullptr;
    DataNode* current=nullptr; //
    int num=0;
    void push(QString _expression, QString _result);
    void gonext();
    void goprev();
};

extern Data history;




















#endif // CLASS_H
