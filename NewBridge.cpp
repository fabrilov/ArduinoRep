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

#include "NewBridge.h"

BridgeClass::BridgeClass(Stream &_stream) :
  index(0), stream(_stream), started(false), max_retries(0) {
  // Empty
}

void BridgeClass::begin() {
  if (started)
    return;
  started = true;

  // Wait for U-boot to finish startup
/*
  do {
    dropAll();
    delay(1000);
  } while (stream.available() > 0);
*/
  while (true) {
/*
    // Bridge interrupt:
    // - Ask the bridge to close itself
    uint8_t quit_cmd[] = {'X', 'X', 'X', 'X', 'X'};
    max_retries = 1;
  //  transfer(quit_cmd, 5);

    // Bridge startup:
    // - If the bridge is not running starts it safely
    //stream.print(CTRL_C);

    delay(250);
	stream.print(F("\n"));
    delay(250);
	stream.print(F("root\n"));
	delay(250);
    stream.print(F("\n"));
    delay(250);

	dropAll();
    stream.print(F("\n"));
    delay(500);
    // Wait for OpenWRT message
    // "Press enter to activate console"
    stream.print(F("run-bridge\n"));
    delay(500);
*/
    dropAll();

    // Reset the brigde to check if it is running
    uint8_t cmd[] = {'X', 'X', '1', '0', '0'};
    uint8_t res[4];
    max_retries = 20;
    uint16_t l = transfer(cmd, 5, res, 4);
    if (l == TRANSFER_TIMEOUT) {
      // Bridge didn't start...
      // Maybe the board is starting-up?

      // Wait and retry
      delay(1000);
      continue;
    }
    if (res[0] != 0)
      while (true);

    // Detect bridge version
    if (l == 4) {
      bridgeVersion = (res[1]-'0')*100 + (res[2]-'0')*10 + (res[3]-'0');
    } else {
      // Bridge v1.0.0 didn't send any version info
      bridgeVersion = 100;
    }

    max_retries = 20;
    return;
  }
}

void BridgeClass::put(const char *key, const char *value) {
  // TODO: do it in a more efficient way
  String cmd = "D";
  uint8_t res[1];
  cmd += key;
  cmd += "\xFE";
  cmd += value;
  transfer((uint8_t*)cmd.c_str(), cmd.length(), res, 1);
}

unsigned int BridgeClass::get(const char *key, uint8_t *value, unsigned int maxlen) {
  uint8_t cmd[] = {'d'};
  unsigned int l = transfer(cmd, 1, (uint8_t *)key, strlen(key), value, maxlen);
  if (l < maxlen)
    value[l] = 0; // Zero-terminate string
  return l;
}

//#if defined(ARDUINO_ARCH_AVR)
//// AVR use an optimized implementation of CRC
//
//#include "crc16.h"
//#else
// Generic implementation for non-AVR architectures
uint16_t _crc_ccitt_update(uint16_t crc, uint8_t data)
{
  data ^= crc & 0xff;
  data ^= data << 4;
  return ((((uint16_t)data << 8) | ((crc >> 8) & 0xff)) ^
          (uint8_t)(data >> 4) ^
          ((uint16_t)data << 3));
}
//#endif

void BridgeClass::crcUpdate(uint8_t c) {
  CRC = _crc_ccitt_update(CRC, c);
}

void BridgeClass::crcReset() {
  CRC = 0xFFFF;
}

void BridgeClass::crcWrite() {
  stream.write((char)(CRC >> 8));
  stream.write((char)(CRC & 0xFF));
}

bool BridgeClass::crcCheck(uint16_t _CRC) {
  return CRC == _CRC;
}

