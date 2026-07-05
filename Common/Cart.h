#ifndef CART_H
#define CART_H
#include <QVector>
#include "Book.h"

class Cart {
private:
    QVector<Book> Items;

    bool isBookInCart(int bookId);

public:
    Cart();
    ~Cart() = default;

    bool AddItem(const Book& newbook);
    bool RemoveItem(int bookId);

    const QVector<Book>& getItems() const;
    double showEachBookPrice();
    int getNumberofitems();

    double getTotalPrice();            
    double getTotalDiscount();          
    double getFinalPrice();            
    double getTotaldiscountPercentage();

    bool CheckOut();
};
#endif // CART_H