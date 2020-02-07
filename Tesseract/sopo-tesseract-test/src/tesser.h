#ifndef TESSER_H
#define TESSER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include "tesseract/baseapi.h"
#include "tesseract/ocrclass.h"

class tesser : public QObject
{
    Q_OBJECT
public:
    explicit tesser(QObject *parent = 0);

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

    Q_INVOKABLE bool ocr(QString filename);
    Q_INVOKABLE QString getText() const;
    ~tesser();

    bool running() const
    {
        return m_running;
    }

signals:
    void textAvailable();
    void runningChanged(bool running);

public slots:

private slots:
    //void ocrFailed();
    void ocrFinished();

private:
    void ocrThread(QString filename);

    tesseract::TessBaseAPI* m_tess;
    QString m_text;

    QFuture<void> m_ocrFuture;
    QFutureWatcher<void> m_ocrWatcher;
    bool m_running;
    int m_min_conf;
};

#endif // TESSER_H
