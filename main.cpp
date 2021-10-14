#include <QCoreApplication>
#include <QElapsedTimer>
#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "nanosvg.h"
#include "qtnanosvg.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString imagePath="E:\\MAP 2.0\\MapText\\ForMyRender\\9\\0_0.svg";
    QSize imageSize(497, 279);
    const QSize resultSize(497, 279);
    QImage image(497, 279, QImage::Format_ARGB32);
    QFile svgFile(imagePath);
    //
    if (svgFile.open(QIODevice::ReadOnly))
    {
        int svgFileSize=svgFile.size();
        QByteArray ba;
        ba.resize(svgFileSize + 1);
        svgFile.read(ba.data(), svgFileSize);
        ba.back() = {};
        if (auto const nsi(nsvgParse(ba.data(), "px", 96)); nsi)
        {
            image.fill(Qt::transparent);

            QPainter p(&image);
            p.setRenderHint(QPainter::Antialiasing, true);

            drawSVGImage(&p, nsi, resultSize.width(), resultSize.height());

            nsvgDelete(nsi);
            image.save("22.png");
        }
    }
//        qDebug() << "+ method" << timer.elapsed() << "milliseconds";
    return a.exec();
}
