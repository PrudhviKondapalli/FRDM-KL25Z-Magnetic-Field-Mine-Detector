# ECEN-5813_Principles-of-Embedded-Software_Final-Project
# Project Proposal: Magnetic Field Mine Detector
# Project Overview:
The Magnetic Field Mine Detector project aims to design and develop a mine detection system using the GY-271 QMC5883L magnetometer and the FRDM-KL25Z microcontroller. The system will detect changes in the magnetic field strength and provide visual and auditory feedback to indicate the presence of magnetic objects, simulating a mine detection scenario.
# Functionality:
The project will:
1. Utilize the GY-271 QMC5883L magnetometer to measure magnetic field strength.
2. Adjust the colour of an RGB LED based on the detected magnetic field strength.
3. Modulate the PWM signal to a speaker or buzzer to generate varying sound levels corresponding to magnetic field strength.
4. Simulate a mine detection system, where the presence of magnetic objects is indicated by the LED colour and sound level.
# Technologies:
The project will involve the following technologies:
1. GY-271 QMC5883L magnetometer module: It will measure magnetic field strength.
2. RGB LED & Speaker or buzzer: Controlled using PWM to change colours.
3. I2C communication protocol for reading magnetic field data from the GY-271.
4. GPIO pins for controlling the LED and speaker.
# Learning Goals:
To demonstrate deeper knowledge, we will:
1. Implement advanced PWM control to smoothly transition the LED colour and speaker loudness 
based on magnetic field strength.
2. Develop efficient sensor data and sensor calibration for real-time mine detection.
3. Apply principles of interactive design to engage users through visual and auditory feedback.
# Anticipate the need to:
1. Study and understand the GY-271 QMC5883L sensor datasheet for accurate magnetic field 
measurements.
2. Investigate advanced PWM control techniques for smooth LED colour transitions and speaker 
volume modulation.
