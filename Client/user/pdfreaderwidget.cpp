#include "pdfreaderwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QPointF>
#include <QStandardPaths>
#include <QPdfPageNavigator>
#include "networkclient.h"

PdfReaderWidget::PdfReaderWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("pdfReaderPage");
    this->setStyleSheet("QWidget#pdfReaderPage { background-color: #2C3E50; }");

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    QWidget *headerWidget = new QWidget(this);
    headerWidget->setMinimumHeight(60);
    headerWidget->setMaximumHeight(60);
    headerWidget->setStyleSheet("background-color: rgba(210, 235, 255, 220);");
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(20, 0, 20, 0);
    headerLayout->setSpacing(8);

    btnBack = new QPushButton("⬅ Back", headerWidget);
    btnBack->setCursor(Qt::PointingHandCursor);
    btnBack->setStyleSheet(
        "QPushButton { background-color: #f4dbde; color: #2C3E50; border: none; border-radius: 12px; padding: 6px 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #FFB6C1; }"
        );
    headerLayout->addWidget(btnBack);

    titleLabel = new QLabel(headerWidget);
    titleLabel->setFont(QFont("Segoe UI", 12, QFont::Bold));
    titleLabel->setStyleSheet("color: #2C3E50; background: transparent;");
    headerLayout->addWidget(titleLabel, 1);

    btnZoomOut = new QPushButton("－", headerWidget);
    btnZoomOut->setCursor(Qt::PointingHandCursor);
    btnZoomOut->setFixedWidth(36);
    btnZoomOut->setStyleSheet(
        "QPushButton { background-color: #2C3E50; color: white; border: none; border-radius: 6px; }"
        "QPushButton:hover { background-color: #FFC0CB; color: #2C3E50; }"
        );
    headerLayout->addWidget(btnZoomOut);

    btnZoomIn = new QPushButton("＋", headerWidget);
    btnZoomIn->setCursor(Qt::PointingHandCursor);
    btnZoomIn->setFixedWidth(36);
    btnZoomIn->setStyleSheet(btnZoomOut->styleSheet());
    headerLayout->addWidget(btnZoomIn);

    btnPrev = new QPushButton("‹ Prev", headerWidget);
    btnPrev->setCursor(Qt::PointingHandCursor);
    btnPrev->setStyleSheet(
        "QPushButton { background-color: #2C3E50; color: white; border: none; border-radius: 6px; padding: 6px 12px; }"
        "QPushButton:hover { background-color: #FFC0CB; color: #2C3E50; }"
        );
    headerLayout->addWidget(btnPrev);

    pageSpin = new QSpinBox(headerWidget);
    pageSpin->setMinimum(1);
    pageSpin->setStyleSheet("background-color: white; border-radius: 6px; padding: 4px; color: #2C3E50;");
    headerLayout->addWidget(pageSpin);

    pageLabel = new QLabel(headerWidget);
    pageLabel->setStyleSheet("color: #2C3E50; background: transparent;");
    headerLayout->addWidget(pageLabel);

    btnNext = new QPushButton("Next ›", headerWidget);
    btnNext->setCursor(Qt::PointingHandCursor);
    btnNext->setStyleSheet(btnPrev->styleSheet());
    headerLayout->addWidget(btnNext);

    outerLayout->addWidget(headerWidget);

    pdfDocument = new QPdfDocument(this);

    pdfView = new QPdfView(this);
    pdfView->setDocument(pdfDocument);
    pdfView->setPageMode(QPdfView::PageMode::SinglePage);
    pdfView->setZoomMode(QPdfView::ZoomMode::FitToWidth);
    outerLayout->addWidget(pdfView, 1);

    connect(btnBack, &QPushButton::clicked, this, &PdfReaderWidget::onBackClicked);
    connect(btnPrev, &QPushButton::clicked, this, &PdfReaderWidget::onPrevPageClicked);
    connect(btnNext, &QPushButton::clicked, this, &PdfReaderWidget::onNextPageClicked);
    connect(pageSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &PdfReaderWidget::onPageSpinChanged);
    connect(btnZoomIn, &QPushButton::clicked, this, &PdfReaderWidget::onZoomInClicked);
    connect(btnZoomOut, &QPushButton::clicked, this, &PdfReaderWidget::onZoomOutClicked);

    connect(pdfView->pageNavigator(), &QPdfPageNavigator::currentPageChanged, this, [this](int page) {
        suppressPageSpinSignal = true;
        pageSpin->setValue(page + 1);
        suppressPageSpinSignal = false;
        updatePageLabel();
    });
}

