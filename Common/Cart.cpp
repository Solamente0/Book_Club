
#include "Book.h"
#include "Cart.h"

Cart::Cart() {
    TotalPrice = 0.0;
    TotalBeforeDiscount = 0.0;
}
bool Cart::isBookInCart(int bookId) {
    for (int i = 0; i < Items.size(); ++i) {
        if (Items[i].getId() == bookId) {
            return true;
        }
    }
    return false;
}
bool Cart::AddItem(const Book& newbook) {
    if (isBookInCart(newbook.getId())) {
        return false; // کتاب از قبل توی سبد هست
    }
    Items.append(newbook);
    CalculateTotalBeforeDiscount();
    return true;
}

bool Cart::RemoveItem(int bookId) {
    for (int i = 0; i < Items.size(); ++i) {
        if (Items[i].getId() == bookId) {
            Items.removeAt(i);
            CalculateTotalBeforeDiscount();
            return true;
        }
    }
    return false; // کتاب توی سبد پیدا نشد
}
const QVector<Book>& Cart::getItems() const {
    return Items;
}

void Cart::showEachBookPrice() {
    if (Items.isEmpty()) {
        qDebug() << "cart is empty";
        return;
    }
    for (const Book& book : Items) {
        qDebug() << "book" << book.getTitle() << "| price: " << book.getFinalPrice();
    }
};

void Cart::CalculateTotalBeforeDiscount() {
    double sum = 0.0;
    for (const Book& eachbook : Items) {
        sum = sum + eachbook.getFinalPrice(); 
    }
    TotalBeforeDiscount = sum; 
    TotalPrice = sum; 
}

double Cart::getPriceBeforeDiscount() {
    return TotalBeforeDiscount;
}

void Cart::ApplyDiscount(double percentage) {
    if (percentage > 0.0 && percentage <= 100.0) {
        double discountAmount = getPriceBeforeDiscount() * (percentage / 100.0);
        TotalPrice = TotalBeforeDiscount - discountAmount;
    }
}

int Cart::getNumberofitems() {
    return Items.size(); 
}

double Cart::getcalculatediscountamount() {
    return getPriceBeforeDiscount() - TotalPrice;
}

double Cart::getFinalPricetobepayed() {
    return TotalPrice;
}

bool Cart::CheckOut() {
    if (Items.isEmpty()) {
        return false; // سبد خالیه
    }
    Items.clear();
    TotalBeforeDiscount = 0.0;
    DiscountPercentage = 0.0;
    return true;
}