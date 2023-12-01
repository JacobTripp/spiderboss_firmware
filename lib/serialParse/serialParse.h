#ifndef SerialParse_h
#define SerialParse_h
class SerialParse {
};
void recvWithStartEndMarkers();
void parseData();
void showParsedData();

const byte numChars;
char receivedChars[0];
char tempChars[0];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[0];
int integerFromPC
float floatFromPC;

boolean newData;
#endif
