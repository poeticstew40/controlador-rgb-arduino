import serial
import tkinter as tk
from tkinter import colorchooser
from tkinter import messagebox

# Configuración del puerto serial
try:
    arduino = serial.Serial('COM5', 9600, timeout=1)
except:
    messagebox.showerror("Error", "No se pudo conectar al Arduino. Verifica el puerto COM.")
    exit()

def send_color():
    color_code = colorchooser.askcolor(title="Elige un color")[0]
    if color_code:
        r, g, b = map(int, color_code)
        command = f"COLOR:{r:03},{g:03},{b:03}\n"
        arduino.write(command.encode())

def send_effect(effect):
    command = f"EFFECT:{effect}\n"
    arduino.write(command.encode())

root = tk.Tk()
root.title("Control de Luces RGB")
root.geometry("300x200")

tk.Label(root, text="Control de Luces RGB").pack(pady=10)

tk.Button(root, text="Cambiar Color", command=send_color).pack(pady=10)
tk.Button(root, text="Efecto 1", command=lambda: send_effect(1)).pack(pady=10)
tk.Button(root, text="Efecto 2", command=lambda: send_effect(2)).pack(pady=10)

root.mainloop()
