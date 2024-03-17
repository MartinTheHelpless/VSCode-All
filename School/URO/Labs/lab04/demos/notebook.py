import tkinter as tk
from tkinter import ttk

root = tk.Tk()

notebook = ttk.Notebook(root)
notebook.pack()

frame1 = ttk.Frame(notebook, width=400, height=280)
frame2 = ttk.Frame(notebook, width=400, height=280)

notebook.add(frame1, text='Page 1')
notebook.add(frame2, text='Page 2')

root.mainloop()