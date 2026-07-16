#include "cartwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>

CartWidget::CartWidget(Cart *cart, QWidget *parent)
    : QWidget(parent), m_cart(cart)
{
    // استایل پس‌زمینه هماهنگ با هوم‌پیج
    this->setObjectName("cartPage");
    this->setStyleSheet("QWidget#cartPage { background-color: #FCFCFC; }");

    setupUI();
    updateUI(); // بارگذاری اولیه داده‌ها
}

void CartWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    itemsLayout->setAlignment(Qt::AlignTop);

    // ==========================================
    // ۱. هدر بالای صفحه (آبی ملایم شما)
    // ==========================================
    QWidget *headerWidget = new QWidget(this);
    headerWidget->setMinimumHeight(75);
    headerWidget->setMaximumHeight(75);
    headerWidget->setStyleSheet("background-color: rgba(210, 235, 255, 170); border-bottom: 1px solid rgba(0,0,0,15);");

    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(25, 0, 25, 0);
    headerLayout->setSpacing(15);

    // دکمه بازگشت (استایل صورتی چرک شما)
    QPushButton *btnBack = new QPushButton("⬅ Back to Club", headerWidget);
    btnBack->setCursor(Qt::PointingHandCursor);
    btnBack->setStyleSheet(
        "QPushButton {"
        "   background-color: #f4dbde;"
        "   color: #803040;"
        "   border: none;"
        "   border-radius: 15px;"
        "   padding-left: 15px;"
        "   padding-right: 15px;"
        "   min-height: 35px;"
        "   font-weight: bold;"
        "   font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(244, 219, 222, 220);"
        "}"
        );
    connect(btnBack, &QPushButton::clicked, this, &CartWidget::backToHomeRequested);
    headerLayout->addWidget(btnBack);

    headerLayout->addStretch(1);

    // عنوان صفحه
    QLabel *lblTitle = new QLabel("My Shopping Cart", headerWidget);
    lblTitle->setFont(QFont("Segoe UI", 18, QFont::Bold));
    lblTitle->setStyleSheet("color: #2E4D63; background: transparent;");
    headerLayout->addWidget(lblTitle);

    headerLayout->addStretch(1);
    mainLayout->addWidget(headerWidget);

    // ==========================================
    // ۲. بخش اصلی محتوا (دو ستونه)
    // ==========================================
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(25);


    // الف) ستون چپ: لیست اسکرول‌شونده کتاب‌ها (اصلاح شده)
    // ==========================================
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // غیرفعال کردن اسکرول افقی و فعال کردن اسکرول عمودی
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // ۱. شیشه‌ای کردن خودِ اسکرول اِریا و ویوپورت آن برای جلوگیری از باگ رنگ سفید/خاکستری پس‌زمینه
    scrollArea->setStyleSheet("background: transparent; border: none;");
    scrollArea->viewport()->setStyleSheet("background: transparent;");

    // ۲. 👈 تزریق مستقیم و بدون واسطه استایل به خودِ اسکرول‌بار عمودی
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "   border: none;"
        "   background: rgba(253, 246, 238, 120);"
        "   width: 10px;"
        "   margin: 0px 0px 0px 0px;"
        "   border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #f4dbde;"
        "   min-height: 30px;"
        "   border-radius: 5px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "   background: #803040;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "   background: none;"
        "}"
        );

    scrollWidget = new QWidget(scrollArea);
    scrollWidget->setStyleSheet("background-color: transparent;");

    // هماهنگی سایز چیدمان فرزندان با اسکرول
    scrollWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    itemsLayout = new QVBoxLayout(scrollWidget);
    itemsLayout->setContentsMargins(0, 0, 8, 0); // فاصله کم از راست برای نچسبیدن کارت‌ها به اسکرول‌بار
    itemsLayout->setSpacing(15);

    scrollArea->setWidget(scrollWidget);
    contentLayout->addWidget(scrollArea, 1);

    // ب) ستون راست: فاکتور پرداخت (نارنجی/هلویی ملایم شما)
    QFrame *summaryFrame = new QFrame(this);
    summaryFrame->setFixedWidth(320);
    summaryFrame->setStyleSheet(
        "QFrame {"
        "   background-color: rgba(255, 192, 159, 195);"
        "   border-radius: 20px;"
        "   border: 1px solid rgba(0, 0, 0, 15);"
        "}"
        );

    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryFrame);
    summaryLayout->setContentsMargins(20, 25, 20, 25);
    summaryLayout->setSpacing(18);

    QLabel *lblSummaryTitle = new QLabel("Order Summary", summaryFrame);
    lblSummaryTitle->setFont(QFont("Segoe UI", 16, QFont::Bold));
    lblSummaryTitle->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    summaryLayout->addWidget(lblSummaryTitle);

    // سطر تعداد اقلام
    QHBoxLayout *rowItems = new QHBoxLayout();
    QLabel *lblTotalItemsText = new QLabel("Total Items:", summaryFrame);
    lblTotalItemsText->setStyleSheet("color: #A04E20; font-size: 13px; background: transparent; border: none;");
    lblTotalItemsVal = new QLabel("0", summaryFrame);
    lblTotalItemsVal->setFont(QFont("Segoe UI", 12, QFont::Bold));
    lblTotalItemsVal->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    rowItems->addWidget(lblTotalItemsText);
    rowItems->addStretch();
    rowItems->addWidget(lblTotalItemsVal);
    summaryLayout->addLayout(rowItems);

    // سطر قیمت کل قبل تخفیف
    QHBoxLayout *rowPrice = new QHBoxLayout();
    QLabel *lblTotalPriceText = new QLabel("Price:", summaryFrame);
    lblTotalPriceText->setStyleSheet("color: #A04E20; font-size: 13px; background: transparent; border: none;");
    lblTotalPriceVal = new QLabel("$0.00", summaryFrame);
    lblTotalPriceVal->setFont(QFont("Segoe UI", 12, QFont::Bold));
    lblTotalPriceVal->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    rowPrice->addWidget(lblTotalPriceText);
    rowPrice->addStretch();
    rowPrice->addWidget(lblTotalPriceVal);
    summaryLayout->addLayout(rowPrice);

    // سطر تخفیف کل
    QHBoxLayout *rowDiscount = new QHBoxLayout();
    QLabel *lblDiscountText = new QLabel("Total Discount:", summaryFrame);
    lblDiscountText->setStyleSheet("color: #A04E20; font-size: 13px; background: transparent; border: none;");
    lblDiscountVal = new QLabel("$0.00 (0%)", summaryFrame);
    lblDiscountVal->setFont(QFont("Segoe UI", 12, QFont::Bold));
    lblDiscountVal->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    rowDiscount->addWidget(lblDiscountText);
    rowDiscount->addStretch();
    rowDiscount->addWidget(lblDiscountVal);
    summaryLayout->addLayout(rowDiscount);

    // خط جداکننده (دیوایدر با غلظت ملایم نارنجی شما)
    QFrame *divider = new QFrame(summaryFrame);
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("background-color: rgba(160, 78, 32, 50); max-height: 1px; border: none;");
    summaryLayout->addWidget(divider);

    // سطر مبلغ قابل پرداخت نهایی
    QHBoxLayout *rowFinal = new QHBoxLayout();
    QLabel *lblFinalPriceText = new QLabel("Final Amount:", summaryFrame);
    lblFinalPriceText->setFont(QFont("Segoe UI", 13, QFont::Bold));
    lblFinalPriceText->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    lblFinalPriceVal = new QLabel("$0.00", summaryFrame);
    lblFinalPriceVal->setFont(QFont("Segoe UI", 16, QFont::Bold));
    lblFinalPriceVal->setStyleSheet("color: #A04E20; background: transparent; border: none;");
    rowFinal->addWidget(lblFinalPriceText);
    rowFinal->addStretch();
    rowFinal->addWidget(lblFinalPriceVal);
    summaryLayout->addLayout(rowFinal);

    summaryLayout->addStretch(1);

    // دکمه ثبت و نهایی‌سازی (صورتی چرک شما با هاور ملایم)
    btnCheckout = new QPushButton("Proceed to Checkout 💳", summaryFrame);
    btnCheckout->setMinimumHeight(45);
    btnCheckout->setCursor(Qt::PointingHandCursor);
    btnCheckout->setStyleSheet(
        "QPushButton {"
        "   background-color: #f4dbde;"
        "   color: #803040;"
        "   border: 1px solid rgba(0, 0, 0, 15);"
        "   border-radius: 12px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(244, 219, 222, 220);"
        "}"
        "QPushButton:disabled {"
        "   background-color: rgba(255, 255, 255, 100);"
        "   color: rgba(128, 48, 64, 100);"
        "}"
        );
    connect(btnCheckout, &QPushButton::clicked, this, [this]() {
        if (m_cart->CheckOut()) {
            updateUI();
            emit checkoutSuccessful();
        }
    });
    summaryLayout->addWidget(btnCheckout);

    contentLayout->addWidget(summaryFrame);
    mainLayout->addLayout(contentLayout, 1);
}

