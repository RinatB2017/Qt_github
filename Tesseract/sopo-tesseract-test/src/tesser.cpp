#include "tesser.h"
#include <QDebug>
#include <QImage>

#include <leptonica/allheaders.h>

tesser::tesser(QObject *parent) :
    QObject(parent),
    m_running(false),
    m_min_conf(50)
{        
    m_tess=new tesseract::TessBaseAPI();
    m_tess->Init(nullptr, "eng");
    m_tess->SetPageSegMode(tesseract::PSM_AUTO_OSD);
    connect(&m_ocrWatcher, SIGNAL(finished()), this, SLOT(ocrFinished()));
}

void tesser::ocrThread(QString filename)
{
    char *text;
    QImage image(filename);

    if (image.isNull())
        return;

    qDebug() << image;

    QImage g=image.convertToFormat(QImage::Format_Grayscale8);
    qDebug() << g;
    if (g.isNull())
        return;

    m_tess->SetImage(g.bits(),
                     g.width(),
                     g.height(),
                     1,
                     g.bytesPerLine());

    m_tess->SetSourceResolution(300);
    m_tess->DetectOS(nullptr);

    m_text.clear();

#if 1
    Boxa* boxes = m_tess->GetComponentImages(tesseract::RIL_BLOCK, true, nullptr, nullptr);
    qDebug() << "Textline image components found: " << boxes->n;

    for (int i = 0; i < boxes->n; i++) {
        BOX* box = boxaGetBox(boxes, i, L_CLONE);
        m_tess->SetRectangle(box->x, box->y, box->w, box->h);
        text = m_tess->GetUTF8Text();
        int conf = m_tess->MeanTextConf();
        fprintf(stderr, "Box[%d]: x=%d, y=%d, w=%d, h=%d, confidence: %d, text: %s",
                       i, box->x, box->y, box->w, box->h, conf, text);
        if (conf>m_min_conf)
            m_text.append(text);
        else
            qDebug() << "Confidence under " << m_min_conf << " skipping";
    }
#else
    m_tess->Recognize(0);
    text=m_tess->GetUTF8Text();
    qDebug() << m_tess->MeanTextConf();

    m_text.append(text);
#endif

    qDebug() << m_text;

    m_tess->Clear();    
}

QString tesser::getText() const
{
    return m_text;
}

tesser::~tesser()
{
    m_tess->End();
}

void tesser::ocrFinished()
{
    m_running=false;
    emit runningChanged(m_running);
    emit textAvailable();
}

bool tesser::ocr(QString filename)
{
    if (m_running==true)
        return false;

    m_ocrFuture=QtConcurrent::run(this, &tesser::ocrThread, filename);

    m_running=true;
    emit runningChanged(m_running);

    m_ocrWatcher.setFuture(m_ocrFuture);
    return true;
}

