#include <Arduino.h>
#include "ibus_packet.h"

extern usb_serial_class Serial;

IbusPacket::IbusPacket(byte msg[], int len) {
    this->source = msg[PKT_SRC_IDX];
    this->length = msg[PKT_LEN_IDX];
    this->destination = msg[PKT_DEST_IDX];
    this->contentLen = len - PKT_OVERHEAD_SIZE;
    byte content[PKT_MAX_SIZE];
    for (int i = 0; i < this->contentLen; i++) {
        content[i] = msg[PKT_CONTENT_IDX + i];
    }
    this->content = content;
    this->checksum = msg[len - 1];
}

IbusPacket::IbusPacket(byte source, byte destination, byte* content, int contentLen) {
  this->source = source;
  this->destination = destination;
  this->content = content;
  this->contentLen = contentLen;
  int length = this->contentLen + PKT_OVERHEAD_SIZE - 2;
  this->length = byte(length);
  this->setChecksum();
}

IbusPacket::IbusPacket(byte source, byte length, byte destination, byte* content, int contentLen) {
  this->source = source;
  this->destination = destination;
  this->content = content;
  this->length = length;
  this->contentLen = contentLen;
  this->setChecksum();
}

IbusPacket::IbusPacket(byte source, byte length, byte destination, byte* content, int contentLen, byte checksum) {
  this->source = source;
  this->destination = destination;
  this->content = content;
  this->length = length;
  this->checksum = checksum;
}

void IbusPacket::setChecksum() {
    int msgLen = this->contentLen + PKT_OVERHEAD_SIZE - 1;
    static byte msg[PKT_MAX_SIZE];
    msg[PKT_SRC_IDX] = this->source;
    msg[PKT_LEN_IDX] = this->length;
    msg[PKT_DEST_IDX] = this->destination;
    for (int i = 0; i < this->contentLen; i++) {
        msg[PKT_CONTENT_IDX + i] = content[i];
    }
    this->checksum = IbusPacket::calculateChecksum(msg, msgLen);
}

byte IbusPacket::calculateChecksum(byte *msg, int len) {
  byte checksum = 0x00;
  for (int i = 0; i < len; i++) {
    checksum ^= msg[i];
  }
  return checksum;
}

byte* IbusPacket::asBytes() {
    int msgLen = this->contentLen + PKT_OVERHEAD_SIZE;
    static byte msg[PKT_MAX_SIZE];
    msg[PKT_SRC_IDX] = this->source;
    msg[PKT_LEN_IDX] = this->length;
    msg[PKT_DEST_IDX] = this->destination;
    for (int i = 0; i < this->contentLen; i++) {
        msg[PKT_CONTENT_IDX + i] = this->content[i];
    }
    msg[msgLen - 1] = this->checksum;
    return msg;
}

int IbusPacket::byteLen() {
    return PKT_OVERHEAD_SIZE + this->contentLen;
}

bool IbusPacket::equals(IbusPacket *pkt) {
    return (
        pkt->source == this->source &&
        pkt->destination == this->destination &&
        pkt->checksum == this->checksum
    );
}

bool IbusPacket::contentEquals(byte *content, int len) {
    if (len == this->contentLen) {
        for (int i = 0; i < len; i++) {
            if (content[i] != this->content[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool IbusPacket::isPacket(byte *msg, int len) {
    byte possibleChecksum = msg[len - 1];
    return (possibleChecksum == IbusPacket::calculateChecksum(msg, len - 1));
}
