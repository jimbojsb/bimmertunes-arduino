#include <Arduino.h>

#ifndef IBUS_PACKET_H
#define IBUS_PACKET_H

#define PKT_SRC_IDX 0
#define PKT_LEN_IDX 1
#define PKT_DEST_IDX 2
#define PKT_CONTENT_IDX 3
#define PKT_OVERHEAD_SIZE 4
#define PKT_MAX_SIZE 36

class IbusPacket {
  private:
    void setChecksum();
    static byte calculateChecksum(byte* msg, int len);
    
  public:
    byte source;
    byte destination;
    byte length;
    byte checksum;
    byte *content;
    int contentLen;
    IbusPacket(byte msg[], int len);
    IbusPacket(byte source, byte length, byte destination, byte* content, int contentLen);
    IbusPacket(byte source, byte length, byte destination, byte* content, int contentLen, byte checksum);
    byte* asBytes();
    int byteLen();
    static bool isPacket(byte msg[], int len);    

};

#endif