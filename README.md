# Midi-Control-Surface
The goal of the project is to build a usb midi controller that is capable of using 6 faders and 6 extra knobs for pan. There are also 2 buttons for switching channels and an extra button for play/pause.

All pots and buttons are connected to HC4067
The project uses free rtos to separate all tasks.

Task 1
 Reading the pot inputs into the channel instances and adding them to the midi packet queue
Task 2
  Reading the pins to adjust midi channel
Task 3
  Reading the packets from the queue and sending via usb