uint16_t BridgeClass::transfer(const uint8_t *buff1, uint16_t len1,
                               const uint8_t *buff2, uint16_t len2,
                               const uint8_t *buff3, uint16_t len3,
                               uint8_t *rxbuff, uint16_t rxlen)
{
  uint16_t len = len1 + len2 + len3;
  uint8_t retries = 0;
  for ( ; retries < max_retries; retries++, delay(1000), dropAll() /* Delay for retransmission */) {
    // Send packet
    crcReset();
    stream.write((char)0xFF);                // Start of packet (0xFF)
    crcUpdate(0xFF);
    stream.write((char)index);               // Message index
    crcUpdate(index);
    stream.write((char)((len >> 8) & 0xFF)); // Message length (hi)
    crcUpdate((len >> 8) & 0xFF);
    stream.write((char)(len & 0xFF));        // Message length (lo)
    crcUpdate(len & 0xFF);
    for (uint16_t i = 0; i < len1; i++) { // Payload
      stream.write((char)buff1[i]);
      crcUpdate(buff1[i]);
    }
    for (uint16_t i = 0; i < len2; i++) { // Payload
      stream.write((char)buff2[i]);
      crcUpdate(buff2[i]);
    }
    for (uint16_t i = 0; i < len3; i++) { // Payload
      stream.write((char)buff3[i]);
      crcUpdate(buff3[i]);
    }
    crcWrite();                     // CRC
    //stream.write((char)0xFF);                // End of packet (0xFF)
    // Wait for ACK in 100ms
    if (timedRead(100) != 0xFF)
      continue;
    crcReset();
    crcUpdate(0xFF);

    // Check packet index
    if (timedRead(5) != index)
      continue;
    crcUpdate(index);

    // Recv len
    int lh = timedRead(10);
    if (lh < 0)
      continue;
    crcUpdate(lh);
    int ll = timedRead(10);
    if (ll < 0)
      continue;
    crcUpdate(ll);
    uint16_t l = lh;
    l <<= 8;
    l += ll;

    // Recv data
    for (uint16_t i = 0; i < l; i++) {
      // Cut received data if rxbuffer is too small
      if (i >= rxlen)
          break;
      int c = timedRead(5);
      if (c < 0)
        continue;
      rxbuff[i] = c;
      crcUpdate(c);
    }

    // Check CRC
    int crc_hi = timedRead(5);
    if (crc_hi < 0)
      continue;
    int crc_lo = timedRead(5);
    if (crc_lo < 0)
      continue;
    if (!crcCheck((crc_hi << 8) + crc_lo))
      continue;

    // Increase index
    index++;

    // Return bytes received
    if (l > rxlen)
      return rxlen;
    return l;
  }

  // Max retries exceeded
  return TRANSFER_TIMEOUT;
}

int BridgeClass::timedRead(unsigned int timeout) {
  int c;
  timeout = timeout *10;
  unsigned long _startMillis = millis();
  do {
    c = stream.read();
    if (c >= 0) return c;
  } while (millis() - _startMillis < timeout);
  return -1;     // -1 indicates timeout
}

void BridgeClass::dropAll() {

  while (stream.available() > 0) {
     stream.read();
	 
  }
}

// Bridge instance
#ifdef __AVR_ATmega32U4__
// Leonardo variants (where HardwareSerial is Serial1)
SerialBridgeClass Bridge(Serial1);
#else
SerialBridgeClass Bridge(Serial);
#endif


// Default constructor uses global Bridge instance
ConsoleClass::ConsoleClass() :
  bridge(Bridge), inBuffered(0), inReadPos(0), inBuffer(NULL),
  autoFlush(true)
{
  // Empty
}

// Constructor with a user provided BridgeClass instance
ConsoleClass::ConsoleClass(BridgeClass &_b) :
  bridge(_b), inBuffered(0), inReadPos(0), inBuffer(NULL),
  autoFlush(true)
{
  // Empty
}

ConsoleClass::~ConsoleClass() {
  end();
}

size_t ConsoleClass::write(uint8_t c) {
  if (autoFlush) {
    uint8_t tmp[] = { 'P', c };
    bridge.transfer(tmp, 2);
    return 1;
  } else {
    outBuffer[outBuffered++] = c;
    if (outBuffered == outBufferSize)
      flush();
  }
}

size_t ConsoleClass::write(const uint8_t *buff, size_t size) {
  if (autoFlush) {
    // TODO: do it in a more efficient way
    uint8_t *tmp = new uint8_t[size + 1];
    tmp[0] = 'P';
    memcpy(tmp + 1, buff, size);
    bridge.transfer(tmp, size + 1);
    delete[] tmp;
    return size;
  } else {
    while (size > 0) {
      outBuffer[outBuffered++] = *buff++;
      size--;
      if (outBuffered == outBufferSize)
        flush();
    }
  }
}

