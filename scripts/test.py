import serial
import time

# Find your Pico's serial port (e.g., /dev/ttyACM0 on Linux, COM3 on Windows)
ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1)
time.sleep(2)  # Wait for connection


def send_key(char):
    ser.write(char.encode())
    response = ser.readline().decode().strip()
    print(f"Response: {response}")


# Example usage
send_key("f")
send_key("h")
send_key("e")
send_key("l")
send_key("l")
send_key("o")
