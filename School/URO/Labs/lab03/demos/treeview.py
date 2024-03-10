import tkinter as tk
from tkinter import ttk

root = tk.Tk()

tree = ttk.Treeview(root, columns=('first_name', 'last_name', 'birth_number'), 
                    show='headings')

tree.heading('first_name', text='First Name')
tree.heading('last_name', text='Last Name')
tree.heading('birth_number', text='Birth Number')

tree.insert('', tk.END, values=("John", "Roe", "045216/1512"))
tree.insert('', tk.END, values=("Jane", "Doe", "901121/7238"))

tree.grid(row=0, column=0, sticky='nsew')

scrollbar = ttk.Scrollbar(root, orient=tk.VERTICAL, command=tree.yview)
tree.configure(yscroll=scrollbar.set)
scrollbar.grid(row=0, column=1, sticky='ns')

root.mainloop()