// متد ساخت سطر اختصاصی برای هر کتاب درون سبد خرید (کرم پاستلی ملایم شما)
QWidget* CartWidget::createCartItemRow(const Book &book) {
    QFrame *rowFrame = new QFrame(this);
    rowFrame->setFixedHeight(100);
    rowFrame->setStyleSheet(
        "QFrame {"
        "   background-color: rgba(253, 246, 238, 180);"
        "   border-radius: 15px;"
        "   border: 1px solid rgba(0, 0, 0, 15);"
        "}"
        );

    QHBoxLayout *rowLayout = new QHBoxLayout(rowFrame);
    rowLayout->setContentsMargins(15, 10, 15, 10);
    rowLayout->setSpacing(15);

    // نمای آیکون/جلد کتاب (ساده و شیشه‌ای)
    QLabel *lblCover = new QLabel(rowFrame);
    lblCover->setFixedSize(60, 80);
    lblCover->setStyleSheet(
        "background-color: rgba(255, 255, 255, 180);"
        "border-radius: 8px;"
        "border: 1px solid rgba(0, 0, 0, 10);"
        );
    lblCover->setAlignment(Qt::AlignCenter);
    lblCover->setText("📖");
    lblCover->setFont(QFont("Segoe UI", 20));
    rowLayout->addWidget(lblCover);

    // عنوان و قیمت کتاب
    QVBoxLayout *infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(5);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *lblTitle = new QLabel(book.getTitle(), rowFrame);
    lblTitle->setFont(QFont("Segoe UI", 12, QFont::Bold));
    lblTitle->setStyleSheet("color: #706357; background: transparent; border: none;");
    infoLayout->addWidget(lblTitle);

    QHBoxLayout *priceLayout = new QHBoxLayout();
    priceLayout->setSpacing(10);

    // نمایش قیمت خط‌خورده در صورت وجود تخفیف
    if (book.getPrice() > book.getFinalPrice()) {
        QLabel *lblOrigPrice = new QLabel(QString("$%1").arg(book.getPrice(), 0, 'f', 2), rowFrame);
        lblOrigPrice->setFont(QFont("Segoe UI", 10));
        lblOrigPrice->setStyleSheet("color: rgba(112, 99, 87, 120); text-decoration: line-through; background: transparent; border: none;");
        priceLayout->addWidget(lblOrigPrice);
    }

    QLabel *lblFinalPrice = new QLabel(QString("$%1").arg(book.getFinalPrice(), 0, 'f', 2), rowFrame);
    lblFinalPrice->setFont(QFont("Segoe UI", 11, QFont::Bold));
    lblFinalPrice->setStyleSheet("color: #706357; background: transparent; border: none;");
    priceLayout->addWidget(lblFinalPrice);
    priceLayout->addStretch(1);

    infoLayout->addLayout(priceLayout);
    rowLayout->addLayout(infoLayout, 1);

    // دکمه حذف سطل آشغال (صورتی چرک شما)
    QPushButton *btnRemove = new QPushButton("🗑️", rowFrame);
    btnRemove->setCursor(Qt::PointingHandCursor);
    btnRemove->setFixedSize(36, 36);
    btnRemove->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   font-size: 18px;"
        "   color: #803040;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(244, 219, 222, 180);"
        "   border-radius: 18px;"
        "}"
        );

    // حذف کتاب از بک‌اند و رفرش پویا ویجت با استفاده از Lambda
    connect(btnRemove, &QPushButton::clicked, this, [this, bookId = book.getId()]() {
        m_cart->RemoveItem(bookId);
        updateUI();
    });

    rowLayout->addWidget(btnRemove);

    return rowFrame;
}

