#include "canframe.h"

using namespace std;

CanFrame::CanFrame(int id, int size, const vector<unsigned char> &data)
    : data (data), id (id)
{
    this->data.resize (checkSize (size));
}

CanFrame::CanFrame(int descriptor, const vector<unsigned char> &data)
    : data (data)
{
    setDescriptor (descriptor);
}

CanFrame::CanFrame(int descriptor)
    : data(std::vector<unsigned char>(getSizeFromDescriptor(descriptor), 0))
{
    setDescriptor(descriptor);
}

CanFrame::CanFrame()
    : data(), id(0)
{ }

int CanFrame::getId() const
{
    return id;
}

void CanFrame::setId(const int &id)
{
    this->id = id;
}

int CanFrame::getDescriptor() const
{
    return id * 0x20 + data.size ();
}

void CanFrame::setDescriptor(int descriptor)
{
    id = descriptor / 0x20;
    int size = getSizeFromDescriptor(descriptor);
    data.resize (size);
}

const vector<unsigned char> &CanFrame::getData() const
{
    return data;
}

void CanFrame::setData(const vector<unsigned char> &data)
{
    this->data = data;
}

unsigned char &CanFrame::operator [](int index)
{
    return data[index-1];
}

const unsigned char &CanFrame::operator [](int index) const
{
    return data[index-1];
}

int CanFrame::getSizeFromDescriptor(int descriptor)
{
    return checkSize(descriptor & 0x0F);
}

int CanFrame::checkSize(int size)
{
    if (size < 0) return 0;
    if (size > 8) return 8;
    return size;
}
