import RPi.GPIO as GPIO
import datetime
import time


GPIO.setmode(GPIO.BCM)  # choose BCM or BOARD numbering schemes. I use BCM
GPIO.setup(25, GPIO.OUT)# set GPIO 25 as an output. You can use any GPIO port
p = GPIO.PWM(25, 50)    # create an object p for PWM on port 25 at 50 Hertz
p.start(70)             # start the PWM on 70 percent duty cycle

print("it works!!!")

for x in range (200,1000):
    p.ChangeFrequency(500)  # change the frequency to x Hz (
    time.sleep(0.0001)
p.stop() 
time.sleep(0.06)
p.start(70)

for x in range (200,1000):
    p.ChangeFrequency(500)  # change the frequency to x Hz (
    time.sleep(0.0001)
p.stop() 
time.sleep(0.06)
p.start(70)

for x in range (200,1000):
    p.ChangeFrequency(500)  # change the frequency to x Hz (
    time.sleep(0.0001)

p.stop()                # stop the PWM output
GPIO.cleanup()          # when your program exits, tidy up after yourself