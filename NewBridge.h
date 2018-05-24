/*
  Copyright (c) 2013 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef NEWBRIDGE_H_
#define NEWBRIDGE_H_

#ifndef BRIDGE_BAUDRATE
#define BRIDGE_BAUDRATE 250000
#endif

#include <Arduino.h>
#include <Stream.h>

class BridgeClass {
  public:
    BridgeClass(Stream &_stream);
    void begin();

    // Methods to handle key/value datastore
    void put(const char *key, const char *value);
    void put(const String &key, const String &value)
    {
      put(key.c_str(), value.c_str());
    }
    unsigned int get(const char *key, uint8_t *buff, unsigned int size);
    unsigned int get(const char *key, char *value, unsigned int maxlen)
    {
      return get(key, reinterpret_cast<uint8_t *>(value), maxlen);
    }

    // Trasnfer a frame (with error correction and response)
    uint16_t transfer(const uint8_t *buff1, uint16_t len1,
                      const uint8_t *buff2, uint16_t len2,
                      const uint8_t *buff3, uint16_t len3,
                      uint8_t *rxbuff, uint16_t rxlen);
    // multiple inline versions of the same function to allow efficient frame concatenation
    uint16_t transfer(const uint8_t *buff1, uint16_t len1)
    {
      return transfer(buff1, len1, NULL, 0);
    }
    uint16_t transfer(const uint8_t *buff1, uint16_t len1,
                      uint8_t *rxbuff, uint16_t rxlen)
    {
      return transfer(buff1, len1, NULL, 0, rxbuff, rxlen);
    }
    uint16_t transfer(const uint8_t *buff1, uint16_t len1,
                      const uint8_t *buff2, uint16_t len2,
                      uint8_t *rxbuff, uint16_t rxlen)
    {
      return transfer(buff1, len1, buff2, len2, NULL, 0, rxbuff, rxlen);
    }

    uint16_t getBridgeVersion()
    {
      return bridgeVersion;
    }

    static const int TRANSFER_TIMEOUT = 0xFFFF;

  private:
    uint8_t index;
    int timedRead(unsigned int timeout);
    void dropAll();
    uint16_t bridgeVersion;

  private:
    void crcUpdate(uint8_t c);
    void crcReset();
    void crcWrite();
    bool crcCheck(uint16_t _CRC);
    uint16_t CRC;

  private:
    static const char CTRL_C = 3;
    Stream &stream;
    bool started;
    uint8_t max_retries;
};

// This subclass uses a serial port Stream
class SerialBridgeClass : public BridgeClass {
  public:
    SerialBridgeClass(HardwareSerial &_serial)
      : BridgeClass(_serial), serial(_serial) {
      // Empty
    }

    void begin(unsigned long baudrate = BRIDGE_BAUDRATE) {
      serial.begin(baudrate);
      BridgeClass::begin();
    }


  private:
    HardwareSerial &serial;
};

extern SerialBridgeClass Bridge;

class ConsoleClass : public Stream {
  public:
    // Default constructor uses global Bridge instance
    ConsoleClass();
    // Constructor with a user provided BridgeClass instance
    ConsoleClass(BridgeClass &_b);
    ~ConsoleClass();

    void begin();
    void end();

    void buffer(uint8_t size);
    void noBuffer();

    bool connected();

    // Stream methods
    // (read from console socket)
    int available();
    int read();
    int peek();
    // (write to console socket)
    size_t write(uint8_t);
    size_t write(const uint8_t *buffer, size_t size);
    void flush();

    operator bool () {
      return connected();
    }

  private:
    BridgeClass &bridge;

    void doBuffer();
    uint8_t inBuffered;
    uint8_t inReadPos;
    static const int BUFFER_SIZE = 32;
    uint8_t *inBuffer;

    bool autoFlush;
    uint8_t outBuffered;
    uint8_t outBufferSize;
    uint8_t *outBuffer;
};

extern ConsoleClass Console;

#define FILE_READ 0
#define FILE_WRITE 1
#define FILE_APPEND 2

class File : public Stream {

  public:
    File(BridgeClass &b = Bridge);
    File(const char *_filename, uint8_t _mode, BridgeClass &b = Bridge);
    ~File();

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual int read();
    virtual int peek();
    virtual int available();
    virtual void flush();
    int read(void *buf, uint16_t nbyte);
    boolean seek(uint32_t pos);
    uint32_t position();
    uint32_t size();
    void close();
    operator bool();
    const char * name();
    boolean isDirectory();
    File openNextFile(uint8_t mode = FILE_READ);
    void rewindDirectory(void);

    //using Print::write;

  private:
    void doBuffer();
    uint8_t buffered;
    uint8_t readPos;
    uint16_t dirPosition;
    static const int BUFFER_SIZE = 256;
    uint8_t buffer[BUFFER_SIZE];


  private:
    BridgeClass &bridge;
    String filename;
    uint8_t mode;
    uint8_t handle;

};

class FileSystemClass {
  public:
    FileSystemClass() : bridge(Bridge) { }
    FileSystemClass(BridgeClass &_b) : bridge(_b) { }

    boolean begin();

    // Open the specified file/directory with the supplied mode (e.g. read or
    // write, etc). Returns a File object for interacting with the file.
    // Note that currently only one file can be open at a time.
    File open(const char *filename, uint8_t mode = FILE_READ);

    // Methods to determine if the requested file path exists.
    boolean exists(const char *filepath);

    // Create the requested directory hierarchy--if intermediate directories
    // do not exist they will be created.
    boolean mkdir(const char *filepath);

    // Delete the file.
    boolean remove(const char *filepath);

    boolean rmdir(const char *filepath);

  private:
    friend class File;

    BridgeClass &bridge;
};

extern FileSystemClass FileSystem;



class MailboxClass {
  public:
    MailboxClass(BridgeClass &b = Bridge) : bridge(b) { }

    void begin() { }
    void end() { }

    // Receive a message and store it inside a buffer
    unsigned int readMessage(uint8_t *buffer, unsigned int size);
    // Receive a message and store it inside a String
    void readMessage(String &str, unsigned int maxLength = 128);

    // Send a message
    void writeMessage(const uint8_t *buffer, unsigned int size);
    // Send a message
    void writeMessage(const String& str);
    // Send a JSON message
    void writeJSON(const String& str);

    // Return the size of the next available message, 0 if there are
    // no messages in queue.
    unsigned int messageAvailable();

  private:
    BridgeClass &bridge;
};

extern MailboxClass Mailbox;


class Process : public Stream {
  public:
    // Constructor with a user provided BridgeClass instance
    Process(BridgeClass &_b = Bridge) :
      bridge(_b), started(false), buffered(0), readPos(0) { }
    ~Process();

    void begin(const String &command);
    void addParameter(const String &param);
    unsigned int run();
    void runAsynchronously();
    boolean running();
    unsigned int exitValue();
    void close();

    unsigned int runShellCommand(const String &command);
    void runShellCommandAsynchronously(const String &command);

    operator bool () {
      return started;
    }

    // Stream methods
    // (read from process stdout)
    int available();
    int read();
    int peek();
    // (write to process stdin)
    size_t write(uint8_t);
    void flush();
    // TODO: add optimized function for block write

  private:
    BridgeClass &bridge;
    unsigned int handle;
    String *cmdline;
    boolean started;

  private:
    void doBuffer();
    uint8_t buffered;
    uint8_t readPos;
    static const int BUFFER_SIZE = 64;
    uint8_t buffer[BUFFER_SIZE];

};


#endif /* BRIDGE_H_ */

