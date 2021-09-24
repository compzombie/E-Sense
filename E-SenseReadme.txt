This project began as a submission to Otronicon that I was not able to present. If I can provide any more information, 
or you just want to update me on what awesome stuff you've all done with it, feel free to email me. 
MLMyerson@gmail.com

For anyone who is as green as I am when it comes to electronics, here are some setup instructions:
 -Please note that I was using an Arduino Uno. If you decide to just use the Atmega 328p, you'll need to look at its 
   data summary sheet. Of course, feel free to use something else.

Connect pins 5 - 12 to LEDs, make sure to ground them. I'm using the 5v power pin, with 410 ohm resistors. To save yourself
ALOT of time learning hardware debouncing on input, the secret is to bridge your input to your ground with a resistor (I used
1,000 ohm resistors). My input pins are set to 3 and 4. 