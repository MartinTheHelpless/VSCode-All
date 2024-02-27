# -*- coding: utf-8 -*-

from tkinter import *
from math import sqrt
import tkinter.font

class myApp:

    def prevod(self, event=None): 
        print("prevod");
        v = float(self.entry.get())
        print(self.entry.get())
        self.res.delete(0, END)
        self.res.insert(0, str(round(v, 2)))

    def __init__(self, root):

        root.title('Převodník teplot')
        root.resizable(False, False) 

        def_font = tkinter.font.nametofont("TkDefaultFont")
        def_font.config(size=16)

        left_frame = LabelFrame(root)
        right_frame = LabelFrame(root, text="right") 
        dir_frame = LabelFrame(left_frame, text="Direction")
        conv_frame = LabelFrame(left_frame, text="Conversion")
        left_frame.pack(side=LEFT, fill=BOTH)
        right_frame.pack(side=RIGHT, fill=BOTH)
  
        dir_frame.pack(fill=BOTH);
        conv_frame.pack(fill=BOTH);
 
        self.var = IntVar()
        self.result = 0

        convButt = Button(left_frame, text="Convert", command=self.prevod);
        convButt.pack(side=BOTTOM, fill=X);

        self.entry = Entry(conv_frame, textvariable=getint);
        self.entry.pack(side=TOP, fill=BOTH);
        self.entry.insert(0, '0');

        self.res = Entry(conv_frame, text=self.result);
        self.res.pack(side=BOTTOM, fill=X ); 

        rbtn0 = Radiobutton(dir_frame, value=1, variable=self.var);
        labA = Label(dir_frame, text="F -> C");
        rbtn1 = Radiobutton(dir_frame, value=0, variable=self.var);
        labB = Label(dir_frame, text="C -> F");
        rbtn1.pack(side=LEFT);
        labB.pack(side=LEFT);
        labA.pack(side=RIGHT);
        rbtn0.pack(side=RIGHT);

 
root = Tk()
root.geometry("500x500") 
app = myApp(root)
root.mainloop()

