# Qt-Svg-Stupid-Render

Very fast, but dummy SVG render to image for QT

Using vector graphics in your project solves the problem of resolution-independent resources for your buttons and other controls.

Qt has svg module, but for small images it's would be very expencive to use it.

This app using [NanoSVG](https://github.com/memononen/nanosvg) lib
Of couse, thanks [user1095108](https://github.com/user1095108/). I use you code, you know it))

### Not working:

- `xmlns:xlink` is not supported. You need to parsing your svg (using QDomDocument for example) if you image has these nodes:
  `<use xlink:href="#q" x="350.2" y="131"/>`

- Raster images in svg. Sorry, but you can pun QImage on QImage

### How to use

- #include "nanosvg.h"
- #include "qtnanosvg.h"
- Usage:

        QString svgPath=your svg Path;
        QString pngPath=path for png
        QSize imageSize(your image Path size);
        const QSize resultSize(size that you want to get);
        QImage image(sizeW, sizeH, Format);//End of paramm
        QFile svgFile(svgPath);
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
                image.save(pngPath);// if you want to save image
            }
        }
