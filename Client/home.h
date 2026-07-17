#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void cartRequested();

private:
    QWidget *createBookWidget(const QString &imagePath,
                              const QString &title,
                              QWidget *parent);

    // نوار هدر بالا
    QWidget *headerWidget;
    QLabel *lblLogo;
    QLineEdit *leSearch;
    QPushButton *btnNotification;
    QPushButton *btnCart;
    QPushButton *btnProfile;

    // منطقه اسکرول‌شونده
    QScrollArea *scrollArea;
    QWidget *scrollWidget;

    // بخش‌های اصلی صفحه
    QFrame *genresFrame;
    QFrame *featuredFrame;
    QFrame *recommendedFrame;
    QFrame *newReleasesFrame;


    QFrame *bestSellersFrame;  // این متغیر را اضافه کن
    QFrame *freeBooksFrame;     // این متغیر را اضافه کن
};

#endif // HOME_H