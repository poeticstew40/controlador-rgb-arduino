import serial
import customtkinter as ctk
from tkinter import colorchooser

# Configuración del puerto serial
try:
    arduino = serial.Serial('COM5', 9600, timeout=1)
except:
    print("Error: No se pudo conectar al Arduino en COM5")
    exit()

# Funciones
def choose_color():
    color_code = colorchooser.askcolor(title="Selecciona un color")[0]  # Devuelve (R, G, B)
    if color_code:
        r, g, b = map(int, color_code)
        command = f"COLOR:{r:03},{g:03},{b:03}\n"
        arduino.write(command.encode())

def activate_rainbow():
    arduino.write(b"RAINBOW\n")

def toggle_lights():
    arduino.write(b"TOGGLE\n")

# Interfaz gráfica
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

root = ctk.CTk()
root.title("Control de Luces RGB")
root.geometry("400x300")

# Botones
ctk.CTkButton(root, text="Elegir Color", command=choose_color).pack(pady=10)
ctk.CTkButton(root, text="Efecto Rainbow", command=activate_rainbow).pack(pady=10)
ctk.CTkButton(root, text="Encender/Apagar", command=toggle_lights).pack(pady=10)

# Inicia la ventana principal
root.mainloop()
