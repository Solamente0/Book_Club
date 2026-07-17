#include "login.h"
#include <QStyleOption>
#include <QPainter>
#include <QMessageBox>
#include <QMessageBox>
#include "home.h"
login::login(QWidget *parent) : QWidget(parent) {
    // ۱. تنظیم نام آبجکت برای اعمال استایل پس‌زمینه بدون ارث‌بری به فرزندان
    this->setObjectName("loginPage");
    this->setStyleSheet(
        "QWidget#loginPage {"
        "   border-image: url(':/resources/images/login_bg.jpg') 0 0 0 0 stretch stretch;"
        "   background-color: #121212;"
        "}"
        );

    // ۲. ساخت لایوت شبکه برای مرکزچین کردن و بزرگ شدن متناسب فرم
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // ۳. ساخت کارت شیشه‌ای اصلی (loginframe)
    loginframe = new QFrame(this);
    loginframe->setObjectName("loginFrame");

    // تنظیم محدوده سایز و فضا دادن به فرم برای Expanding
    loginframe->setMinimumSize(350, 480);
    loginframe->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // استایل شیشه‌ای ملایم و فیکس کردن رنگ متون و فیلدها بدون کادرهای اضافی
    loginframe->setStyleSheet(
        "QFrame#loginFrame {"
        "   background-color: rgba(255, 255, 255, 150);" /* شیشه سفید-کرم محو */
        "   border-radius: 25px;"
        "   border: 1px solid rgba(255, 255, 255, 100);"
        "}"
        "QLabel, QCheckBox {"
        "   color: #000000;" /* مشکی خالص بدون قاب */
        "   background: transparent;"
        "   border: none;"
        "}"
        "QLineEdit {"
        "   background-color: rgba(255, 255, 255, 220);"
        "   border: 1px solid #CCCCCC;"
        "   border-radius: 8px;"
        "   padding: 8px;"
        "   color: #000000;"
        "}"
        "QLineEdit:focus {"
        "   border: 1.5px solid #6F4E37;" /* کادر جگری موقع کلیک روی فیلد */
        "}"
        "QPushButton#signInBtn {"
        "   background-color: #6F4E37;" /* دکمه اصلی جگری */
        "   color: white;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "}"
        "QPushButton#signInBtn:hover { background-color: #A33A4A; }"
        );

    // ۴. لایوت عمودی برای چیدمان متقارن اجزای داخل کارت
    QVBoxLayout *frameLayout = new QVBoxLayout(loginframe);
    frameLayout->setContentsMargins(35, 40, 35, 40);
    frameLayout->setSpacing(15);
    frameLayout->setAlignment(Qt::AlignCenter);

    // ۵. عناوین بالای فرم
    lblwelcome = new QLabel("welcome to Book Club!", loginframe);
    QFont welcomeFont("Segoe UI", 20, QFont::Bold);
    lblwelcome->setFont(welcomeFont);
    lblwelcome->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(lblwelcome);

    lblsubtitle = new QLabel("sign in to continue", loginframe);
    lblsubtitle->setFont(QFont("Segoe UI", 11));
    lblsubtitle->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(lblsubtitle);

    frameLayout->addSpacing(10);

    // ۶. فیلد نام کاربری
    lblusername = new QLabel("username", loginframe);
    lblusername->setFont(QFont("Segoe UI", 10, QFont::DemiBold));
    frameLayout->addWidget(lblusername);

    leusername = new QLineEdit(loginframe);
    leusername->setPlaceholderText("Enter your username");
    leusername->setMinimumHeight(40);
    frameLayout->addWidget(leusername);

    // ۷. فیلد رمز عبور
    lblpassword = new QLabel("password", loginframe);
    lblpassword->setFont(QFont("Segoe UI", 10, QFont::DemiBold));
    frameLayout->addWidget(lblpassword);

    lepassword = new QLineEdit(loginframe);
    lepassword->setPlaceholderText("Enter your password");
    lepassword->setEchoMode(QLineEdit::Password);
    lepassword->setMinimumHeight(40);
    frameLayout->addWidget(lepassword);

    // ۸. ردیف آپشن‌ها (Remember Me و Forgot Password)
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    chkrememberme = new QCheckBox("remember me", loginframe);

    btnforgot = new QPushButton("forgot password?", loginframe);
    btnforgot->setStyleSheet("color: #6F4E37; background: transparent; border: none; text-decoration: underline;");
    btnforgot->setCursor(Qt::PointingHandCursor);

    optionsLayout->addWidget(chkrememberme);
    optionsLayout->addStretch();
    optionsLayout->addWidget(btnforgot);
    frameLayout->addLayout(optionsLayout);

    frameLayout->addSpacing(15);

    // ۹. دکمه اصلی Sign In
    btnsignin = new QPushButton("Sign in", loginframe);
    btnsignin->setObjectName("signInBtn");
    btnsignin->setMinimumHeight(45);
    btnsignin->setCursor(Qt::PointingHandCursor);
    QFont btnFont = btnsignin->font();
    btnFont.setPointSize(12);
    btnsignin->setFont(btnFont);
    frameLayout->addWidget(btnsignin);

    connect(btnsignin, &QPushButton::clicked,
            this, &login::onSignInClicked);

    frameLayout->addSpacing(10);

    // ۱۰. لینک‌های فوتر ثبت‌نام
    QHBoxLayout *signupLayout = new QHBoxLayout();
    signupLayout->setAlignment(Qt::AlignCenter);
    lblsignup = new QLabel("Don't have an account?", loginframe);
    btnsignup = new QPushButton("sign up", loginframe);
    btnsignup->setStyleSheet("color: #6F4E37; background: transparent; border: none; font-weight: bold;");
    btnsignup->setCursor(Qt::PointingHandCursor);

    signupLayout->addWidget(lblsignup);
    signupLayout->addWidget(btnsignup);
    frameLayout->addLayout(signupLayout);
    connect(btnsignup, &QPushButton::clicked, this, [=]() {
        emit GoToSignUp(); // وقتی روی ساین‌آپ در لاگین کلیک شد، این سیگنال جار زده می‌شود
    });

    // ۱۱. سیستم پیاده‌سازی فنرهای گرید (Stretch) برای بزرگ شدن داینامیک و مرکزچین ماندن
    mainLayout->addWidget(loginframe, 1, 1);
    mainLayout->setRowStretch(0, 1);    // فضای آزاد بالا
    mainLayout->setRowStretch(2, 1);    // فضای آزاد پایین
    mainLayout->setColumnStretch(0, 1); // فضای آزاد چپ
    mainLayout->setColumnStretch(2, 1); // فضای آزاد راست

    this->setLayout(mainLayout);
}

// متد نقاشی سفارشی برای وادار کردن QWidget به رندرسازی بک‌گراند QSS
void login::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void login::onSignInClicked()
{
    QString username = leusername->text().trimmed();
    QString password = lepassword->text();

    if (username.isEmpty())
    {
        QMessageBox::warning(this,
                             "Login",
                             "Please enter your username.");

        leusername->setFocus();
        return;
    }

    if (password.isEmpty())
    {
        QMessageBox::warning(this,
                             "Login",
                             "Please enter your password.");

        lepassword->setFocus();
        return;
    }

    emit SignInSuccess();
}

login::~login() {
    // مدیریت حافظه توسط سیستم Parent-Child کیوتی هندل می‌شود
}