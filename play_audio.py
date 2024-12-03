import serial
import time
import subprocess
import re
import os


SERIAL_PORT = "/dev/tty.usbmodem12301"
BAUD_RATE = 9600


AUDIO_DIR = "audio"


def play_audio(year):

    audio_file = os.path.join(AUDIO_DIR, f"{year}.mp3")

    if os.path.isfile(audio_file):
        print(f"Reproduciendo archivo: {audio_file}")
        subprocess.call(["afplay", audio_file])
    else:
        print(f"Archivo de audio para el año {year} no encontrado.")


def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Conectado al puerto {SERIAL_PORT}")
        time.sleep(2)
    except serial.SerialException:
        print(f"No se puede abrir el puerto {SERIAL_PORT}")
        return

    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode("utf-8").strip()
                print(f"Recibido: {line}")

                match = re.match(r"PLAY_AUDIO_(\d{4})", line)
                if match:
                    year = match.group(1)
                    play_audio(year)
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("Programa terminado por el usuario.")
    finally:
        ser.close()


if __name__ == "__main__":
    main()
