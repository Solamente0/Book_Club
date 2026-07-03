#ifndef CART_H
#define CART_H

#include <QVector>
#include "Book.h"

class Cart {
private:
    QVector<Book> Items;
    double TotalPrice;

public:
    Cart();
    ~Cart()=default;


    void AddItem(const Book& newbook);
    void RemoveItem(int bookId);
    const QVector<Book>& getItems() ;
    double getEachBookPrice();
    void CalculateTotalBeforeDiscount();
    double getPriceBeforeDiscount();
    int getNumberofitems();
    void ApplyDiscount(double percentage);
    double getcalculatediscountamount();
    double getFinalPricetobepayed();

    void CheckOut();



};

#endif // CART_H