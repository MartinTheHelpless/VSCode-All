import tkinter as tk
from tkinter import ttk

class LeftFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master, style="Red.TFrame")
        self.pack(side="left", fill="y")

        self.subframe = ttk.Frame(self, style="Centered.TFrame")
        self.subframe.pack(expand=True, fill='both')

        padding = 10
        self.subframe.grid_rowconfigure(0, weight=1)
        self.subframe.grid_columnconfigure(0, weight=1)

        for i in range(6):
            ttk.Button(self.subframe, text=f"Button {i+1}").pack(fill="both", padx=padding, pady=padding)

class TopRightFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master, style="Green.TFrame")
        self.pack(side="top", fill="both", expand=True)
 
        self.search_label = ttk.Label(self, text="Search:")
        self.search_label.pack(side="left", padx=5, pady=5)
        self.search_entry = ttk.Entry(self)
        self.search_entry.pack(side="left", fill="x", expand=True, padx=5, pady=5)
 
        self.another_widget = ttk.Button(self, text="Another Widget")
        self.another_widget.pack(side="right", padx=5, pady=5)
 
        self.search_entry.bind("<Return>", self.search)

    def search(self, event=None): 
        search_query = self.search_entry.get().lower()
 

class BottomRightFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master, style="Blue.TFrame")
        self.pack(side="top", fill="both", expand=True)
 
        padding = 10
        self.treeview = ttk.Treeview(self, columns=("Column 1", "Column 2", "Column 3", "Column 4"), show="headings")
        self.treeview.pack(expand=True, fill="both", padx=padding, pady=padding)
 
        self.treeview.heading("Column 1", text="Column 1")
        self.treeview.heading("Column 2", text="Column 2")
        self.treeview.heading("Column 3", text="Column 3")
        self.treeview.heading("Column 4", text="Column 4")
 
        column_widths = (100, 100, 100, 100)  
        for i, width in enumerate(column_widths):
            self.treeview.column(i, width=width)

def main():
    root = tk.Tk() 
    root.geometry("600x280") 

    root.style = ttk.Style()
    root.style.configure("Red.TFrame", background="red")
    root.style.configure("Green.TFrame", background="green")
    root.style.configure("Blue.TFrame", background="blue")
    root.style.configure("Centered.TFrame", background="white")

    left_frame = LeftFrame(root)
    top_right_frame = TopRightFrame(root)
    bottom_right_frame = BottomRightFrame(root)

    left_frame.pack(side="left", fill="y")
    top_right_frame.pack(fill="x")
    bottom_right_frame.pack(fill="both", expand=True)   

    root.mainloop()

if __name__ == "__main__":
    main()
