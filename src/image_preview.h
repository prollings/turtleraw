// Copyright (c) 2021 Jan Kowalewicz. Licensed under MIT license (see LICENSE for more details).
#pragma once

#include <QWidget>
#include <QObject>

#include <QLabel>
#include <QScrollArea>
#include <QPixmap>

namespace turtleraw {

class ImagePreviewWidget : public QWidget {
    Q_OBJECT
public:
    ImagePreviewWidget(QWidget *parent = nullptr);

    // Loads an image from a given file path. Nothing more, nothing less.
    QPixmap& loadImage(QString filePath, bool useThumbnails);
    
    // Clear the label holding the image.
    void clear() {
        m_imageLbl->clear();
        m_imageLbl->setText(tr("No image"));
    }

    QScrollArea *m_scrollArea;
protected:
    void resizeImagePreview();

    QLabel *m_imageLbl;
    QPixmap m_previewPxmp;
};

} // namespace