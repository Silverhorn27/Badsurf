#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QParallelAnimationGroup>

namespace Ui {
class LoggerWidget;
}

class LoggerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoggerWidget(const QString &title = "", const int animationDuration = 300,
                          QWidget *parent = nullptr);
    ~LoggerWidget();

public slots:
    void log(const QString &msg);

private:
    Ui::LoggerWidget *ui;
    QTextEdit *_logEdit;
    QParallelAnimationGroup _toggleAnimation;
    int _animationDuration;
};

#endif // LOGGERWIDGET_H
