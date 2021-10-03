#include "logo.h"

Logo::Logo(QWidget * parent) : QWidget(parent) {
    logo = new QLabel(this);

    QPixmap pixmap = QPixmap("logo.png");
    logo->setPixmap(pixmap);


}
