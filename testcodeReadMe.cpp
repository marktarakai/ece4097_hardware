// ".'--'." -NS
//
//This program will allow for user input for the SPI connection and
//can be used to test specific values

#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <bitset>

using namespace std;

static const int CHANNEL = 0;

int main()
{
  int fd, result, input;
  unsigned char buffer[100];

  cout << "Starting resistor testing program" << endl;

  //Interface config
  //wiringPiSPISetup(CHANNEL, Bus_Speed)
  fd = wiringPiSPISetup(CHANNEL, 780800);

  cout << "Config initialized" << endl;

  buffer[0] = 0;
  buffer[1] = 0;
  wiringPiSPIDataRW(CHANNEL, buffer, 1);
  input = 0x00;


  sleep(3);

  while(input != 0xFF)
  {
    cout << "Enter a hexidecimal 2-byte code (0x## or ##), or FF to quit"
         << endl;
    cin >> hex >> input;
    if(input != 0xFF)
    {
      //Byte 1 of input is stored in buffer[0]
      //  This ranges from 0-3, 0 enables A, 1 enables B, 2 enables C, and
      //  3 enables all phases
      buffer[0] = input;    //  /16;

      //Byte 2 of input is stored in buffer[1]
      //  This ranges from 0-15 (0-F), where 0 enables 1 resistor, and
      //  F anables all resistors in the enabled phases
//      buffer[1] = input%16;


      cout << "Writing    " << bitset<32>(buffer[0]) << " to the array" << endl;
//      cout << "Following  " << bitset<32>(buffer[1]) << " to the array" << endl;


      //Writes the buffer as a whole to the array, sending both bytes
      result = wiringPiSPIDataRW(CHANNEL, buffer, 1);
//      cout << result << endl;
    }
//    sleep(5);
  }

  cout << "Resetting array to default 0x00" << endl;
  buffer[0] = 0;
  buffer[1] = 0;
  wiringPiSPIDataRW(CHANNEL, buffer, 1);
  sleep(2);

}
