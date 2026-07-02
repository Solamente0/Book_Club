#include <QDebug>
#include <Book.h>
#include <Cart.h>

Cart::Cart() {
    TotalPrice = 0.0;
}

void Cart::AddItem(const Book& newbook){
    Items.append(newbook);
    CalculateTotal();
};

void Cart::RemoveItem(int bookId){
    for (int i=0;i<Items.size();++i){
        if(Items[i].getId()==bookId){
            Items.removeAt(i);
        }
        break;
    }
    CalculateTotal();
};

void Checkout(){
    if (Items.isEmpty()) {
        qDebug() << "Shopping cart is empty. Cannot checkout.";
        return;
    }
    
    qDebug() << "Checking out" << Items.size() << "items. Total Pay:" << TotalPrice;
   
};
void Cart::ApplyDiscount(double percentage){
    if (percentage > 0.0 && percentage <= 100.0) {
        double discountAmount = TotalPrice * (percentage / 100.0);
        TotalPrice =TotalPrice-discountAmount;
    }
};
void Cart::CalculateTotal(){
    double sum = 0.0;
    for (const Book& eachbook : Items) {
        sum =sum+eachbook.getFinalPrice(); 
    }
    TotalPrice = sum;
};


QVector<Book> Cart::getItems() {
     return Items;
};
double Cart::getTotalPrice() {
    return TotalPrice;
};