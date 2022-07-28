#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QPixmap>

class ImageProvider {
   public:
    ImageProvider();
    void setPixmap(const QPixmap &pixmap);
    QPixmap requestPixmap(const QString &id, const QSize &requestedSize);

   private:
    QPixmap m_pixmap;
};

#endif  // IMAGEPROVIDER_H
