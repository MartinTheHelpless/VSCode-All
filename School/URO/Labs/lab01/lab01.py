from tkinter import *
from tkinter import ttk
import tkinter as tk

class myApp01:
  def __init__(self, master):
    self.bu1 = ttk.Button(master, text="TOP", style="TButton", command=master.quit)
    self.bu2 = ttk.Button(master, text="MID_TOP", style="TButton", command=master.quit)
    self.bu3 = ttk.Button(master, text="MID_BOTTOM", style="TButton", command=master.quit)
    self.bu4 = ttk.Button(master, text="BOTTOM", style="TButton", command=master.quit)
    self.bu1.pack(); 
    self.bu2.pack(); 
    self.bu3.pack();
    self.bu4.pack();


class myApp02:
  def __init__(self, master):
    self.bu1 = ttk.Button(master, text="LEFT", style="TButton", command=master.quit)
    self.bu2 = ttk.Button(master, text="RIGHT", style="TButton", command=master.quit)
    self.bu3 = ttk.Button(master, text="TOP", style="TButton", command=master.quit)
    self.bu4 = ttk.Button(master, text="BOTTOM", style="TButton", command=master.quit)
    self.bu1.pack(side = LEFT); 
    self.bu2.pack(side = RIGHT); 
    self.bu3.pack(side = TOP);
    self.bu4.pack(side = BOTTOM, fill = BOTH);


class myApp03:
  def __init__(self, master):
    self.bu1 = ttk.Button(master, text="LEFT", style="TButton", command=master.quit)
    self.bu2 = ttk.Button(master, text="RIGHT", style="TButton", command=master.quit)
    self.bu3 = ttk.Button(master, text="BOTTOM", style="TButton", command=master.quit)
    self.bu4 = ttk.Button(master, text="BOTTOM", style="TButton", command=master.quit)
    self.bu3.pack(side = BOTTOM);
    self.bu4.pack(side = BOTTOM);
    self.bu1.pack(side = LEFT); 
    self.bu2.pack(side = RIGHT); 

root = Tk()
root.geometry("110x110")
app = myApp02(root)
root.mainloop()