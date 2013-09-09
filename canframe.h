#ifndef CANFRAME_H
#define CANFRAME_H

#include <vector>

class CanFrame
{
public:
    CanFrame(int id, int size, const std::vector<unsigned char>& data);
    CanFrame(int descriptor, const std::vector<unsigned char>& data);
    CanFrame(int descriptor);
    CanFrame();

    int getId() const;
    void setId(const int &id);

    int getDescriptor() const;
    void setDescriptor(int descriptor);

    const std::vector<unsigned char> &getData() const;
    void setData(const std::vector<unsigned char> &data);

    // !WARNING! --< CAN message byte numbers start from 1 >-- !WARNING!
    unsigned char &operator[] (int index);
    const unsigned char &operator[] (int index) const;

private:
    std::vector<unsigned char> data;
    int id;

    inline int getSizeFromDescriptor(int descriptor);
    inline int checkSize(int size);
};

#endif // CANFRAME_H