void ConsoleClass::flush() {
  if (autoFlush)
    return;

  bridge.transfer(outBuffer, outBuffered);
  outBuffered = 1;
}

void ConsoleClass::noBuffer() {
  if (autoFlush)
    return;
  delete[] outBuffer;
  autoFlush = true;
}

void ConsoleClass::buffer(uint8_t size) {
  noBuffer();
  if (size == 0)
    return;
  outBuffer = new uint8_t[size + 1];
  outBuffer[0] = 'P'; // WRITE tag
  outBufferSize = size + 1;
  outBuffered = 1;
  autoFlush = false;
}

bool ConsoleClass::connected() {
  uint8_t tmp = 'a';
  bridge.transfer(&tmp, 1, &tmp, 1);
  return tmp == 1;
}

int ConsoleClass::available() {
  // Look if there is new data available
  doBuffer();
  return inBuffered;
}

int ConsoleClass::read() {
  doBuffer();
  if (inBuffered == 0)
    return -1; // no chars available
  else {
    inBuffered--;
    return inBuffer[inReadPos++];
  }
}

int ConsoleClass::peek() {
  doBuffer();
  if (inBuffered == 0)
    return -1; // no chars available
  else
    return inBuffer[inReadPos];
}

void ConsoleClass::doBuffer() {
  // If there are already char in buffer exit
  if (inBuffered > 0)
    return;

  // Try to buffer up to 32 characters
  inReadPos = 0;
  uint8_t tmp[] = { 'p', BUFFER_SIZE };
  inBuffered = bridge.transfer(tmp, 2, inBuffer, BUFFER_SIZE);
}

void ConsoleClass::begin() {
  bridge.begin();
  end();
  inBuffer = new uint8_t[BUFFER_SIZE];
}

void ConsoleClass::end() {
  noBuffer();
  if (inBuffer) {
    delete[] inBuffer;
    inBuffer = NULL;
  }
}

ConsoleClass Console;


File::File(BridgeClass &b) : mode(255), bridge(b) {
  // Empty
}

File::File(const char *_filename, uint8_t _mode, BridgeClass &b) : mode(_mode), bridge(b) {
  filename = _filename;
  char modes[] = {'r', 'w', 'a'};
  uint8_t cmd[] = {'F', modes[mode]};
  uint8_t res[2];
  dirPosition = 1;
  bridge.transfer(cmd, 2, (uint8_t*)filename.c_str(), filename.length(), res, 2);
  if (res[0] != 0) { // res[0] contains error code
    mode = 255; // In case of error keep the file closed
    return;
  }
  handle = res[1];
  buffered = 0;
}

File::operator bool() {
  return (mode != 255);
}

File::~File() {
  close();
}

size_t File::write(uint8_t c) {
  return write(&c, 1);
}

size_t File::write(const uint8_t *buf, size_t size) {
  if (mode == 255)
    return -1;
  uint8_t cmd[] = {'g', handle};
  uint8_t res[1];
  bridge.transfer(cmd, 2, buf, size, res, 1);
  if (res[0] != 0) // res[0] contains error code
    return -res[0];
  return size;
}

int File::read() {
  doBuffer();
  if (buffered == 0)
    return -1; // no chars available
  else {
    buffered--;
    return buffer[readPos++];
  }
}

int File::peek() {
  doBuffer();
  if (buffered == 0)
    return -1; // no chars available
  else
    return buffer[readPos];
}

boolean File::seek(uint32_t position) {
  uint8_t cmd[] = {
    's',
    handle,
    (position >> 24) & 0xFF,
    (position >> 16) & 0xFF,
    (position >> 8) & 0xFF,
    position & 0xFF
  };
  uint8_t res[1];
  bridge.transfer(cmd, 6, res, 1);
  if (res[0] == 0) {
    // If seek succeed then flush buffers
    buffered = 0;
    return true;
  }
  return false;
}

