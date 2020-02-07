#include "thread.h"
#include <tesseract/baseapi.h>
#include <tesseract/ocrclass.h>
#include <leptonica/allheaders.h>
#include <QPixmap>
#include <QMetaObject>

static QObject *receiver = nullptr;
static int height = 0;

bool progress(int /*progress*/, int left, int right, int top, int bottom)
{
    QMetaObject::invokeMethod(receiver, "addRect", Qt::AutoConnection, Q_ARG(QRect, QRect(left, height-top, right-left, -(bottom-top))));
    return false;
}

bool cancel(void* cancel_this, int /*words*/)
{
    volatile bool *cancelFlag = static_cast<volatile bool*>(cancel_this);
    return *cancelFlag;
}

void runThread(const QString &imageFile, QObject *receiver, volatile bool *cancelFlag, volatile bool *isRunning)
{
    ::receiver = receiver;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(nullptr, "eng"))
    {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead(imageFile.toStdString().c_str());
    ::height = static_cast<int>(image->h);
    api->SetImage(image);

    ETEXT_DESC monitor;
    monitor.progress_callback = progress;
    monitor.cancel = cancel;
    monitor.cancel_this = (void*) cancelFlag;
    api->Recognize(&monitor);

    // Destroy used object and release memory
    api->End();
    pixDestroy(&image);
    *isRunning = false;
}
