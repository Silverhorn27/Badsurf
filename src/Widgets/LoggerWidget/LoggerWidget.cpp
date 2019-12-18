#include <QPropertyAnimation>
#include <QDebug>

#include "LoggerWidget.h"
#include "ui_LoggerWidget.h"

LoggerWidget::LoggerWidget(const QString & title, const int animationDuration,
                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoggerWidget)
    , _logEdit(new QTextEdit)
    , _animationDuration(animationDuration)
{
    ui->setupUi(this);
    ui->toggleButton->setStyleSheet("QToolButton { border: none; }");
    ui->toggleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toggleButton->setArrowType(Qt::ArrowType::RightArrow);
    ui->toggleButton->setText(title);
    ui->toggleButton->setCheckable(true);
    ui->toggleButton->setChecked(false);

    ui->headerLine->setFrameShape(QFrame::HLine);
    ui->headerLine->setFrameShadow(QFrame::Sunken);
    ui->headerLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

//    ui->contentArea->setStyleSheet("QScrollArea { background-color: white; border: none; }");
    ui->contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // start out collapsed
    ui->contentArea->setMaximumHeight(0);
    ui->contentArea->setMinimumHeight(0);
    // let the entire widget grow and shrink with its content
    _toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
    _toggleAnimation.addAnimation(new QPropertyAnimation(this, "maximumHeight"));
    _toggleAnimation.addAnimation(new QPropertyAnimation(ui->contentArea, "maximumHeight"));
    // don't waste space

    ui->gridLayout->setVerticalSpacing(0);
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);

    QObject::connect(ui->toggleButton, &QToolButton::clicked, [this](const bool checked) {
        ui->toggleButton->setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        _toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        _toggleAnimation.start();
    });

    ui->contentArea->setWidget(_logEdit);
    ui->contentArea->setMinimumSize(0,0);
    _logEdit->setFrameStyle(QFrame::NoFrame);
    _logEdit->setReadOnly(true);

    const auto collapsedHeight = sizeHint().height() - ui->contentArea->maximumHeight();
    auto contentHeight = _logEdit->sizeHint().height() - 68;
//    qDebug() << _logEdit->sizeHint().height() << "   " << sizeHint().height() << "  " << ui->contentArea->maximumHeight();
    for (int i = 0; i < _toggleAnimation.animationCount() - 1; ++i) {
        QPropertyAnimation * spoilerAnimation = static_cast<QPropertyAnimation *>(_toggleAnimation.animationAt(i));
        spoilerAnimation->setDuration(_animationDuration);
        spoilerAnimation->setStartValue(collapsedHeight);
        spoilerAnimation->setEndValue(collapsedHeight + contentHeight);
    }
    QPropertyAnimation * contentAnimation = static_cast<QPropertyAnimation *>(_toggleAnimation.animationAt(_toggleAnimation.animationCount() - 1));
    contentAnimation->setDuration(_animationDuration);
    contentAnimation->setStartValue(0);
    contentAnimation->setEndValue(contentHeight);
}

LoggerWidget::~LoggerWidget()
{
    delete ui;
}

void LoggerWidget::log(const QString &msg)
{
    _logEdit->append(msg);
}
