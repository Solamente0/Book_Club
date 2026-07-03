#include <QDebug>
#include <Book.h>
#include "Cart.h"

Cart::Cart() {
    TotalPrice = 0.0;
}

void Cart::AddItem(const Book& newbook){
    Items.append(newbook);
};

void Cart::RemoveItem(int bookId){
    for (int i=0;i<Items.size();++i){
        if(Items[i].getId()==bookId){
            Items.removeAt(i);
            break;
        };
    }
};
const QVector<Book>& Cart::getItems() const {
     return Items;
};
double Cart::getEachBookPrice(){
    for (const Book& book : Items){
        return book.getFinalPrice();
    }
};

void Cart::CalculateTotalBeforeDiscount(){
    double sum = 0.0;
    for (const Book& eachbook : Items) {
        sum =sum+eachbook.getFinalPrice(); 
    }
    double totalpricebeforediscount = sum;
};
double Cart::getPriceBeforeDiscount(){
    return totalpricebeforediscount;
}
void Cart::ApplyDiscount(double percentage) {
    if (percentage > 0.0 && percentage <= 100.0) {
        double discountAmount = getPriceBeforeDiscount() * (percentage / 100.0);
        TotalPrice -= discountAmount;
    };
};
int Cart::getNumberofitems(){
    Items.counter();
}
double Cart::getCalculatediscountamount(){
       return getPriceBeforeDiscount()-TotalPrice;
}
double Cart::getFinalPricetobepayed(){
    return TotalPrice;
}
void Cart::CheckOut() {
    if (Items.isEmpty()) {
        qDebug() << "Shopping cart is empty. Cannot checkout.";
        return;
    }

    qDebug() << "Checking out" << Items.size() << "items. Total Paid:" << TotalPrice;
}

