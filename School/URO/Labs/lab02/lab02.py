# -*- coding: utf-8 -*-

from tkinter import *
from math import sqrt
import tkinter.font

class myApp:

    def prevod(self, event=None):  
        self.ca.delete(self.rectangle);
        if(self.var.get() == 1): 
            self.res.delete(0, END)
            self.result = round(float(self.entry.get()) * 1.8 + 32, 2) 
            self.res.insert(0, str(self.result)) 
            print(self.result);
            print(int(self.entry.get()));
            self.rectangle = self.ca.create_rectangle(151, 328, 148, 231 - int(self.entry.get()) * 3, fill='black');
        elif(self.var.get() == 0): 
            self.result = round((float(self.entry.get()) - 32) * 5 / 9, 2)
            self.res.delete(0, END)
            self.res.insert(0, str(self.result))
            print(self.result);
            print(int(self.entry.get()));
            self.rectangle = self.ca.create_rectangle(151, 328, 148, 231 - self.result * 3, fill='black');
         
    def __init__(self, root):

        root.title('Převodník teplot')
        root.resizable(False, False) 
        root.bind('<Return>', self.prevod) 

        def_font = tkinter.font.nametofont("TkDefaultFont")
        def_font.config(size=16)

        self.right_frame = LabelFrame(root, text="right") 

        self.ca = Canvas(self.right_frame, width=300, height=400)
        self.photo = PhotoImage(file="/home/buri/Documents/Programming/VSCode/VSCode-All/School/URO/Labs/lab02/th_emtpy.png")
        self.ca.create_image(150, 200, image=self.photo)
        self.ca.pack();


        left_frame = LabelFrame(root)
        dir_frame = LabelFrame(left_frame, text="Direction")
        conv_frame = LabelFrame(left_frame, text="Conversion")
        left_frame.pack(side=LEFT, fill=BOTH)
        self.right_frame.pack(side=RIGHT, fill=BOTH)
  
        dir_frame.pack(fill=BOTH);
        conv_frame.pack(fill=BOTH);
 
        self.var = IntVar() 
        self.result = IntVar()
        self.rectangle = self.ca.create_rectangle(151, 328, 148, 231, fill='black');

        convButt = Button(left_frame, text="Convert", command=self.prevod);
        convButt.pack(side=BOTTOM, fill=X);

        self.input = Label(conv_frame, text="Input");
        self.output = Label(conv_frame, text="Output");

        self.input.pack(side=TOP);

        self.entry = Entry(conv_frame, textvariable=getint);
        self.entry.pack(side=TOP, fill=BOTH);
        self.entry.insert(0, '0');

        self.output.pack(side=TOP);

        self.res = Entry(conv_frame, text=self.result);
        self.res.pack(side=BOTTOM, fill=X ); 
        
        rbtn1 = Radiobutton(dir_frame, value=0, variable=self.var);
        labB = Label(dir_frame, text="F -> C");
        rbtn0 = Radiobutton(dir_frame, value=1, variable=self.var);
        labA = Label(dir_frame, text="C -> F");
        rbtn1.pack(side=LEFT);
        labB.pack(side=LEFT);
        labA.pack(side=RIGHT);
        rbtn0.pack(side=RIGHT);

 
root = Tk()
root.geometry("500x500") 
app = myApp(root)
root.mainloop()

