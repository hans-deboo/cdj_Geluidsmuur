import serial
import pygame

# Initialize serial connection
ser = serial.Serial('/dev/ttyUSB0', 9600)

# Initialize pygame mixer
pygame.mixer.init()

# Define sound files for each value
sound_files = {
    '1': './sound1.mp3',
    '2': './sound2.mp3',
    '3': './sound3.mp3'
}

# Read and process serial data indefinitely
while True:
    # Read a line of data from the serial port
    data = ser.readline().strip().decode('utf-8')
    
    # Check if the data is within the desired range (1 to 3)
    if data in sound_files:
        # Load and play the corresponding sound file
        sound_file = sound_files[data]
        pygame.mixer.music.load(sound_file)
        pygame.mixer.music.play()
        print(f"Playing {sound_file}")
        print(f"Data received {data}")

