# IBM 41K6814 AKA Futaba M202MD08A Arduino / Python
[This is a arduino project for output of data to VFD IBM 41k6814](https://github.com/homez/arduino_41k6814)

## I also 'recently' aquired one of these displays, and I'd like to make it do something.

I'll be compliluing any information I find on the subject, so one migth be able to use this as a reference.

## Project goals

* Connect the display to a computer, using a USB to RS-485 converter
* Display symbols on device
* Display computer stats (CPU%, GPU%, RAM%, etc.)

### [Heres another take at this problenm](https://github.com/gzalo/LCD-M202MD08A)

### [IBM P/N 41K6814 20x2 VFD POS "Pole" display aka Futaba M202MD08A](https://forum.arduino.cc/t/ibm-p-n-41k6814-20x2-vfd-pos-pole-display-aka-futaba-m202md08a/257190)

[system](/u/system)

[2014. sept.](/t/ibm-p-n-41k6814-20x2-vfd-pos-pole-display-aka-futaba-m202md08a/257190 "Date posted")post #1

I bought one of these on ebay quite cheaply, brand new old stock. It seems that there are a lot of them out there.

What i have learned:

1: The four pin connector wants +12vdc on pin 1, ground on pin 4, and pins 2 and 3 are likely signals "A" and "B" in an RS485 differential pair (there is an RS485 line driver on the board; IBM likes using RS485, etc).

2: IBM won't say a word

3: Futaba will tell you that it is an IBM design and to talk to IBM.

4: There are, however, some very similar Futaba displays out there, including the MD202MD08 (without the "A") that people have successfully interfaced in DIY projects.

I'm guessing that this is just an RS485 version of the MD202MD08 and that Futaba is just under NDA with IBM.

I'm hoping, further, that it can be made to work with the PrimeVFD library, here: [Arduino Playground - PrimeVfd 14](http://playground.arduino.cc/Main/PrimeVfd)

It is likely possible to scrape the rs485 driver right off the board and install a max232 module. But I found some chinese ebayer who sells rs485 to ttl modules for like a buck, so i have one on order.

I paid $6 shipped on ebay for an IBM P/N 10N1002 Y-cable providing 3 of the funky 4p4c connectors. As others have found, when i apply 12vdc across pins 1 and 4, it waits a bit and then displays "U001".

It's very easy to open the case. just squeeze gently along the bottom of the back of the case, where the vents are, and lift it apart. Three screws hold the display to the front of the case. There is room enough in here for an arduino nano or whathaveyou if you wanted to embed something right in it.

It's probably possible to remove the IBM connector and replace it with a DB9 or RJ45 but this would require unsticking the glass from the board and i don't want to do that just now.

Evidence found so far:

You'll notice that both of these comments, and the PrimeVFD info, refer to it's slowness and complexity.

So, well, Noritake modules are better. But who cares, i have this giant Futaba and i want to use it.

### Serial specs*:

I have the same project, i have 2 of M202MD08A vfd displays.
some additional info:
      * IBM 12bit rs485 protocol named "4680 Store Systems Serial I/O Channel Attachment Information"      // _I suspect this document contains the pinout, speeds and command set._
      * www.elektroda.pl/rtvforum/download.php?id=329610  // _This link is broken_
      * http://www.screenkeys.com/downloads/Technical%20Reference%20Manual%20for%20SK-7510.pdf 30      // _This page requires a log-in._
      * page 11 vfd display address is 24 or 25
      * 12 bit rs485: 1 start 8 data 1 address and 2 stop bits at 187.5 kbps _(187500 8N2)_ serial packets, and I not found commands for vfd. That will be nice.

### emondaca, _same page still_

```
2020. june.post #3
I need to emulate a Pole display and a SureMark printer to communicate with a SurePos700.
I know the document from IBM "4680 Store System Serial I/O Channel Attachment Information" contains all a I need, but is not online at the present.
¿Have somebody a old copy on pdf to post o send to me?      _Still looking for it, If I find it I'll upload it for good._

Thanks in advance.
Cheers
```

### [We display information on VFD IBM 41K6814](http://we.easyelectronics.ru/lcd_gfx/vyvodim-informaciyu-na-vfd-ibm-41k6814.html)

On occasion, I received a VFD display from an IBM 41K6814 POS terminal.  
![](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/2ace14.jpg)  
  
Well, as soon as I got it, I bought it through an ad for 334 rubles.  
  
2 lines of 20 characters.  
![top pcb](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/7b425e.jpg)![bottom pcb](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/68b6e9.jpg)  
  
The board says M202MD08A FUTABA.  
  
Search queries yield very little information.  
Mostly questions on various forums about how to work with it.  
The Poles have the most information, where they replaced the display controller with their own.  
  
![](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/3224d7.jpg)  
RS485 connection interface.  
1 - +12v  
2 - A  
3 - B  
4 - GND  
  
The control protocol is quite strange, in my understanding it is a kind of mixture of protocols from both pdf files.  
  
Even though the documentation says:  

    Twelve Bit Asynchronous1. Bit 1 = Start Bit2. Bits 2 to 9 = Data Bits 0 to 73. Bit 10 = Address Bit4. Bits 11 and 12 = Stop Bits(minimum)Bit Rate = 187.5 Kbits per second

  
I got a stable reception only with one stop bit.  
  
If you simply apply power, the display will show “U001” in the second line.  
![U001](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/3d538c.jpg)  
  
All the data below was obtained from the working system by taking a dump of information running in RS485.  
  
The documentation says that the display can have an address of 24 or 25 (It looks like mine is 25).  
When receiving 0x1A5, the display can respond with two options:  
1\. 0x15A - End of Poll (name from the documentation)  
2\. 0x125 xx cc cc 0x17E - data packet.  
xx - data  
cc cc - two bytes crc16 x25 IBM-SDLC  
The amount of data transmitted is not known in advance.  
  
here is a dump of the exchange during initialization:  

    >> 0x1A5>> 0x1A5<< 0x125 0x0F 0x3B 0xAA 0x17E>> 0x125 0x83 0x5F 0xE4 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x63 0x51 0x03 0x17E>> 0x125 0x00 0x00 0x00 0x01 0x3B 0x98 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x20 0x10 0x20 0x06 0x00 0x02 0x12 0xF9 0xA8 0x17E>> 0x125 0x21 0x47 0x62 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x22 0x40 0x00 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x8E 0xFE 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x41 0x41 0x01 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x24 0x40 0x01 0x06 0x09 0x1C 0x08 0x1C 0x09 0x06 0x00 0xA3 0x82 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x61 0x43 0x20 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x26 0x40 0x02 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x21 0x3B 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x81 0x4D 0xC7 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x28 0x40 0x03 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x01 0x3F 0x17E>> 0x1A5>> 0x1A5<< 0x125 0xA1 0x4F 0xE6 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x2A 0x40 0x04 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0xC1 0x7D 0x17E>> 0x1A5>> 0x1A5<< 0x125 0xC1 0x49 0x85 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x2C 0x40 0x05 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x4B 0xC5 0x17E>> 0x1A5>> 0x1A5<< 0x125 0xE1 0x4B 0xA4 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x2E 0x40 0x06 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x6E 0xB8 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x01 0x45 0x43 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x20 0x40 0x07 0x00 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x55 0x48 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x21 0x47 0x62 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x22 0x41 0x0A 0x00 0x4D 0x9E 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x41 0x41 0x01 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x24 0x81 0x28 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x80 0x96 0x77 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x61 0x43 0x20 0x17E>> 0x1CA>> 0x1CA>> 0x125 0x26 0x82 0x28 0x55 0x30 0x30 0x37 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0xEC 0x86 0xFD 0x17E>> 0x1A5>> 0x1A5<< 0x125 0x81 0x4D 0xC7 0x17E

  
After it, U007 is displayed on the display,  
![](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/13/ceb7e2.jpg)  
  
or whatever you send to it...  
  
![](http://we.easyelectronics.ru/uploads/images/00/15/45/2017/04/12/b1ae7a.jpg)  
  
Its Russian encoding is peculiar.  
From 0x80 to 0xAF there is “ABVG... mnop”, and the continuation from 0xE0 to 0xF1 is “rust... eyuyaYo”.  
  
It is possible to change information both on a specific line and on the entire display with one command.  

    0x17A0x03 0x00 0x00 0x00 LL - длина сообщенияXX - сообщениеСС СС - CRC 0x17E

  
For example:  

    0x17A 0x03 0x00 0x00 0x00 0x28 0x55 0x30 0x30 0x35 0x2E 0x34 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0xF6 0x11 0x17E

  
But even if you display only one character with this command, all unused familiar spaces will be cleared.  
  
To change one specific line  

    0x1250x24 - not unambiguous, either this is the sequence 20, 22, 24, 26, 28, 2A, 2C, 2E, or in the lower nibble the higher nibble of the received status from the display is transmitted (both options work) 0x81 - line “number” 0x81 first 0x82 second0x28XX - 20 bytes of dataDD - sum of data & 0xFFCC SS - CRC 0x17E

  
For example, it will clear the first line:  

    0x125 0x24 0x81 0x28 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x20 0x80 0x96 0x77 0x17E

  
  
Loading a symbol  

    0x1250x24 - not unambiguous, either this is the sequence 20, 22, 24, 26, 28, 2A, 2C, 2E, or the lower nib is the highest nib of the received status from the display (both options work) 0x40 - 0x01 - from 0x00 to 0x07 character number XX - 8 bytes of data, only the first 7.CC CC is used - CRC 0x17E

  
For example, loading 1 symbol "euro sign"  

    0x125 0x24 0x40 0x01 0x06 0x09 0x1C 0x08 0x1C 0x09 0x06 0x00 0xA3 0x82 0x17E

  
  
To communicate with the display, an Arduino Mega 2560 and MAX13485 were used.  
But for some reason I had to connect AB, BA, otherwise it didn’t work.  
  
  
[Mega2560 and 41k6814](https://github.com/homez/arduino_41k6814)  
[Atmega328p and 41k6814](https://github.com/gzalo/LCD-M202MD08A)

*   [VFD IBM 41K6814](http://we.easyelectronics.ru/tag/VFD%20IBM%2041K6814/)

*   [](#)+3[](#)
*   12 апреля 2017, 22:52
*   [HOMEZ](http://we.easyelectronics.ru/profile/HOMEZ/)
*   2

Файлы в топике: [ibm futaba pdf.zip](http://we.easyelectronics.ru/attachments/get/2749), [futaba\_rs485.zip](http://we.easyelectronics.ru/attachments/get/2751)
