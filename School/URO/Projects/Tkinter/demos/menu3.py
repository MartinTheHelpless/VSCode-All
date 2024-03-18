import tkinter as tk
from tkinter import ttk

root = tk.Tk()

menu = tk.Menu(root, tearoff=0)
menu.add_command(label="Back", command=root.quit)
menu.add_command(label="Quit", command=root.quit)

frame = tk.Frame(root, width=300, height=200)
frame.pack()

def popup(event):
    menu.post(event.x_root, event.y_root)

frame.bind("<Button-3>", popup)

root.mainloop()