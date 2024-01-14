# Xnergy Firmware Challenge
GPIO Module Design
Task Assumptions
* Button 1 pressed for 1sec - GREEN LED is ON and Blinking for 1sec 
* Button 2 pressed for 5sec - RED LED is ON continously 

test_app.c 
---handles button1 task after button release from pressing
---handles button2 task after button release from pressing

button.c 
---handles GPIO initial setting
---GPIO edge level interrupt
---GPIO reading debouce
---button state if pressed or released

led.c
--- handles GPIO initial setting
--- GPIO setting to ON and OFF
--- cyclic timer for blinking

Dummy functions and header to compile error
timer.c
timer.h
gpio.c
gpio.h
sys_type.h
