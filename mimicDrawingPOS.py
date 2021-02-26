'''
Tufts University, Spring 2021
mimicDrawing.py
By: Sawyer Bailey Paccione and Joshua Fitzgerald
Completed:      February 21st, 2021, 9:09 PM
Description:    Reads the current position and angles into arrays, 
                to be played back later. Due to SPIKE Primes limited
                IDE, this code has to be run in REPL which is why 
                there are global variables and it is not modular.
'''
################################################################################
#                                   Imports                                    #
################################################################################
import hub
import utime

################################################################################
#                              Initialize  Values                              #
################################################################################

# Initialize Spike Prime Motor Connections
left_motor      = hub.port.F.motor
right_motor     = hub.port.E.motor

# Initialize Position and Angle Lists
left_pos  = [0]
right_pos = [0]

left_angle = [0]
right_angle = [0]

WAIT_TIME = 20 # milliseconds

# Set Initial Positions of Motors (To be Returned to)
desired1 = right_motor.get()[1]
desired2 = left_motor.get()[1]

# Initialize the connection the WIO on the Port
wio = hub.port.A
wio.mode(hub.port.MODE_FULL_DUPLEX)
wio.baud(9600)

################################################################################
#                          Read In Positions and Angles                        #
################################################################################
while True : 
    # Collect Current Position of Motors
    curr_leftpos  = left_motor.get()[1]
    curr_rightpos = right_motor.get()[1]

    # Store Positions in List
    left_pos.append(curr_leftpos)
    right_pos.append(curr_rightpos)

    # Collect Current Angles of Motors 
    curr_leftang  = left_motor.get()[2]
    curr_rightang = right_motor.get()[2]

    # Store Angles in List
    left_angle.append(curr_leftang)
    right_angle.append(curr_rightang)
    utime.sleep_ms(WAIT_TIME)


################################################################################
#                          Return to Original Position                         #
################################################################################
# Proportional Controller
error1 = 10 # Threshold Values
error2 = 10
Kp = 2      # Proportional Component
while (True):    
    # Motor 1
    current1 = right_motor.get()[1]
    error1 = desired1 - current1
    speed1 = Kp * error1  # Speed is proportional to the error
    speed1 = min(speed1, 100) # Set Upper Bound on Speed of 100
    speed1 = max(speed1,-100) # Set Lower Bound on Speed of -100 
    right_motor.pwm(int(speed1)) # Set Speed Using Pulse-Width Modulation

    # Motor 2 (Repeat Steps Above)
    current2 = left_motor.get()[1]
    error2 = desired2 - current2
    speed2 = Kp * error2
    speed2 = min(speed2, 100)
    speed2 = max(speed2,-100)
    left_motor.pwm(int(speed2))

    utime.sleep_ms(WAIT_TIME)

    # Wait for Keyboard Interrupt to Exit While Loop

# Stop Motors
left_motor.pwm(0)
right_motor.pwm(0)

utime.sleep_ms(500)

################################################################################
#                             Rerun the Positions                              #
################################################################################

# Loop through the position and angle lists, rerunning/sending them at the same 
#    Speed
for i in range(len(left_pos)): 

    left_motor.run_to_position(left_pos[i], 60)
    right_motor.run_to_position(right_pos[i], 60)
    
    # Send Information to WIO to be Parsed
    wio.write('L' + str(-left_angle[i]) + 'R' + str(-right_angle[i]) + '\n')
    
    utime.sleep_ms(WAIT_TIME)

# Reset Motors to Zero
left_motor.pwm(0)
right_motor.pwm(0)