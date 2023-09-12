# IBM 41K6814 AKA Futaba M202MD08A Arduino / Python
This is a arduino project for output of data to VFD IBM 41k6814:
https://github.com/homez/arduino_41k6814
---
## I also 'recently' aquired one of these displays, and I'd like to make it do something.
I'll be compliluing any information I find on the subject, so one migth be able to use this as a reference.

### [IBM P/N 41K6814 20x2 VFD POS "Pole" display aka Futaba M202MD08A](https://forum.arduino.cc/t/ibm-p-n-41k6814-20x2-vfd-pos-pole-display-aka-futaba-m202md08a/257190)

<div class="topic-body clearfix"><div role="heading" aria-level="2" class="topic-meta-data"><div class="names trigger-user-card"><span class="first username staff admin moderator"><a href="/u/system" data-user-card="system" class="">system</a><span title="Ez a felhasználó egy moderátor" class="svg-icon-title"><svg class="fa d-icon d-icon-shield-alt svg-icon svg-node" aria-hidden="true"><use xlink:href="#shield-alt"></use></svg></span></span></div><div class="post-infos"><div class="post-info post-date"><a class="widget-link post-date" href="/t/ibm-p-n-41k6814-20x2-vfd-pos-pole-display-aka-futaba-m202md08a/257190" title="Közlés dátuma"><span title="2014. szept. 12., 01:00" data-time="1410476448000" data-format="tiny" class="relative-date">'14. szept.</span></a><a class="post_number">post #1</a></div><div class="read-state read" title="A bejegyzés olvasatlan"><svg class="fa d-icon d-icon-circle svg-icon svg-node" aria-hidden="true"><use xlink:href="#circle"></use></svg></div></div></div><div class="regular contents"><div class="cooked"><p>I bought one of these on ebay quite cheaply, brand new old stock. It seems that there are a lot of them out there.</p>
<p>What i have learned:</p>
<p>1: The four pin connector wants +12vdc on pin 1, ground on pin 4, and pins 2 and 3 are likely signals "A" and "B" in an RS485 differential pair (there is an RS485 line driver on the board; IBM likes using RS485, etc).</p>
<p>2: IBM won't say a word</p>
<p>3: Futaba will tell you that it is an IBM design and to talk to IBM.</p>
<p>4: There are, however, some very similar Futaba displays out there, including the MD202MD08 (without the "A") that people have successfully interfaced in DIY projects.</p>
<p>I'm guessing that this is just an RS485 version of the MD202MD08 and that Futaba is just under NDA with IBM.</p>
<p>I'm hoping, further, that it can be made to work with the PrimeVFD library, here: <a href="http://playground.arduino.cc/Main/PrimeVfd" class="inline-onebox">Arduino Playground - PrimeVfd <span class="badge badge-notification clicks" title="14 kattintás">14</span></a></p>
<p>It is likely possible to scrape the rs485 driver right off the board and install a max232 module. But I found some chinese ebayer who sells rs485 to ttl modules for like a buck, so i have one on order.</p>
<p>I paid $6 shipped on ebay for an IBM P/N 10N1002 Y-cable providing 3 of the funky 4p4c connectors. As others have found, when i apply 12vdc across pins 1 and 4, it waits a bit and then displays "U001".</p>
<p>It's very easy to open the case. just squeeze gently along the bottom of the back of the case, where the vents are, and lift it apart. Three screws hold the display to the front of the case. There is room enough in here for an arduino nano or whathaveyou if you wanted to embed something right in it.</p>
<p>It's probably possible to remove the IBM connector and replace it with a DB9 or RJ45 but this would require unsticking the glass from the board and i don't want to do that just now.</p>
<p>Evidence found so far:</p>
<p class="lazy-video-wrapper">    <div class="lazy-video-container youtube-onebox video-loaded" data-video-id="CcN8lIoj5jQ" data-video-title="IBM Futaba VFD Display driven by Microchip PIC microcontroller" data-video-start-time="0" data-provider-name="youtube">
      <iframe src="https://www.youtube.com/embed/CcN8lIoj5jQ?autoplay=1&amp;start=0" title="IBM Futaba VFD Display driven by Microchip PIC microcontroller" allowfullscreen="" scrolling="no" frameborder="0" seamless="seamless" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture"></iframe>

</div>
</p>


<p>You'll notice that both of these comments, and the PrimeVFD info, refer to it's slowness and complexity.</p>
<p>So, well, Noritake modules are better. But who cares, i have this giant Futaba and i want to use it.</p></div><div></div><section class="post-menu-area clearfix"></section></div><section class="post-actions">
  </section><div class="post-links-container"></div><div class="topic-map"></div></div>

### Serial specs*:

```
I have the same project, i have 2 of M202MD08A vfd displays.
some additional info:
      * IBM 12bit rs485 protocol named "4680 Store Systems Serial I/O Channel Attachment Information"      // _I suspect this document contains the pinout, speeds and command set._
      * www.elektroda.pl/rtvforum/download.php?id=329610  // _This link is broken_
      * http://www.screenkeys.com/downloads/Technical%20Reference%20Manual%20for%20SK-7510.pdf 30      // _This page requires a log-in._
      * page 11 vfd display address is 24 or 25
      * 12 bit rs485: 1 start 8 data 1 address and 2 stop bits at 187.5 kbps _(187500 8N2)_ serial packets, and I not found commands for vfd. That will be nice.
```

### emondaca, _same page still_

```
2020. june.post #3
I need to emulate a Pole display and a SureMark printer to communicate with a SurePos700.
I know the document from IBM "4680 Store System Serial I/O Channel Attachment Information" contains all a I need, but is not online at the present.
¿Have somebody a old copy on pdf to post o send to me?      _Still looking for it, If I find it I'll upload it for good._

Thanks in advance.
Cheers
```
