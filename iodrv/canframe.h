#ifndef CANFRAME_H
#define CANFRAME_H

#include <vector>

#if defined WITH_CAN
#include <linux/can.h>
#endif // WITH_CAN

class CanFrame
{
public:
    CanFrame(int id, int size, const std::vector<unsigned char>& data);
    CanFrame(int descriptor, const std::vector<unsigned char>& data);
#if defined WITH_CAN
    CanFrame(const can_frame& canFrame);
    CanFrame(const can_frame* canFrame);
#endif // WITH_CAN
    CanFrame();

    int getId() const;
    void setId(const int &id);

    int getDescriptor() const;
    void setDescriptor(int descriptor);

    const std::vector<unsigned char> &getData() const;
    void setData(const std::vector<unsigned char> &data);

private:
    std::vector<unsigned char> data;
    int id;

    inline int checkSize(int size);
};

#endif // CANFRAME_H
