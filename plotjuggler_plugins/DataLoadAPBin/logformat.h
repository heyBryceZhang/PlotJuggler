#pragma once
#include <cstdint>
#define PACKED
// once the logging code is all converted we will remove these from
// this header
static constexpr uint8_t HEAD_BYTE1 = 0xA3;    // Decimal 163
static constexpr uint8_t HEAD_BYTE2 = 0x95;    // Decimal 149
/*
  unfortunately these need to be macros because of a limitation of
  named member structure initialisation in g++
 */
#define LOG_PACKET_HEADER	       uint8_t head1, head2, msgid;
#define LOG_PACKET_HEADER_INIT(id) head1 : HEAD_BYTE1, head2 : HEAD_BYTE2, msgid : id


enum LOG_TYPE_ID_t
{
  LOG_FORMAT_MSG = 128,  // this must remain #128
  LOG_PARAMETER_MSG = 129,
  LOG_FORMAT_UNITS_MSG = 206,
  LOG_UNIT_MSG = 207,
  LOG_MULT_MSG = 208,
  LOG_MESSAGE_MSG = 134,
  LOG_EVENT_MSG = 235,
};

static constexpr uint8_t MAX_LOGFORMAT_FORMAT = 16;
static constexpr uint8_t MAX_LABELS_SIZE = 64;
/*
  log structures common to all vehicle types
 */
struct PACKED log_Format {
  LOG_PACKET_HEADER
  uint8_t type;
  uint8_t length;
  char name[4];
  char format[MAX_LOGFORMAT_FORMAT];
  char labels[MAX_LABELS_SIZE];
};