#ifndef _UTIL_WORD_H_
#define _UTIL_WORD_H_
/**
@file
Utility Functions for Manipulating Words

@defgroup util_word "util/word.h": Utility Functions for Manipulating Words
@code#include "util/word.h"@endcode

This header file provides utility functions for manipulating words.

*/
/*

  word.h - Utility Functions for Manipulating Words

  This file is part of ModbusMaster.

  ModbusMaster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ModbusMaster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ModbusMaster.  If not, see <http://www.gnu.org/licenses/>.

  Written by Doc Walker (Rx)
  Copyright © 2009-2015 Doc Walker <4-20ma at wvfans dot net>

*/


/** @ingroup util_word
    Return low word of a 32-bit integer.

    @param uint32_t ww (0x00000000..0xFFFFFFFF)
    @return low word of input (0x0000..0xFFFF)
*/
static inline uint16_t lowWord(uint32_t ww)
{
  return (uint16_t) ((ww) & 0xFFFF);
}


/** @ingroup util_word
    Return high word of a 32-bit integer.

    @param uint32_t ww (0x00000000..0xFFFFFFFF)
    @return high word of input (0x0000..0xFFFF)
*/
static inline uint16_t highWord(uint32_t ww)
{
  return (uint16_t) ((ww) >> 16);
}


#endif /* _UTIL_WORD_H_ */



#ifndef _UTIL_CRC16_H_
#define _UTIL_CRC16_H_



/**
@file
CRC Computations

@defgroup util_crc16 "util/crc16.h": CRC Computations
@code#include "util/crc16.h"@endcode

This header file provides functions for calculating
cyclic redundancy checks (CRC) using common polynomials.
Modified by Doc Walker to be processor-independent (removed inline
assembler to allow it to compile on SAM3X8E processors).

@par References:
Jack Crenshaw's "Implementing CRCs" article in the January 1992 issue of @e
Embedded @e Systems @e Programming. This may be difficult to find, but it
explains CRC's in very clear and concise terms. Well worth the effort to
obtain a copy.

*/
/* Copyright (c) 2002, 2003, 2004  Marek Michalkiewicz
   Copyright (c) 2005, 2007 Joerg Wunsch
   Copyright (c) 2013 Dave Hylands
   Copyright (c) 2013 Frederic Nadeau
   Copyright (c) 2015 Doc Walker
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */




/** @ingroup util_crc16
    Processor-independent CRC-16 calculation.

    Polynomial: x^16 + x^15 + x^2 + 1 (0xA001)<br>
    Initial value: 0xFFFF

    This CRC is normally used in disk-drive controllers.

    @param uint16_t crc (0x0000..0xFFFF)
    @param uint8_t a (0x00..0xFF)
    @return calculated CRC (0x0000..0xFFFF)
*/
static uint16_t crc16_update(uint16_t crc, uint8_t a)
{
  int i;

  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }

  return crc;
}



#endif /* _UTIL_CRC16_H_ */

