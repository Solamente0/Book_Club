#include "mainwindow.h"
#include "login.h"
#include "home.h"
#include "register.h"
#include "Cart.h"
#include "cartwidget.h"
#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox> // 👈 اضافه شد برای نمایش پیام خرید موفق (اختیاری)

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    resize(700,700);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry(); // واسه اینکه بیفته وسط صفحه لپتاپ

    move(
        screenGeometry.center().x() - width() / 2,
        screenGeometry.center().y() - height() / 2
        );

    stack = new QStackedWidget(this);

    mainCart = new Cart();


    LoginPage = new login(this);
    HomePage = new home(this);
    RegisterPage = new Register(this);
    CartPage = new CartWidget(mainCart, this); // ۲. 👈 ساخت ویجت سبد خرید و ارسال پوینتر بک‌اند به آن


    stack->addWidget(LoginPage);
    stack->addWidget(HomePage);
    stack->addWidget(RegisterPage);
    stack->addWidget(CartPage); // ۳. 👈 اضافه کردن ویجت سبد خرید به استک (ایندکس ۳)

    connect(LoginPage, &login::SignInSuccess, this, [this]() {
        stack->setCurrentWidget(HomePage);
    });


    connect(LoginPage, &login::GoToSignUp, this, [this]() {
        stack->setCurrentWidget(RegisterPage);
    });


    connect(RegisterPage, &Register::goToLogin, this, [this]() {
        stack->setCurrentWidget(LoginPage);
    });

    connect(RegisterPage,&Register::SignUpSuccess,this,[this]()
            {stack->setCurrentWidget(LoginPage);
            });

    connect(HomePage, &home::cartRequested, this, [this]() {
        CartPage->updateUI(); // بسیار مهم: لیست کتاب‌ها و مبالغ فاکتور را قبل از نمایش، آپدیت کن
        stack->setCurrentWidget(CartPage);
    });

    // ب) کلیک روی دکمه بازگشت در سبد خرید -> برگشت به هوم‌پیج
    connect(CartPage, &CartWidget::backToHomeRequested, this, [this]() {
        stack->setCurrentWidget(HomePage);
    });

    // ج) نهایی‌سازی خرید موفق -> نمایش پیام و بازگشت به هوم‌پیج
    connect(CartPage, &CartWidget::checkoutSuccessful, this, [this]() {
        QMessageBox::information(this, "Success", "Thank you for your purchase! Books added to your library.");
        stack->setCurrentWidget(HomePage);
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stack);

    stack->setCurrentWidget(LoginPage);


};