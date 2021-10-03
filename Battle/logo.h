#ifndef LOGO_H
#define LOGO_H

#include <QLabel>
#include <QWidget>

class Logo : public QWidget {
public:
    Logo(QWidget * parent = nullptr);

private:
    QLabel *logo;
};

#endif // LOGO_H
