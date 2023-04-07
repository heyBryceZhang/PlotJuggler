# Ardupilot .bin log parse protocol

.bin file is consists of message packages.

There are three types packages, fmt(format) definition, fmt messages and log datas.
fmt definition is always at the top of the file, follwed by the fmt messages,
log datas is at the end which is the main part of .bin files.

All messages are defined by the structure below:

``` C++
struct PACKED log {
    uint8_t HEAD_1; \\ 0xA3 = 163
    uint8_t HEAD_2; \\ 0x95 = 149
    uint8_t msg_id; \\ Fixed to 128 for fmt definition and messages.
    uint8_t data[n];
}
```


## 1.Fmt definition and messages

When parsing logs, find "fmt definition package" first, whose msg_id = 128 and type = 128, get the value of "length" which defines the length of all fmt messages.
Then parse all fmt messages, their msg_id = 128, type are different.

``` C++
#define LOG_PACKET_HEADER	       uint8_t head1 = 0xA3, head2 = 0x95, msgid=128;
struct PACKED log_Format {
    LOG_PACKET_HEADER;
    uint8_t type; // define different messages, e.g. fmt definition = 128, PIDR = 188, .
    uint8_t length;
    char name[4]; // log package name
    char format[MAX_LOGFORMAT_FORMAT]; // parameter type, definition below, default MAX_LOGFORMAT_FORMAT = 16
    char labels[MAX_LABELS_SIZE]; // paramter name, default MAX_LABELS_SIZE = 64
}

/*
Format characters in the format string for binary log messages
  a   : int16_t[32]
  b   : int8_t
  B   : uint8_t
  h   : int16_t
  H   : uint16_t
  i   : int32_t
  I   : uint32_t
  f   : float
  d   : double
  n   : char[4]
  N   : char[16]
  Z   : char[64]
  c   : int16_t * 100
  C   : uint16_t * 100
  e   : int32_t * 100
  E   : uint32_t * 100
  L   : int32_t latitude/longitude
  M   : uint8_t flight mode
  q   : int64_t
  Q   : uint64_t
 */

```


## 2.Log datas

Log data structure is defined below, all include the packet header and timestamp followed by valid data.
There are several special data message, PARAM(msgid=64), MSG(msgid=91), UNITS (msgid=177), MULTI (msgid=178).
They can only be printed, and cannot be used to draw curves.

``` C++
#define LOG_PACKET_HEADER	       uint8_t head1 = 0xA3, head2 = 0x95, msgid=128;
struct PACKED log_xxx_MSG {
    LOG_PACKET_HEADER;
    uint64_t time_us; // timestamp in us.
    ...               // valid log data
    ...
    ...
}

```

A parsing code [Ardupilog](https://github.com/Georacer/ardupilog) written in matlab can be referred to.


