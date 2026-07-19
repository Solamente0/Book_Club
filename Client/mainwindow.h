#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QStackedWidget>
#include "login.h"
#include "home.h"
#include "register.h"
#include "cartwidget.h"
#include "Cart.h"
#include "bookdetailwindow.h"
#include "UserManager.h"
#include "User.h"
#include "genreselectionwidget.h"
#include "forgotpasswordwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    QStackedWidget *stack;
    login *LoginPage;
    home *HomePage;
    Register *RegisterPage;
    CartWidget *CartPage;
    Cart *mainCart;
    BookDetailWidget *BookDetailPage;
    GenreSelectionWidget *GenreSelectionPage;
    UserManager *userManager;
    User currentUser;
    ForgotPasswordWidget *ForgotPasswordPage;
};
#endif // MAINWINDOW_H