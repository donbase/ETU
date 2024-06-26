#include "application.h"
#include "Matrix.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}


void TApplication::recieve(QByteArray msg)
{
    QString answer, s;
    qDebug()<<"=="<<msg<<"==";
    //number* values;
    int l = msg.length();
    int posi = msg.indexOf(';');
    int posi2 = msg.indexOf(';',posi+1);
    int posi3 = msg.indexOf(';',posi2+1);
    //int size = msg.left(posi).toInt(); // кол-во элемов матррицы

    int mode = msg.left(posi).toInt(); // real, complex or ratio
    int size1 = msg.mid(posi+1, posi2-posi-1).toInt(); //кол-во строк
    int size2 = msg.mid(posi2+1, posi3-posi2-1).toInt(); // кол-во столбцов

    //int size1 = msg.left(posi).toInt(); // кол-во строк
    //int size2 = msg.mid(posi+1, posi2-posi-1).toInt(); // кол-во столбцов

    QString rev_msg = QString(msg);
    std::reverse(rev_msg.begin(), rev_msg.end());
    posi = rev_msg.indexOf(';');

    int request = msg.right(posi).toInt();

    int k = 0;
    QString Data = QString(msg);
    QStringList w = Data.split(';');

    Matrix<double> m_real;
    Matrix<Tratio> m_ratio;
    Matrix<Tcomplex> m_complex;


    if(mode == REAL_MODE){
        double values[size1*size2];
        for(int i = 3; i <= size1*size2+2; i++){
            QString tmp = w[i];
            int p = tmp.indexOf('/');
            double a = tmp.left(p).toDouble();
            values[k] = a;
            qDebug()<<QString().setNum(a)<<';';
            k++;
    }
        m_real = Matrix(size1, size2, values);
    }
    else if (mode == RATIO_MODE){
        Tratio values[size1*size2];
        for(int i = 3; i <= size1*size2+2; i++){
            QString tmp = w[i];
            int p = tmp.indexOf('/');
            int a = tmp.left(p).toInt();
            l = tmp.length() - p - 1;
            int b = tmp.right(l).toInt();
            Tratio R(a, b);
            R.evklid(R);
            values[k] = R;
            qDebug()<<QString().setNum(a)<<'/'<<QString().setNum(b);
            k++;

        }
        m_ratio = Matrix(size1, size2, values);
    }

    else if (mode == COMPLEX_MODE){
        Tcomplex values[size1*size2];
        for(int i = 3; i <= size1*size2+2; i++){
            QString tmp = w[i];
            int p = tmp.indexOf('/');
            int a = tmp.left(p).toInt();
            l = tmp.length() - p - 1;
            int b = tmp.right(l).toInt();
            Tcomplex R(a, b);
            values[k] = R;
            qDebug()<<QString().setNum(a)<<'/'<<QString().setNum(b);
            k++;

        }
        m_complex = Matrix(size1, size2, values);
    }



    //double values[size1*size2];// = new double[size1*size2];


    //for(int i = 3; i <= size1*size2+2; i++){
      //  QString tmp = w[i];
        /*if(mode == RATIO_MODE){
        int p = tmp.indexOf('/');
        int a = tmp.left(p).toInt();
        l = tmp.length() - p - 1;
        int b = tmp.right(l).toInt();
        Tratio R(a, b);
        R.evklid(R);
        values[k] = R;
        qDebug()<<QString().setNum(a)<<'/'<<QString().setNum(b);
        k++;
        }*/

        //if(mode == REAL_MODE){
        //int p = tmp.indexOf('/');
        //double a = tmp.left(p).toDouble();
        //l = tmp.length() - p - 1;
        //int b = tmp.right(l).toInt();
        //Tratio R(a, b);
        //R.evklid(R);
        //values[k] = a;
        //qDebug()<<QString().setNum(a)<<';';
        //k++;
        //}
    //}
   // Matrix<double> m = Matrix(size1, size2, values);

    //double trans_m[size1*size2];
    switch (request)
    {
        case PRINT_RANK_REQUEST:
        if(mode == REAL_MODE){
            int res = m_real.rang_mat();
            answer<<QString().setNum(RANK_ANSWER) <<QString(';');
            answer += QString::number(res);
        }
        else if (mode == RATIO_MODE){
            int res = m_ratio.rang_mat();
            answer<<QString().setNum(RANK_ANSWER) <<QString(';');
            answer += QString::number(res);
        }
        else if (mode == COMPLEX_MODE){
            int res = m_complex.rang_mat();
            answer<<QString().setNum(RANK_ANSWER) <<QString(';');
            answer += QString::number(res);
        }
            break;
        case PRINT_DET_REQUEST:
            if (size1 != size2){
            answer<<QString().setNum(DET_ANSWER) <<QString(';');
            answer<<QString("ERROR! Not square matrix!");
            break;
            }

            answer<<QString().setNum(DET_ANSWER) <<QString(';');
            if(mode == REAL_MODE){
                double det = m_real.Det();
                if(isnan(det)) det = 0;
                answer += QString().setNum(det);
            }

            if(mode == RATIO_MODE){
                Tratio det = m_ratio.Det();
                answer<<det;
            }
            if(mode == COMPLEX_MODE){
                Tcomplex det = m_complex.Det();
                answer<<det;
            }
            break;

        case PRINT_TRANS_REQUEST:
            answer<<QString().setNum(TRANS_ANSWER) <<QString(';');

            if(mode == REAL_MODE){
                double ** res;
                res = m_real.Trans();
                for(int i = 0; i < size2; i++){
                    if(i != 0) answer += "\n\t   ";
                    for(int j = 0; j < size1; j++){
                        double tmp = res[i][j];
                        answer<<QString().setNum(tmp);
                        answer<<QString('\t');
                    }
                    delete res[i];
                }
                delete res;
            }

            else if(mode == RATIO_MODE){
                Tratio** res;
                res = m_ratio.Trans();
                for(int i = 0; i < size2; i++){
                    if(i != 0) answer += "\n\t   ";
                    for(int j = 0; j < size1; j++){
                        Tratio tmp = res[i][j];
                        answer<<tmp;
                        answer<<QString('\t');
                    }
                    delete res[i];
                }
                delete res;


            }

            else if(mode == COMPLEX_MODE){
                Tcomplex** res;
                res = m_complex.Trans();
                for(int i = 0; i < size2; i++){
                    if(i != 0) answer += "\n\t   ";
                    for(int j = 0; j < size1; j++){
                        Tcomplex tmp = res[i][j];
                        answer<<tmp;
                        answer<<QString('\t');
                    }
                    delete res[i];
                }
                delete res;


            }






            break;

        default: return;
        }




    comm->send(QByteArray().append(answer.toUtf8()));

    }
