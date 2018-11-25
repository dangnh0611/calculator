#include "class.h"
using namespace std;

long double ans=0;
bool reset=false;
Data history;

Window::Window(){
    QPalette global_pal;
    global_pal.setBrush(QPalette::Window,QColor("#303030"));
    this->setPalette(global_pal);

    setWindowIcon(QIcon(":/icons/cal.png"));
    eval=new Eval("",this);
    eval->setAutoFillBackground(true);
    eval->setFont(QFont("Bold",32,-1));
    eval->setAlignment(Qt::AlignRight);
    eval->setTextInteractionFlags(Qt::TextSelectableByMouse);
    eval->setToolTip("Result screen");
    QPalette pal;
    pal.setBrush(QPalette::Window,QColor("#DDDDDD"));
    eval->setPalette(pal);

    expr=new Expression("",this);
    expr->setFont(QFont("Bold",28,-1));
    expr->setFrame(false);
    expr->setClearButtonEnabled(true);
    expr->setToolTip("Expression screen");

    QPalette expr_pal;
    expr_pal.setBrush(QPalette::Base,QColor("#DDDDDD"));
    expr->setPalette(expr_pal);


    DoubleButton* button_sin=new DoubleButton(QIcon(),"sin|sin⁻¹",expr,"sin()");
    DoubleButton* button_cos=new DoubleButton(QIcon(),"cos|cos⁻¹",expr,"cos()");
    DoubleButton* button_tan=new DoubleButton(QIcon(),"tan|tan⁻¹",expr,"tan()");
    DoubleButton* button_e_pi=new DoubleButton(QIcon(),"π|e",expr,"π");
    Button* button_back =new Button(QIcon(":/icons/back.png"),"",expr,"<");
    Button* button_next =new Button(QIcon(":/icons/next.png"),"",expr,">");
    Button* button_7 =new Button(QIcon(),"7",expr,"7");
    Button* button_8 =new Button(QIcon(),"8",expr,"8");
    Button* button_9 =new Button(QIcon(),"9",expr,"9");
    Button* button_plus = new Button(QIcon(),"+",expr,"+");
    Button* button_D = new Button(QIcon(":/icons/del.png"),"",expr,"DEL");
    Button* button_A = new Button(QIcon(":/icons/ac.png"),"",expr,"AC");
    Button* button_4 = new Button(QIcon(),"4",expr,"4");
    Button* button_5 = new Button(QIcon(),"5",expr,"5");
    Button* button_6 = new Button(QIcon(),"6",expr,"6");
    Button* button_minus = new Button(QIcon(),"-",expr,"-");
    Button* button_leftpar = new Button(QIcon(),"(",expr,"(");
    Button* button_rightpar = new Button(QIcon(),")",expr,")");
    Button* button_1 = new Button(QIcon(),"1",expr,"1");
    Button* button_2 = new Button(QIcon(),"2",expr,"2");
    Button* button_3 = new Button(QIcon(),"3",expr,"3");
    Button* button_mul = new Button(QIcon(),"×",expr,"×");
    Button* button_pow = new Button(QIcon(),"^",expr,"^");
    Button* button_log = new Button(QIcon(),"log",expr,"log");
    Button* button_0 = new Button(QIcon(),"0",expr,"0");
    Button* button_dot = new Button(QIcon(),".",expr,".");
    Button* button_ans = new Button(QIcon(),"Ans",expr,"Ans");
    Button* button_divide = new Button(QIcon(),"÷",expr,"÷");
    Button* button_equal = new Button(QIcon(),"=",expr,"=");

    button_sin->setToolTip("sin(x°)\narcsin(x) in [°]");
    button_cos->setToolTip("cos(x°)\narccos(x) in [°]");
    button_tan->setToolTip("tan(x°)\narctan(x) in [°]");
    button_e_pi->setToolTip("Pi number[pi]\nEuler's number[e]");
    button_back->setToolTip("Previous expression");
    button_next->setToolTip("Next expression");
    button_7->setToolTip("Digit[7]");
    button_8->setToolTip("Digit[8]");
    button_9->setToolTip("Digit[9]");
    button_plus->setToolTip("Add[+]");
    button_D->setToolTip("Backspace");
    button_A->setToolTip("Clear screen");
    button_4->setToolTip("Digit[4]");
    button_5->setToolTip("Digit[5]");
    button_6->setToolTip("Digit[6]");
    button_minus->setToolTip("Subtract[-]");
    button_leftpar->setToolTip("Left parentheses");
    button_rightpar->setToolTip("Right parentheses");
    button_1->setToolTip("Digit[1]");
    button_2->setToolTip("Digit[2]");
    button_3->setToolTip("Digit[3]");
    button_mul->setToolTip("Multiply[*]");
    button_pow->setToolTip("Exponent[^]");
    button_log->setToolTip("Logarithm");
    button_0->setToolTip("Digit[0]");
    button_dot->setToolTip("Dot[.]");
    button_ans->setToolTip("Previous result");
    button_divide->setToolTip("Divide[/]");
    button_equal->setToolTip("Calculate result");

    button_sin->setFont(QFont("",13));
    button_cos->setFont(QFont("",13));
    button_tan->setFont(QFont("",13));
    button_e_pi->setFont(QFont("",15));
    button_log->setFont(QFont("",17));
    button_pow->setFont(QFont("",32,70));
    button_leftpar->setFont(QFont("",20));
    button_rightpar->setFont(QFont("",20));
    button_plus->setFont(QFont("",30,80));
    button_minus->setFont(QFont("",38,80));
    button_mul->setFont(QFont("",28,80));
    button_divide->setFont(QFont("",28,80));
    button_equal->setFont(QFont("",30));
    button_ans->setFont(QFont("",16));
    button_dot->setFont(QFont("",30,90));
    QPalette button_pal;
    button_pal.setBrush(QPalette::Button,QColor("#EE3000"));
    button_equal->setPalette(button_pal);

    connect(button_A,SIGNAL(clicked()),eval,SLOT(clear()));
    connect(expr,SIGNAL(calculate(QString)),eval,SLOT(calculate(QString)));
    connect(expr,SIGNAL(textChanged(QString)),expr,SLOT(check(QString)));
    connect(expr,SIGNAL(editingFinished()),expr,SLOT(complete()));
    connect(expr,SIGNAL(textChanged(QString)),eval,SLOT(clear()));
    connect(expr,SIGNAL(backnext(QString)),eval,SLOT(setText(QString)));

    QVBoxLayout* screen_layout=new QVBoxLayout(this);
    screen_layout->addWidget(expr);
    screen_layout->addWidget(eval);
    screen_layout->setSpacing(0);
    QWidget* screen=new QWidget(this);
    screen->setLayout(screen_layout);

    QGridLayout* button_layout=new QGridLayout(this);
    button_layout->setSpacing(0);
    button_layout->setColumnStretch(0,2);
    button_layout->setColumnStretch(1,2);
    button_layout->setColumnStretch(2,1);
    button_layout->setColumnStretch(3,1);
    button_layout->setColumnStretch(4,2);

    button_layout->addWidget(button_sin,0,0);
    button_layout->addWidget(button_cos,0,1);
    button_layout->addWidget(button_back,0,2);
    button_layout->addWidget(button_next,0,3);
    button_layout->addWidget(button_A,0,4);

    button_layout->addWidget(button_tan,1,0);
    button_layout->addWidget(button_e_pi,1,1);
    button_layout->addWidget(button_log,1,2,1,2);
    button_layout->addWidget(button_D,1,4);

    button_layout->addWidget(button_leftpar,2,0);
    button_layout->addWidget(button_rightpar,2,1);
    button_layout->addWidget(button_pow,2,2,1,2);
    button_layout->addWidget(button_plus,2,4);

    button_layout->addWidget(button_7,3,0);
    button_layout->addWidget(button_8,3,1);
    button_layout->addWidget(button_9,3,2,1,2);
    button_layout->addWidget(button_minus,3,4);

    button_layout->addWidget(button_4,4,0);
    button_layout->addWidget(button_5,4,1);
    button_layout->addWidget(button_6,4,2,1,2);
    button_layout->addWidget(button_mul,4,4);

    button_layout->addWidget(button_1,5,0);
    button_layout->addWidget(button_2,5,1);
    button_layout->addWidget(button_3,5,2,1,2);
    button_layout->addWidget(button_divide,5,4);

    button_layout->addWidget(button_0,6,0);
    button_layout->addWidget(button_dot,6,1);
    button_layout->addWidget(button_ans,6,2,1,2);
    button_layout->addWidget(button_equal,6,4);
    QWidget* button=new QWidget(this);
    button->setLayout(button_layout);

    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->setMargin(5);
    layout->addWidget(screen,1);
    layout->addWidget(button,2);
    this->setLayout(layout);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Button::Button(const QIcon &icon, const QString &text, QLineEdit *parent,QString _symbol):QPushButton(icon,text,parent),symbol(_symbol){
    setFont(QFont("",18,90));
    QPalette pal;
    pal.setBrush(QPalette::Button,QColor("#303030"));
    pal.setBrush(QPalette::ButtonText,QColor("#EEEEEE"));
    this->setPalette(pal);
    this->setIconSize(QSize(60,60));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setFocusPolicy(Qt::NoFocus);
    connect(this,SIGNAL(clicked()),this,SLOT(receiveClick()));
    connect(this,SIGNAL(sendClick(QString)),this->parent(),SLOT(action(QString)));
}

void Button::receiveClick(){
    emit sendClick(symbol);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DoubleButton::DoubleButton(const QIcon &icon, const QString &text, QLineEdit *parent,QString _symbol):Button(icon,text,parent,_symbol){
    connect(this,SIGNAL(sendDoubleClick(QString)),this->parent(),SLOT(receiveDoubleClick(QString)));
}

void DoubleButton::mouseDoubleClickEvent(QMouseEvent*)
{
    emit sendDoubleClick(symbol);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Eval::Eval(const QString &text, QWidget *parent):QLabel(text,parent){
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Eval::calculate(QString qstr){
    QString temp_str=qstr;
    qstr.replace("log","l");
    qstr.replace(QChar(247),'/');
    qstr.replace(QChar(215),'*');
    qstr.replace(QChar(960),"pi");

    std::string str=qstr.toStdString();
    try{
    ans=CalculateWork::calculator(str);
    }
    catch(QString error){
        setText(error);
        return;
    };
    QString result=QString::number(static_cast<double>(ans),'g',15);
    setText(result);
    reset=true;
    history.push(temp_str,result);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Expression::Expression(const QString &contents, QWidget *parent):QLineEdit (contents,parent){
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Expression::action(QString s){
    if(s=="DEL"){
        reset=false;
        backspace();
    }
    else if(s=="AC"){
        setText("");
    }
    else if(s=="="){
        emit calculate(text());
    }
    else if(s=="<"){
        if(reset==true){
            history.goprev();
            setText(history.current->expression);
            emit backnext(history.current->result);
        }
        else{
            if(!history.num){}
            else{
                setText(history.current->expression);
                emit backnext(history.current->result);
                reset=true;
            }
        }
    }
    else if(s==">"){
        if(reset==true){
            history.gonext();
            setText(history.current->expression);
            emit backnext(history.current->result);
        }
        else{
            if(!history.num){}
            else{
                setText(history.current->expression);
                emit backnext(history.current->result);
                reset=true;
            }
        }
    }
    else{
        if(reset==false) insert(s);
        else{
            reset=false;
            setText("");
            if(s=="+"||s=="-"||s=="×"||s=="÷"||s=="^") insert("Ans"+s);
            else insert(s);
        }
        if(s=="sin()"||s=="cos()"||s=="tan()") cursorBackward(false,1);
    }
}


void Expression::check(QString str){
    int pos=cursorPosition();
    str=str.replace('/',QChar(247));
    str=str.replace('*',QChar(215));
    setText(str);
    setCursorPosition(pos);

}

void Expression::complete(){
    setCursorPosition(text().length());
    emit calculate(text());
}

void Expression::receiveDoubleClick(QString symbol)
{
    if(symbol=="π"){
        backspace();
        insert("e");
    }
    else{
        cursorBackward(false,4);
        insert("a");
        cursorForward(false,4);
    }
}

void Expression::mouseReleaseEvent(QMouseEvent *event)
{
    reset=false;
    QLineEdit::mouseReleaseEvent(event);
}

void Expression::keyPressEvent(QKeyEvent* event)
{
    if(reset==false) QLineEdit::keyPressEvent(event);
    else{
    int key=event->key();
    switch(key){
    case Qt::Key_Left:
        cursorBackward(false);
    case Qt::Key_Up:
        reset=false;
        break;
    case Qt::Key_Return:
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Tab:
    case Qt::Key_Alt:
        break;
    case Qt::Key_Delete:
        reset=false;
        setText("");
        break;
    case Qt::Key_Backspace:
        reset=false;
        backspace();
        break;
    case Qt::Key_Plus:
        reset=false;
        setText("");
        insert("Ans+");
        break;
    case Qt::Key_Minus:
        reset=false;
        setText("");
        insert("Ans-");
        break;
    case Qt::Key_Asterisk:
        reset=false;
        setText("");
        insert("Ans×");
        break;
    case Qt::Key_Slash:
        reset=false;
        setText("");
        insert("Ans÷");
        break;
    default:
        reset=false;
        setText("");
        insert(event->text());
    }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t CalculateWork::findParenRight(string str,size_t pos)
{
    size_t n=1;
    while(n!=0&&(pos<str.length())){
        if(str[pos]=='(') n++;
        else if(str[pos]==')') n--;
        else{}
        pos++;
    }
    if(n==0) return pos;
    else throw QString("Syntax Error!");
}

long double CalculateWork::calculate(char c,long double num1,long double num2){
    switch(c){
    case '+':return num1+num2;
    case '-':return num1-num2;
    case '*':return num1*num2;
    case '/':
        if(num2==0) throw QString("Math Error!");
        else return num1/num2;
    case '^':return pow(num1,num2);
    case 'l':
        if(num1==1||num2==0) throw QString("Math Error!");
        else return log(num2)/log(num1);
    default:throw QString("Syntax Error!");
    }
}

long double CalculateWork::calculator(string str){

        //CONVERT INFIX NOTATION TO POSTFIX NOTATION
   queue<Note> expr;
   stack<Note> cal;
   stack<char> stk;
   size_t pos=0;
   bool isoperand=true;
   while(pos<str.length()){
       char c=str[pos];
       if(c=='(') isoperand=false;
       if(isoperand==false){
           pos++;
           if(order(c)==-1) throw QString("Syntax Error!");
           else if(c=='('){stk.push(c);isoperand=true;}
           else if(c==')'){
               bool isOK=false;
               while(!stk.empty()&&!isOK){
                   if(stk.top()=='('){isOK=true;}
                   else{
                   expr.push(Note(stk.top()));
                   }
                   stk.pop();
               }
               if(isOK==false) throw QString("Syntax Error!");
           }
           else{
               while(!stk.empty()){
                    if(order(stk.top())>order(c)){
                    expr.push(Note(stk.top()));
                    stk.pop();
                    }
                    else if(order(stk.top())<order(c)){break;}
                    else{
                        if(order(c)==1||order(c)==2){
                            expr.push(Note(stk.top()));
                            stk.pop();
                        }
                        else break;
                    }
                }
               stk.push(c);
               isoperand=true;
           }
       }
       else{
           long double d;
           if(str.substr(pos,3)=="Ans"){
               d=ans;
               pos+=3;
           }
           else if(str.substr(pos,2)=="pi"){
               d=M_PI;
               pos+=2;
           }
           else if(str[pos]=='e'){
               d=M_E;
               pos+=1;
           }
           else if(str.substr(pos,4)=="sin("){
               size_t pos2=findParenRight(str,pos+4);
               d=sin(calculator(str.substr(pos+4,pos2-pos-5))*M_PI/180);
               pos=pos2;
           }
           else if(str.substr(pos,4)=="cos("){
               size_t pos2=findParenRight(str,pos+4);
               d=cos(calculator(str.substr(pos+4,pos2-pos-5))*M_PI/180);
               pos=pos2;
           }
           else if(str.substr(pos,4)=="tan("){
               size_t pos2=findParenRight(str,pos+4);
               d=tan(calculator(str.substr(pos+4,pos2-pos-5))*M_PI/180);
               pos=pos2;
           }
           else if(str.substr(pos,5)=="asin("){
               size_t pos2=findParenRight(str,pos+5);
               long double temp=calculator(str.substr(pos+5,pos2-pos-6));
               if(temp<-1||temp>1) throw QString("Math Error!");
               d=asin(temp)*180/M_PI;
               pos=pos2;
           }
           else if(str.substr(pos,5)=="acos("){
               size_t pos2=findParenRight(str,pos+5);
               long double temp=calculator(str.substr(pos+5,pos2-pos-6));
               if(temp<-1||temp>1) throw QString("Math Error!");
               d=acos(temp)*180/M_PI;
               pos=pos2;
           }
           else if(str.substr(pos,5)=="atan("){
               size_t pos2=findParenRight(str,pos+5);
               d=atan(calculator(str.substr(pos+5,pos2-pos-6)))*180/M_PI;
               pos=pos2;
           }
           else{
           size_t temp_pos;
           try{
           d=stold(str.substr(pos),&temp_pos);
           }
           catch(exception){
               throw QString("Syntax Error!");
           }
           pos+=temp_pos;
           }
           expr.push(Note(d));
           isoperand=false;
       }
   }
   while(!stk.empty()){
       if(stk.top()=='(') throw QString("Syntax Error!");
       expr.push(Note(stk.top()));
       stk.pop();
   }

   //CALCULATE THE POSTFIX EXPRESSION
   while(!expr.empty()){
       if(expr.front().isoperand==true){
           cal.push(Note(expr.front().num));
           expr.pop();
       }
       else{
           Note note1(cal.top());
           cal.pop();
           if(cal.empty()) throw QString("Syntax Error!");
           Note note2(cal.top());
           cal.pop();
           cal.push(Note(calculate(expr.front().op,note2.num,note1.num)));
           expr.pop();
       }
   }
   if(cal.empty()) throw QString("Syntax Error!");
   long double eval=cal.top().num;
   cal.pop();
   if(!cal.empty()) throw QString("Syntax Error!");
   else return eval;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataNode::DataNode(QString _expression, QString _result,DataNode* _prev,DataNode* _next):expression(_expression),result(_result),prev(_prev),next(_next){}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Data::push(QString expression, QString result){
if(num<20){
    if(!num){
        first=new DataNode(expression,result,nullptr,nullptr);
        last=first;
        current=last;
        num++;
    }
    else{
        last->next=new DataNode(expression,result,last,nullptr);
        last=last->next;
        current=last;
        num++;
    }
}
    else{
        DataNode* tempNode=first;
        first=first->next;
        first->prev=nullptr;
        delete tempNode;
        last->next=new DataNode(expression,result,last,nullptr);
        last=last->next;
        current=last;
    }
}

void Data::gonext(){
    if(current->next) current=current->next;
    else{}
}

void Data::goprev(){
    if(current->prev) current=current->prev;
    else{}
}
