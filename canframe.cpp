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

#ifdef WITH_CAN
CanFrame::CanFrame(const struct can_frame &canFrame)
    : data (canFrame.data, canFrame.data + canFrame.can_dlc), id (canFrame.can_id&0x1FFF)
{ }

CanFrame::CanFrame(const struct can_frame *canFrame)
    :  data (canFrame->data, canFrame->data + canFrame->can_dlc), id (canFrame->can_id&0x1FFF)
{ }
#endif // WITH_CAN

CanFrame::CanFrame()
    : data(), id(0)
{ }

#ifdef WITH_CAN
CanFrame::operator can_frame() const
{
    can_frame frame;

    frame.can_id = getId ();
    frame.can_dlc = data.size ();
    int i = 0;
    for( ; i < data.size (); i ++ )
        frame.data[i] = data[i];
    for ( ; i < 8; i ++ )
        frame.data[i] = 0;

    return frame;
}
#endif // WITH_CAN

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
    int size = checkSize (descriptor & 0xF);
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

int CanFrame::checkSize(int size)
{
    if (size < 0) return 0;
    if (size > 8) return 8;
    return size;
}
