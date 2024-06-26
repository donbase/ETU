#include "interface.h"
#include "common.h"
#include <string>
#include <iostream>

#define X_START 50
Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №6");
    setFixedSize(600, 500);
    int x = 50;
    int y = 20;
    int w = 30;
    int h = 25;
    a_numer = new QLineEdit*[SIZE1*SIZE2];
    a_denom = new QLineEdit*[SIZE1*SIZE2];
    delimeter_a = new QLabel*[SIZE1*SIZE2];



    for(int i = 0; i < SIZE1*SIZE2; i++){
        a_numer[i] = new QLineEdit("1", this);
        a_numer[i]->setGeometry(x,y,w, h);
        a_denom[i] = new QLineEdit("1", this);
        a_denom[i]->setGeometry(x, y+30, w, h);
        delimeter_a[i]= new QLabel("-------", this);
        delimeter_a[i]->setGeometry(x, y+15, w, h);
        x += 40;
        if ((i+1) % SIZE2 == 0){
            x = X_START;
            y+= 70;
        }

    }



    name_size = new QLabel("Size of matrix = ", this);
    name_size->setGeometry(320, 20, 120, h);
    size = new QLineEdit("3", this);
    size->setGeometry(430, 20, 25, h);
    eq = new QLabel("X", this);
    eq->setGeometry(460, 20, 15, h);
    size2 = new QLineEdit("3", this);
    size2->setGeometry(480, 20, 25, h);
    set_size_btn = new QPushButton("Set size", this);
    set_size_btn->setGeometry(530, 20, 60, h);


    find_det_btn = new QPushButton("Find Det", this);
    find_det_btn->setGeometry(350, 70, 240, h);

    find_rank_btn = new QPushButton("Find Rank", this);
    find_rank_btn->setGeometry(350, 120, 240, h);

    do_trans_btn = new QPushButton("Do Transparation ", this);
    do_trans_btn->setGeometry(350, 170, 240, h);
    output = new QLabel(this);
    output->setGeometry(100, 300, 320, 200);

    real_mode = new QRadioButton("Real numbers", this);
    real_mode->setGeometry(350, 200, 150, h);
    complex_mode = new QRadioButton("Complex numbers", this);
    complex_mode->setGeometry(350, 230, 150, h);
    ratio_mode = new QRadioButton("Rational numbers", this);
    ratio_mode->setGeometry(350, 260, 150, h);
    ratio_mode->setChecked(true);







    //enter_value_btn = new QPushButton("ENTER VALUES", this);
    //enter_value_btn->setGeometry(350, 250, 240, h);

    connect(set_size_btn, SIGNAL(pressed()), this, SLOT(create_matrix()));
    connect(find_det_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(find_rank_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(do_trans_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(real_mode, SIGNAL(clicked()), this, SLOT(rebuild_matrix()));
    connect(complex_mode, SIGNAL(clicked()), this, SLOT(rebuild_matrix()));
    connect(ratio_mode, SIGNAL(clicked()), this, SLOT(rebuild_matrix()));


}

Interface::~Interface()
{
    for(int i = 0; i < SIZE; i++){
        delete a_numer[i];
        delete a_denom[i];
        delete delimeter_a[i];
    }
    delete a_numer;
    delete a_denom;
    delete delimeter_a;
    delete name_size;
    delete size;
    delete set_size_btn;
    delete find_det_btn;
    delete find_rank_btn;
    delete do_trans_btn;
    delete output;
    delete A;
    //delete enter_value_btn;
    delete output_trans;
    delete eq;
    delete size2;
    delete real_mode;
    delete complex_mode;
    delete ratio_mode;

}


void Interface::formRequest()
{
    QString msg;
    if(real_mode->isChecked()){
        msg << QString().setNum(REAL_MODE)<< QString(';');
        msg << QString::number(SIZE1) << QString(';');
        msg << QString::number(SIZE2) << QString(';');
        for(int i = 0; i < SIZE1*SIZE2; i++)
            msg << a_numer[i]->text() << QString(';');
    }
    else if(complex_mode->isChecked()){
        msg << QString().setNum(COMPLEX_MODE)<< QString(';');
        msg << QString::number(SIZE1) << QString(';');
        msg << QString::number(SIZE2) << QString(';');
        for(int i = 0; i < SIZE1*SIZE2; i++)
            msg << a_numer[i]->text() << QString('/') << a_denom[i]->text() << QString(';');
    }
    else if(ratio_mode->isChecked()){
        msg << QString().setNum(RATIO_MODE)<< QString(';');
        msg << QString::number(SIZE1) << QString(';');
        msg << QString::number(SIZE2) << QString(';');
        for(int i = 0; i < SIZE1*SIZE2; i++)
            msg << a_numer[i]->text() << QString('/') << a_denom[i]->text() << QString(';');
    }

    QPushButton *btn = (QPushButton*)sender();

    if (btn == find_det_btn){
        msg << QString().setNum(PRINT_DET_REQUEST);
    }
    if (btn == find_rank_btn){
        msg << QString().setNum(PRINT_RANK_REQUEST);
        //int l = msg.length();
        //std::cout<<msg.toStdString();
    }
    if (btn == do_trans_btn){
        msg << QString().setNum(PRINT_TRANS_REQUEST);
    }
    emit request(msg);
}



void Interface::answer(QString msg)
{
    QString s;
    int pos = msg.indexOf(';');
    int l = msg.length();
    int ans = msg.left(pos).toInt();




    switch (ans)
    {
        case RANK_ANSWER:
            s += "\tRank(A) = ";
            s += msg.right(l-pos-1);
            output->setText(s);
            //flag_A = true;
            flag_output = true;
            output->show();
            break;
        case DET_ANSWER:
            s += "\tDet(A) = ";
            s += msg.right(l-pos-1);
            output->setText(s);
            //flag_A = true;
            flag_output = true;
            break;
        case TRANS_ANSWER:
            s = "Trans(A) = ";
            s += msg.right(l-2);
            //flag_A = true;
            flag_output = true;
            output->setText(s);
            break;
        default: break;   //!!!!!
    }
}


void Interface::create_matrix(){

    if (flag_output == true){
            delete output;
            flag_output = false;
    }

    int NEW_SIZE1 = size->text().toInt();
    int NEW_SIZE2 = size2->text().toInt();
    int NEW_SIZE = NEW_SIZE1*NEW_SIZE2;


    for(int i = 0; i < SIZE1*SIZE2; i++){
            delete a_numer[i];
            delete a_denom[i];
            delete delimeter_a[i];
    }
    delete a_numer;
    delete a_denom;
    delete delimeter_a;

    int x = 50;
    int y = 20;
    int w = 30;
    int h = 25;
    a_numer = new QLineEdit*[NEW_SIZE1*NEW_SIZE2];
    a_denom = new QLineEdit*[NEW_SIZE1*NEW_SIZE2];
    delimeter_a = new QLabel*[NEW_SIZE1*NEW_SIZE2];



    SIZE1 = NEW_SIZE1;
    SIZE2  = NEW_SIZE2;
    SIZE = NEW_SIZE1*NEW_SIZE2;


    if(ratio_mode->isChecked()){
            for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            a_denom[i]->setGeometry(x, y+30, w, h);
            a_denom[i]->show();
            delimeter_a[i]= new QLabel("-------", this);
            delimeter_a[i]->setGeometry(x, y+15, w, h);
            delimeter_a[i]->show();
            x += 40;
            if ((i+1) % SIZE2 == 0){
                x = X_START;
                y+= 70;
            }

            }
    }

    else if (real_mode->isChecked()){
            for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            //a_denom[i]->setGeometry(x, y+30, w, h);
            //a_denom[i]->show();
            delimeter_a[i]= new QLabel("-------", this);
            //delimeter_a[i]->setGeometry(x, y+15, w, h);
            //delimeter_a[i]->show();
            x += 40;
            if ((i+1) % SIZE2 == 0){
                x = X_START;
                y+= 35;
            }

            }

    }

    else if (complex_mode->isChecked()){

            for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            a_denom[i]->setGeometry(x+40, y, w, h);
            a_denom[i]->show();
            delimeter_a[i]= new QLabel(" i", this);
            delimeter_a[i]->setGeometry(x+70, y, w, h);
            delimeter_a[i]->show();
            x += 100;
            if ((i+1) % SIZE2 == 0){
                x = X_START;
                y+= 40;
            }

            }

    }

    output = new QLabel("Matrix has been created.\n", this);
    output->setGeometry(100, 300, 320, 200);
    output->show();
    flag_output = true;


}


