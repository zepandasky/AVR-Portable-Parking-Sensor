from machine import UART, Pin, Timer, PWM
import time

buzzer = PWM(Pin(2))
uart0 = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))

#This timer sets pitch height of the buzzer
tim = Timer()
tim2 = Timer()
x = True
y = -1
def switcher(timer):
    global x
    if(x == True):
        print("here1")
        buzzer.freq(2000)
        buzzer.duty_u16(30000)
        x = False
    else:
        print("here")
        buzzer.deinit()
        x = True

def beep_sound(distance : int):
    global y
    print(distance)
    if(distance < 10) :
        if(y != 0):
            tim2.init(freq=50, mode=Timer.PERIODIC, callback=switcher)
            y = 0
    if(distance > 10 and distance < 25) :
        if(y != 1):
            tim2.init(freq=15, mode=Timer.PERIODIC, callback=switcher)
            y = 1
    if(distance > 25 and distance < 40) :
        if(y != 2):
            tim2.init(freq=5, mode=Timer.PERIODIC, callback=switcher)
            y = 2
    if(distance > 40 ) :
        if(y != 3):
            tim2.init(freq=1, mode=Timer.PERIODIC, callback=switcher)
            y = 3

def read_uart():
    rxData = bytes()
    while uart0.any() > 0:
        rxData = uart0.read()
        return rxData
    return None

# tim.init(freq=4500, mode=Timer.PERIODIC, callback=tick)
# tim2.init(freq=2, mode=Timer.PERIODIC, callback=switcher)

while(1):
    uart_val = read_uart()
    if(uart_val is not None):
        distance = uart_val.decode('utf-8')
        distance = int(distance)
        beep_sound(distance)
