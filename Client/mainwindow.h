#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>

#include "login.h"
#include "home.h"
#include "register.h"
#include "cartwidget.h"
#include "Cart.h"

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
    CartWidget *CartPage; // 👈 اضافه شد: پوینتر صفحه سبد خرید
    Cart *mainCart;       // 👈 اضافه شد: پوینتر به بک‌اند مشترک سبد خرید
};

#endif // MAINWINDOW_H