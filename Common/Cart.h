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
    void CalculateTotal();


    const QVector<Book>& getItems() const;
    double getTotalPrice() const;
};

#endif // CART_H