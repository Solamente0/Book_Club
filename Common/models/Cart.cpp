#include "Book.h"
#include "Cart.h"

Cart::Cart() {};

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
    return true;
}

bool Cart::RemoveItem(int bookId) {
    for (int i = 0; i < Items.size(); ++i) {
        if (Items[i].getId() == bookId) {
            Items.removeAt(i);
            return true;
        }
    }
    return false; // کتاب توی سبد پیدا نشد
}

const QVector<Book>& Cart::getItems() const {
    return Items;
}

double Cart::showEachBookPrice() {
    if (Items.isEmpty()) {
        return 0.0;
    }
    for (const Book& book : Items) {
        return book.getFinalPrice();
    }
};

int Cart::getNumberofitems() {
    return Items.size();
}

double Cart::getTotalPrice() {
    double sum = 0.0;
    for (const Book& eachbook : Items) {
        sum = sum + eachbook.getPrice();
    }
    return sum;
};   // جمع قیمت اصلی بدون تخفیف

double Cart::getTotalDiscount() {
    double sum = 0.0;
    for (const Book& eachbook : Items) {
        sum = sum + (eachbook.getPrice() - eachbook.getFinalPrice());
    }
    return sum;
};   // جمع مقدار تخفیف

double Cart::getFinalPrice() {
    return getTotalPrice() - getTotalDiscount();
};   // قیمت نهایی قابل پرداخت

double Cart::getTotaldiscountPercentage() {
    if (getTotalPrice() == 0.0) {
        return 0.0;
    }
    return (getTotalDiscount() / getTotalPrice()) * 100.0;
}

bool Cart::CheckOut() {
    if (Items.isEmpty()) {
        return false; // سبد خالیه
    }
    Items.clear();
    return true;
}
