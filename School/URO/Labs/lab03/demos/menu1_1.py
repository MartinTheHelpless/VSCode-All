import tkinter as tk
from tkinter import ttk

root = tk.Tk()

menuList = tk.Menu(root)
menuList.add_command(label="Ahoj!", command=root.destroy)
menuList.add_command(label="Pryč!", command=root.destroy)

root.config(menu=menuList)
root.mainloop()
