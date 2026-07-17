#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPaintEvent>

class Register : public QWidget {
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onSignUpClicked();

signals:
    void SignUpSuccess();
signals:
    void goToLogin(); // سیگنال بازگشت به صفحه لاگین

private:
    QFrame *signupframe;
    QLabel *lblwelcome;
    QLabel *lblsubtitle;

    QLabel *lblusername;
    QLineEdit *leusername;

    QLabel *lblemail;
    QLineEdit *leemail;

    QLabel *lblpassword;
    QLineEdit *lepassword;

    QLabel *lblconfirmpassword;
    QLineEdit *leconfirmpassword;

    QCheckBox *chkterms;
    QPushButton *btnsignup;

    QLabel *lblsignin;
    QPushButton *btnsignin;
};

#endif // REGISTER_H