void PdfReaderWidget::openBook(const Book &book)
{
    currentBookId = book.getId();
    titleLabel->setText(book.getTitle());

    QJsonObject data;
    data["book_id"] = currentBookId;

    QJsonObject response = NetworkClient::instance().sendRequest(RequestType::GetBookFile, data);
    if (response.value("status").toString() != "Success") {
        QMessageBox::warning(this, "Cannot Open Book",
            response.value("message").toString("You must purchase this book first."));
        emit backRequested();
        return;
    }

    QByteArray pdfBytes = QByteArray::fromBase64(
        response.value("data").toObject().value("pdf_data").toString().toLatin1());

    QString dir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/bookclub";
    QDir().mkpath(dir);

    QString filePath = QString("%1/book_%2.pdf").arg(dir).arg(currentBookId);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly) || file.write(pdfBytes) < 0) {
        QMessageBox::warning(this, "Error", "Could not save the book file for reading.");
        emit backRequested();
        return;
    }
    file.close();

    if (pdfDocument->load(filePath) != QPdfDocument::Error::None) {
        QMessageBox::warning(this, "Error", "Could not open this PDF file.");
        emit backRequested();
        return;
    }

    int pageCount = pdfDocument->pageCount();
    pageSpin->setMaximum(pageCount > 0 ? pageCount : 1);
    updatePageLabel();

    QJsonObject lastPageResponse = NetworkClient::instance().sendRequest(
        RequestType::GetLastReadPage, QJsonObject{{"book_id", currentBookId}});

    int startPage = 0;
    if (lastPageResponse.value("status").toString() == "Success")
        startPage = lastPageResponse.value("data").toObject().value("page").toInt();

    if (startPage < 0 || startPage >= pageCount)
        startPage = 0;

    pdfView->pageNavigator()->jump(startPage, QPointF());
    suppressPageSpinSignal = true;
    pageSpin->setValue(startPage + 1);
    suppressPageSpinSignal = false;
    updatePageLabel();
}

void PdfReaderWidget::updatePageLabel()
{
    pageLabel->setText(QString("/ %1").arg(pdfDocument->pageCount()));
}

void PdfReaderWidget::onPrevPageClicked()
{
    int page = pdfView->pageNavigator()->currentPage();
    if (page > 0)
        pdfView->pageNavigator()->jump(page - 1, QPointF());
}

void PdfReaderWidget::onNextPageClicked()
{
    int page = pdfView->pageNavigator()->currentPage();
    if (page < pdfDocument->pageCount() - 1)
        pdfView->pageNavigator()->jump(page + 1, QPointF());
}

void PdfReaderWidget::onPageSpinChanged(int page)
{
    if (suppressPageSpinSignal)
        return;

    int index = page - 1;
    if (index >= 0 && index < pdfDocument->pageCount())
        pdfView->pageNavigator()->jump(index, QPointF());
}

void PdfReaderWidget::onZoomInClicked()
{
    pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
    pdfView->setZoomFactor(pdfView->zoomFactor() * 1.15);
}

void PdfReaderWidget::onZoomOutClicked()
{
    pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
    pdfView->setZoomFactor(pdfView->zoomFactor() / 1.15);
}

void PdfReaderWidget::saveLastReadPage()
{
    if (currentBookId == 0)
        return;

    QJsonObject data;
    data["book_id"] = currentBookId;
    data["page"] = pdfView->pageNavigator()->currentPage();
    NetworkClient::instance().sendRequest(RequestType::UpdateLastReadPage, data);
}

void PdfReaderWidget::onBackClicked()
{
    saveLastReadPage();
    emit backRequested();
}