// مدیریت پویای وضعیت سبد خرید (خالی یا پر بودن) و محاسبات فاکتور نهایی
void CartWidget::updateUI() {
    // حذف آیتم‌های قبلی از حافظه پیش از بازسازی مجدد برای ممانعت از نشت حافظه
    QLayoutItem *child;
    while ((child = itemsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    const QVector<Book>& items = m_cart->getItems();

    // هندل کردن وضعیت سبد خرید خالی
    if (items.isEmpty()) {
        QLabel *lblEmpty = new QLabel("Your cart is empty! 🛒", this);
        lblEmpty->setFont(QFont("Segoe UI", 16, QFont::Bold));
        lblEmpty->setStyleSheet("color: #803040; background: transparent;");
        lblEmpty->setAlignment(Qt::AlignCenter);
        itemsLayout->addWidget(lblEmpty);

        lblTotalItemsVal->setText("0");
        lblTotalPriceVal->setText("$0.00");
        lblDiscountVal->setText("$0.00 (0%)");
        lblFinalPriceVal->setText("$0.00");
        btnCheckout->setEnabled(false);
        return;
    }

    btnCheckout->setEnabled(true);

    for (const Book &book : items) {
        QWidget *row = createCartItemRow(book);
        itemsLayout->addWidget(row);
    }


    // به‌روزرسانی نهایی فاکتور راست با توابع ریاضی کلاس منطق شما
    lblTotalItemsVal->setText(QString::number(m_cart->getNumberofitems()));
    lblTotalPriceVal->setText(QString("$%1").arg(m_cart->getTotalPrice(), 0, 'f', 2));
    lblDiscountVal->setText(QString("$%1 (%2%)")
                                .arg(m_cart->getTotalDiscount(), 0, 'f', 2)
                                .arg(m_cart->getTotaldiscountPercentage(), 0, 'f', 1));
    lblFinalPriceVal->setText(QString("$%1").arg(m_cart->getFinalPrice(), 0, 'f', 2));
}

void CartWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}