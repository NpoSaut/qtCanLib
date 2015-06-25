#include "ICan.h"

#include <QMetaType>

ICan::ICan(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<CanFrame>("CanFrame");
}
