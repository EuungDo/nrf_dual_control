import time
import serial
import threading

# 송신용 아두이노 시리얼 포트 설정
ser_tx = serial.Serial(
    port='/dev/ttyACM0',  # 적절한 포트로 변경
    baudrate=115200,
    timeout=1
)

# 수신용 아두이노 시리얼 포트 설정
ser_rx = serial.Serial(
    port='/dev/ttyACM1',  # 적절한 포트로 변경
    baudrate=115200,
    timeout=1
)

def send_to_arduino():
    while True:
        message = input("Enter a number to send to Arduino: ")
        if ser_tx.is_open:
            ser_tx.write((message + '\n').encode('utf-8'))
            print(f"Message '{message}' sent to Arduino on port {ser_tx.port}\n")
        time.sleep(1)

def read_from_arduino():
    while True:
        if ser_rx.is_open and ser_rx.in_waiting > 0:
            incoming_message = ser_rx.readline().decode('utf-8').strip()
            if incoming_message:
                print(f"Received from Arduino on port {ser_rx.port}: {incoming_message}\n")
            time.sleep(1)

def main():
    send_thread = threading.Thread(target=send_to_arduino)
    receive_thread = threading.Thread(target=read_from_arduino)
    
    send_thread.start()
    receive_thread.start()

    send_thread.join()
    receive_thread.join()
    
if __name__ == "__main__":
    try:
        if ser_tx.is_open and ser_rx.is_open:
            print(f"Serial ports {ser_tx.port} and {ser_rx.port} opened successfully.")
            main()

    except Exception as e:
        print(f"An unexpected error occurred: {e}")