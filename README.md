# arduino-projector-screen-controll

controller to roll a projector screen up and down<br>
## Materials<br>
 1 Arduino uno<br>
 2 arduino relay modules with optocoupler low level trigger<br>
 2 hall effect switches<br>
 2 small magnets<br>
 1 ir sender diode 850-940nm<br>
 1 ir receiver module standard 38khz<br> 
 1 motor with reversible direction AC 220v 68KTYZ 80rpm<br>
 
 connect relay 1 to pin 4<br>
 connect relay 2 to pin 7<br>
 connect motor to relays<br>
 
 connect IRReceiver to pin 8<br>
 connect IRSender 1 to pin 6 (use 2n2222 to interface)<br>
 
 connect hall sensor 1 to pin 2<br>
 connect hall sensor 2 to pin 3<br>
 magnet 1 on screen top and <br>
 magnet 2 on screen bottom<br>
 
 # **use cases**<br>

## first switch on<br>

### pre-condition<br>
screen is up<br>
projector is off<br>
other equipment is off<br>

### actions<br>
press onoff in control remote<br>

### results<br>
screens rolls down<br>
projector is switch on<br>
additional equipment is switch on<br>
screen stops roll when it reaches bottom<br>

## switch off<br>
### pre-condition<br>
screen is down<br>
projector is on<br>
other equipment is on<br>

### actions<br>
press onoff in control remote<br>

### results<br>
screens rolls up<br>
projector is switch off<br>
additional equipment is switch off<br>
screen stops roll when it reaches top<br>

## pull screen down<br>
### pre-condition<br>
screen is up<br>
projector is on/off<br>
other equipment is on/off<br>

### actions<br>
press arrow down in control remote<br>

### results<br>
screens rolls down<br>
projector is unchanged<br>
additional equipment is unchanged<br>
screen stops roll when it reaches bottom<br>

## pull screen up<br>
### pre-condition<br>
screen is down<br>
projector is on/off<br>
other equipment is on/off<br>

### actions<br>
press arrow up in control remote<br>

### results<br>
screens rolls up<br>
projector is unchanged<br>
additional equipment is unchanged<br>
screen stops roll when it reaches top<br>

## change screen direction while rolling up/down<br>
### pre-condition<br>
screen is travelling up/down<br>
projector is on/off<br>
other equipment is on/off<br>

### actions<br>
press arrow down or up in control remote<br>

### results<br>
screen rolling stops<br>
screens rolls in the pressed direction<br>
projector is unchanged<br>
additional equipment is unchanged<br>
screen stops roll when it reaches top/bottom<br>


## Stop screen rolling up/down<br>
### pre-condition<br>
screen is travelling up/down<br>
projector is on/off<br>
other equipment is on/off<br>

### actions<br>
press stop in control remote<br>

### results<br>
screen rolling stops immediatly<br>
projector is unchanged<br>
additional equipment is unchanged<br>


## Repeat IR signals<br>
### pre-condition<br>
screen is up/down<br>
projector is on/off<br>
other equipment is on/off<br>

### actions<br>
press any other key in current/different control remote<br>

### results<br>
screen rolling unchanged<br>
ir signals from remote are re-send by arduino to corresponding projector/equipment<br>
except for UP,DOWN and STOP<br>