uint32_t File::position() {
  uint8_t cmd[] = {'S', handle};
  uint8_t res[5];
  bridge.transfer(cmd, 2, res, 5);
  //err = res[0]; // res[0] contains error code
  uint32_t pos = res[1] << 24;
  pos += res[2] << 16;
  pos += res[3] << 8;
  pos += res[4];
  return pos - buffered;
}

void File::doBuffer() {
  // If there are already char in buffer exit
  if (buffered > 0)
    return;

  // Try to buffer up to BUFFER_SIZE characters
  readPos = 0;
  uint8_t cmd[] = {'G', handle, BUFFER_SIZE - 1};
  buffered = bridge.transfer(cmd, 3, buffer, BUFFER_SIZE);
  //err = buff[0]; // First byte is error code
  if (BridgeClass::TRANSFER_TIMEOUT == buffered || 0 == buffered) {
    // transfer failed to retrieve any data
    buffered = 0;
  } else {
    // transfer retrieved at least one byte of data so skip the error code character
    readPos++;
    buffered--;
  }
}

int File::available() {
  // Look if there is new data available
  doBuffer();
  return buffered;
}

void File::flush() {
}

int File::read(void *buff, uint16_t nbyte) {
  uint16_t n = 0;
  uint8_t *p = reinterpret_cast<uint8_t *>(buff);
  while (n < nbyte) {
    if (buffered == 0) {
      doBuffer();
      if (buffered == 0)
        break;
    }
    *p++ = buffer[readPos++];
    buffered--;
    n++;
  }
  return n;
}

uint32_t File::size() {
  if (bridge.getBridgeVersion() < 101)
	return 0;
  uint8_t cmd[] = {'t', handle};
  uint8_t buff[5];
  bridge.transfer(cmd, 2, buff, 5);
  //err = res[0]; // First byte is error code
  uint32_t res;
  res  = ((uint32_t)buff[1]) << 24;
  res |= ((uint32_t)buff[2]) << 16;
  res |= ((uint32_t)buff[3]) << 8;
  res |= ((uint32_t)buff[4]);
  return res;
}

void File::close() {
  if (mode == 255)
    return;
  uint8_t cmd[] = {'f', handle};
  uint8_t ret[1];
  bridge.transfer(cmd, 2, ret, 1);
  mode = 255;
}

const char *File::name() {
  return filename.c_str();
}


boolean File::isDirectory() {
  uint8_t res[1];
  uint8_t lenght;
  uint8_t cmd[] = {'i'};
  if (mode != 255)
    return 0;

  bridge.transfer(cmd, 1, (uint8_t *)filename.c_str(), filename.length(), res, 1);
  return res[0];
}


File File::openNextFile(uint8_t mode) {
  Process awk;
  char tmp;
  String command;
  String filepath;
  if (dirPosition == 0xFFFF) return File();

  command = "ls ";
  command += filename;
  command += " | awk 'NR==";
  command += dirPosition;
  command += "'";

  awk.runShellCommand(command);

  while (awk.running());

  command = "";

  while (awk.available()) {
    tmp = awk.read();
    if (tmp != '\n') command += tmp;
  }
  if (command.length() == 0)
    return File();
  dirPosition++;
  filepath = filename + "/" + command;
  return File(filepath.c_str(), mode);

}

void File::rewindDirectory(void) {
  dirPosition = 1;
}






boolean FileSystemClass::begin() {
  return true;
}

File FileSystemClass::open(const char *filename, uint8_t mode) {
  return File(filename, mode);
}

boolean FileSystemClass::exists(const char *filepath) {
  Process ls;
  ls.begin("ls");
  ls.addParameter(filepath);
  int res = ls.run();
  return (res == 0);
}

boolean FileSystemClass::mkdir(const char *filepath) {
  Process mk;
  mk.begin("mkdir");
  mk.addParameter("-p");
  mk.addParameter(filepath);
  int res = mk.run();
  return (res == 0);
}

boolean FileSystemClass::remove(const char *filepath) {
  Process rm;
  rm.begin("rm");
  rm.addParameter(filepath);
  int res = rm.run();
  return (res == 0);
}

