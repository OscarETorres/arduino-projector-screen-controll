arduino-projector-screen-controll

controller to roll a projector screen up and down<br>
Materials<br>
 1 Arduino uno<br>
 2 arduino relay modules with optocoupler low level trigger<br>
 2 hall effect switches<br>
 2 small magnets<br>
 1 ir sender diode 850-940nm<br>
 1 ir receiver module standard 38khz<br> 
 1 motor with reversible direction AC 220v 68KTYZ 80rpm<br>
 
*use cases*

first switch on

pre-condition
screen is up
projector is off
other equipment is off

actions
press onoff in control remote

results
screens rolls down
projector is switch on
additional equipment is switch on
screen stops roll when it reaches bottom

switch off
pre-condition
screen is down
projector is on
other equipment is on

actions
press onoff in control remote

results
screens rolls up
projector is switch off
additional equipment is switch off
screen stops roll when it reaches top

pull screen down
pre-condition
screen is up
projector is on/off
other equipment is on/off

actions
press arrow down in control remote

results
screens rolls down
projector is unchanged
additional equipment is unchanged
screen stops roll when it reaches bottom

pull screen up
pre-condition
screen is down
projector is on/off
other equipment is on/off

actions
press arrow up in control remote

results
screens rolls up
projector is unchanged
additional equipment is unchanged
screen stops roll when it reaches top

change screen direction while rolling up/down
pre-condition
screen is travelling up/down
projector is on/off
other equipment is on/off

actions
press arrow down or up in control remote

results
screen rolling stops
screens rolls in the pressed direction
projector is unchanged
additional equipment is unchanged
screen stops roll when it reaches top/bottom



