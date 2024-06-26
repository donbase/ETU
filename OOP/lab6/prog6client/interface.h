#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class Interface : public QWidget
{
    Q_OBJECT

    QLabel **delimeter_a;
    QLineEdit **a_numer, **a_denom;
    QLabel *A;
    QLabel *output_trans;
    QLabel  *name_size, *output;
    QLineEdit *size;
    QLineEdit *size2;
    QLabel *eq;

    QPushButton *set_size_btn;
    QPushButton *find_det_btn;
    QPushButton *find_rank_btn;
    QPushButton *do_trans_btn;

    QRadioButton *real_mode;
    QRadioButton *complex_mode;
    QRadioButton *ratio_mode;
   // QPushButton *enter_value_btn;

//    friend QString& operator<< (QString&,const QString&);

public:
    bool flag_A = false;  // check: has memory already been cleaned
    bool flag_output = false; //
    bool flag_trans = false;
    int SIZE1 = 3;
    int SIZE2 = 3;
    int SIZE = 9;
    Interface(QWidget *parent = nullptr);
    ~Interface();
//   !!!!!!!!!!!!!!


public slots:
    void answer(QString);
    void create_matrix();
    void rebuild_matrix();

private slots:
    void formRequest();

signals:
    void request(QString);

};

#endif // INTERFACE_H