boolean FileSystemClass::rmdir(const char *filepath) {
  Process rm;
  rm.begin("rmdir");
  rm.addParameter(filepath);
  int res = rm.run();
  return (res == 0);
}

FileSystemClass FileSystem;


unsigned int MailboxClass::readMessage(uint8_t *buff, unsigned int size) {
  uint8_t tmp[] = { 'm' };
  return bridge.transfer(tmp, 1, buff, size);
}

void MailboxClass::readMessage(String &str, unsigned int maxLength) {
  uint8_t tmp[] = { 'm' };
  // XXX: Is there a better way to create the string?
  uint8_t buff[maxLength + 1];
  int l = bridge.transfer(tmp, 1, buff, maxLength);
  buff[l] = 0;
  str = (const char *)buff;
}

void MailboxClass::writeMessage(const uint8_t *buff, unsigned int size) {
  uint8_t cmd[] = {'M'};
  bridge.transfer(cmd, 1, buff, size, NULL, 0);
}

void MailboxClass::writeMessage(const String& str) {
  writeMessage((uint8_t*) str.c_str(), str.length());
}

void MailboxClass::writeJSON(const String& str) {
  uint8_t cmd[] = {'J'};
  bridge.transfer(cmd, 1, (uint8_t*) str.c_str(), str.length(), NULL, 0);
}

unsigned int MailboxClass::messageAvailable() {
  uint8_t tmp[] = {'n'};
  uint8_t res[2];
  bridge.transfer(tmp, 1, res, 2);
  return (res[0] << 8) + res[1];
}

MailboxClass Mailbox(Bridge);



Process::~Process() {
  close();
}

size_t Process::write(uint8_t c) {
  uint8_t cmd[] = {'I', handle, c};
  bridge.transfer(cmd, 3);
  return 1;
}

void Process::flush() {
}

int Process::available() {
  // Look if there is new data available
  doBuffer();
  return buffered;
}

int Process::read() {
  doBuffer();
  if (buffered == 0)
    return -1; // no chars available
  else {
    buffered--;
    return buffer[readPos++];
  }
}

int Process::peek() {
  doBuffer();
  if (buffered == 0)
    return -1; // no chars available
  else
    return buffer[readPos];
}

void Process::doBuffer() {
  // If there are already char in buffer exit
  if (buffered > 0)
    return;

  // Try to buffer up to 32 characters
  readPos = 0;
  uint8_t cmd[] = {'O', handle, sizeof(buffer)};
  buffered = bridge.transfer(cmd, 3, buffer, sizeof(buffer));
}

void Process::begin(const String &command) {
  close();
  cmdline = new String(command);
}

void Process::addParameter(const String &param) {
  *cmdline += "\xFE";
  *cmdline += param;
}

void Process::runAsynchronously() {
  uint8_t cmd[] = {'R'};
  uint8_t res[2];
  bridge.transfer(cmd, 1, (uint8_t*)cmdline->c_str(), cmdline->length(), res, 2);
  handle = res[1];

  delete cmdline;
  cmdline = NULL;

  if (res[0] == 0) // res[0] contains error code
    started = true;
}

boolean Process::running() {
  uint8_t cmd[] = {'r', handle};
  uint8_t res[1];
  bridge.transfer(cmd, 2, res, 1);
  return (res[0] == 1);
}

unsigned int Process::exitValue() {
  uint8_t cmd[] = {'W', handle};
  uint8_t res[2];
  bridge.transfer(cmd, 2, res, 2);
  return (res[0] << 8) + res[1];
}

unsigned int Process::run() {
  runAsynchronously();
  while (running())
    delay(100);
  return exitValue();
}

void Process::close() {
  if (started) {
    uint8_t cmd[] = {'w', handle};
    bridge.transfer(cmd, 2);
  }
  started = false;
}

unsigned int Process::runShellCommand(const String &command) {
  runShellCommandAsynchronously(command);
  while (running())
    delay(100);
  return exitValue();
}

void Process::runShellCommandAsynchronously(const String &command) {
  begin("/bin/sh");
  addParameter("-c");
  addParameter(command);
  runAsynchronously();
}


