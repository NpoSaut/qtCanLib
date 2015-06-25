#include "DummyCan.h"

DummyCan::DummyCan(QObject *parent) :
    ICan(parent)
{
}

void DummyCan::send(CanFrame)
{

}
