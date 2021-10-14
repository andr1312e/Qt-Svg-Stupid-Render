# Qt-Svg-Stupid-Render

Very fast, but dummy SVG render to image for QT

Using vector graphics in your project solves the problem of resolution-independent resources for your buttons and other controls.

Qt has svg module, but for small images it's would be very expencive to use it.

This app using [NanoSVG](https://github.com/memononen/nanosvg) lib

Of couse, thanks [user1095108](https://github.com/user1095108/). I use you code, you know it)). Give him a star)

### Not working:

- `xmlns:xlink` is not supported. You need to parsing your svg (using `QDomDocument` for example). Try to convert these nodes:
  `<use xlink:href="#q" x="350.2" y="131"/>` to: `<path d="M 1.9 0.0 C 1.5 0.0 1.1 -0.0 0.8 -0.3 C 0.6 -0.6 0.4 -1.1 0.4 -1.7 C 0.4 -2.2 0.5 -2.7 0.6 -3.1 C 0.7 -3.6 0.9 -4.0 1.2 -4.3 C 1.4 -4.7 1.7 -4.9 2.0 -5.1 C 2.3 -5.3 2.6 -5.4 3.0 -5.4 C 3.4 -5.4 3.7 -5.3 3.9 -5.1 C 4.1 -5.0 4.3 -4.7 4.4 -4.5 L 4.5 -4.5 C 4.5 -4.6 4.6 -4.7 4.7 -4.9 C 4.7 -5.1 4.8 -5.2 4.9 -5.3 L 5.7 -5.3 C 5.6 -5.2 5.5 -5.0 5.4 -4.7 C 5.3 -4.5 5.2 -4.2 5.1 -3.9 Z" transform="translate(350.2 131)"/>`

- Raster images in svg not supported. Sorry, but you can pun raster QImage on QImage

- Scripts. And you should talk that it would be)))

### How to use

- copy `"nanosvg.h" "qtnanosvg.h" "qtnanosvg.cpp"` into your project
- `#include "nanosvg.h"`
- `#include "qtnanosvg.h"`
- Usage (`QImage` or `QPixmap`) how you want:

        QString svgPath="your svg Path";
        QString pngPath="path for png";
        QSize imageSize(your image Path size);
        const QSize resultSize(size that you want to get);
        QImage image(sizeW, sizeH, Format);//End of param
        
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
