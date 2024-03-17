import tkinter as tk
from tkinter import ttk

root = tk.Tk()

menubar = tk.Menu(root)
filemenu = tk.Menu(menubar, tearoff=0)
filemenu.add_command(label="Konec", command=root.quit)
menubar.add_cascade(label="Soubor", menu=filemenu)

root.config(menu=menubar)

root.mainloop()