import tkinter as tk
from tkinter import ttk
from tkinter import *

root = tk.Tk()

menubar = tk.Menu(root)
menuOne = tk.Menu(menubar, tearoff=0)
menuTwo = tk.Menu(menubar, tearoff=0)
menuThree = tk.Menu(menubar, tearoff=0)
menubar.add_cascade(label="Soubor", menu=menuOne)
menubar.add_cascade(label="Nastavení", menu=menuTwo)
menubar.add_cascade(label="Nápověda", menu=menuThree)
menuOne.add_command(label="Konec", command=root.quit)
menuTwo.add_command(label="Whatever", command=root.quit)
menuThree.add_command(label="Something", command=root.quit)

tree = ttk.Treeview(root, columns=('first_name', 'last_name', 'birth_number'), 
                    show='headings')

tree.heading('last_name', text='Last Name')
tree.heading('first_name', text='First Name')
tree.heading('birth_number', text='Birth Number')

tree.insert('', tk.END, values=("John", "Roe", "045216/1512"))
tree.insert('', tk.END, values=("Jane", "Doe", "901121/7238"))

tree.grid(row=0, column=0, sticky='nsew')

scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscroll=scrollbar.set)
scrollbar.grid(row=0, column=1, sticky='ns')


formFrame = Frame(root, width=610, height=110)
notebookFrame = LabelFrame(root, width=620, height=100)

buttonFrame = LabelFrame(root, width=620, height=100)

cancel = Button(buttonFrame , text="Cancel", padx=5);
new = Button(buttonFrame , text="New record", padx=5);
save = Button(buttonFrame , text="Save record", padx=5);

new.pack(side=RIGHT);
save.pack(side=RIGHT);
cancel.pack(side=RIGHT);


name = Label(formFrame, text="Name: ");
surname = Label(formFrame, text="Surname: ");
persNum = Label(formFrame, text="Pers. Num.: ");

txt01 = Entry(formFrame);
txt02 = Entry(formFrame);
txt03 = Entry(formFrame);

name.grid(row=0, column=0); 
txt01.grid(row=0, column=1);

surname.grid(row=1, column=0);
txt02.grid(row=1, column=1);

persNum.grid(row=2, column=0);
txt03.grid(row=2, column=1);

formFrame.grid(row=1,column=0);
notebookFrame.grid(row=2, column=0);
buttonFrame.grid(row=3, column=0);

notebook = ttk.Notebook(notebookFrame)
notebook.pack()

frame1 = ttk.Frame(notebook, width=620, height=100)
frame2 = ttk.Frame(notebook, width=620, height=100)


city = Label(frame1, text="City: ");
street = Label(frame1, text="Street: ");
postNum = Label(frame1, text="Post. Num.: ");

capsule = Frame(frame1);

frame2Entry = Text(frame2, height=8,width=77);

frame2Entry.pack();

txt01 = Entry(capsule, width=9);
txt02 = Entry(frame1);
txt03 = Entry(frame1);
txt04 = Entry(capsule, width=5 );

padding = Frame(frame1);

hNum = Label(capsule, text="H.n.:");
padding.grid(column=0, row=0, padx=105);

street.grid(row=0, column=1); 
txt01.pack(side=LEFT );

hNum.pack(side=LEFT); 
txt04.pack(side=RIGHT );

city.grid(row=1, column=1);
txt02.grid(row=1, column=2, columnspan=3);

postNum.grid(row=2, column=1);
txt03.grid(row=2, column=2); 

capsule.grid(row=0, column=2);

notebook.add(frame1, text='Adresa')
notebook.add(frame2, text='Poznámka')
 

root.config(menu=menubar) 
root.geometry("630x500") 
root.mainloop()