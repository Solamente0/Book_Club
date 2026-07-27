#ifndef PDFREADERWIDGET_H
#define PDFREADERWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QPdfDocument>
#include <QPdfView>
#include "Book.h"

class PdfReaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PdfReaderWidget(QWidget *parent = nullptr);
    void openBook(const Book &book);

signals:
    void backRequested();

private slots:
    void onPrevPageClicked();
    void onNextPageClicked();
    void onPageSpinChanged(int page);
    void onZoomInClicked();
    void onZoomOutClicked();
    void onBackClicked();

private:
    void saveLastReadPage();
    void updatePageLabel();

    int currentBookId = 0;

    QPdfDocument *pdfDocument;
    QPdfView *pdfView;

    QLabel *titleLabel;
    QLabel *pageLabel;
    QSpinBox *pageSpin;
    QPushButton *btnBack;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;

    bool suppressPageSpinSignal = false;
};
#endif // PDFREADERWIDGET_H
