#ifndef LOGIN_H
#define LOGIN_H
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
#include <QAction>
#include "home.h"
#include "UserManager.h"
#include "User.h"

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(UserManager *manager, QWidget *parent = nullptr);
    ~login();
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onSignInClicked();
signals:
    void SignInSuccess(User user);
    void GoToSignUp();
    void ForgotPasswordRequested();
private:
    UserManager *userManager;

    QFrame *loginframe;
    QLabel *lblwelcome;
    QLabel *lblsubtitle;
    QLabel *lblusername;
    QLineEdit *leusername;
    QLabel *lblpassword;
    QLineEdit *lepassword;
    QCheckBox *chkrememberme;
    QPushButton *btnforgot;
    QPushButton *btnsignin;
    QLabel *lblsignup;
    QPushButton *btnsignup;
};
#endif // LOGIN_H