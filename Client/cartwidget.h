#ifndef CARTWIDGET_H
#define CARTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include "Cart.h"

class CartWidget : public QWidget {
    Q_OBJECT
private:
    Cart *m_cart; // پوینتر به کلاس منطق سبد خرید شما

    // اجزای رابط کاربری
    QWidget *scrollWidget;
    QVBoxLayout *itemsLayout;
    QScrollArea *scrollArea;

    QLabel *lblTotalItemsVal;
    QLabel *lblTotalPriceVal;
    QLabel *lblDiscountVal;
    QLabel *lblFinalPriceVal;
    QPushButton *btnCheckout;

    void setupUI();
    QWidget* createCartItemRow(const Book &book);

public:
    explicit CartWidget(Cart *cart, QWidget *parent = nullptr);
    ~CartWidget() = default;

    void updateUI(); // متد به‌روزرسانی پویا لیست کتاب‌ها و محاسبات فاکتور

signals:
    void checkoutSuccessful(); // سیگنال اتمام موفق خرید (برای انتقال کتاب‌ها به کتابخانه شخصی)
    void backToHomeRequested(); // سیگنال بازگشت به هوم‌پیج

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CARTWIDGET_H