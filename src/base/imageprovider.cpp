#include "imageprovider.h"

ImageProvider::ImageProvider() {
    QPixmap pixmap(100, 100);
    pixmap.fill(Qt::white);
    m_pixmap = pixmap;
}

void ImageProvider::setPixmap(const QPixmap &pixmap) {
    if (!pixmap.isNull()) m_pixmap = pixmap;
}

QPixmap ImageProvider::requestPixmap(const QString &id,
                                     const QSize &requestedSize) {
    Q_UNUSED(id);
    m_pixmap = m_pixmap.scaled(requestedSize);

    return m_pixmap;
}
