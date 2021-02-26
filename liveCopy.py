'''
Tufts University, Spring 2021
mimicDrawing.py
By: Sawyer Bailey Paccione and Joshua Fitzgerald
Completed:      February 21st, 2021, 9:09 PM
Description:    Live Copies the robotic arms angles and positions onto the WIO
'''
################################################################################
#                                   Imports                                    #
################################################################################
import hub
import utime

################################################################################
#                              Initialize  Values                              #
################################################################################

left_motor      = hub.port.F.motor
right_motor     = hub.port.E.motor

left_pos  = [0]
right_pos = [0]

left_angle = [0]
right_angle = [0]

WAIT_TIME = 20 # milliseconds

desired1 = right_motor.get()[1]
desired2 = left_motor.get()[1]

# Initialize the connection the WIO on the Port
wio = hub.port.A
wio.mode(hub.port.MODE_FULL_DUPLEX)
wio.baud(9600)

################################################################################
#                          Read In Velocity and Angles                         #
################################################################################
while True : 
    curr_leftang  = left_motor.get()[2]
    curr_rightang = right_motor.get()[2]
    wio.write('L' + str(-curr_leftang) + 'R' + str(-curr_rightang) + '\n')
    utime.sleep_ms(WAIT_TIME)

    