void Interface::rebuild_matrix(){
    for(int i = 0; i < SIZE1*SIZE2; i++){
            delete a_numer[i];
            delete a_denom[i];
            delete delimeter_a[i];
    }
    delete a_numer;
    delete a_denom;
    delete delimeter_a;

    int x = 50;
    int y = 20;
    int w = 30;
    int h = 25;
    a_numer = new QLineEdit*[SIZE1*SIZE2];
    a_denom = new QLineEdit*[SIZE1*SIZE2];
    delimeter_a = new QLabel*[SIZE1*SIZE2];


    if(ratio_mode->isChecked()){
    for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            a_denom[i]->setGeometry(x, y+30, w, h);
            a_denom[i]->show();
            delimeter_a[i]= new QLabel("-------", this);
            delimeter_a[i]->setGeometry(x, y+15, w, h);
            delimeter_a[i]->show();
            x += 40;
            if ((i+1) % SIZE2 == 0){
            x = X_START;
            y+= 70;
            }

    }
    }

    else if (real_mode->isChecked()){
    for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            //a_denom[i]->setGeometry(x, y+30, w, h);
            //a_denom[i]->show();
            delimeter_a[i]= new QLabel("-------", this);
            //delimeter_a[i]->setGeometry(x, y+15, w, h);
            //delimeter_a[i]->show();
            x += 40;
            if ((i+1) % SIZE2 == 0){
            x = X_START;
            y+= 35;
            }

    }

    }

    else if (complex_mode->isChecked()){

    for(int i = 0; i < SIZE1*SIZE2; i++){
            a_numer[i] = new QLineEdit("1", this);
            a_numer[i]->setGeometry(x,y,w, h);
            a_numer[i]->show();
            a_denom[i] = new QLineEdit("1", this);
            a_denom[i]->setGeometry(x+40, y, w, h);
            a_denom[i]->show();
            delimeter_a[i]= new QLabel(" i", this);
            delimeter_a[i]->setGeometry(x+70, y, w, h);
            delimeter_a[i]->show();
            x += 100;
            if ((i+1) % SIZE2 == 0){
            x = X_START;
            y+= 40;
            }

    }

    }


    //output = new QLabel("Matrix has been created.\n", this);
    //output->setGeometry(100, 300, 320, 200);
    //output->show();
    //flag_output = true;

}
