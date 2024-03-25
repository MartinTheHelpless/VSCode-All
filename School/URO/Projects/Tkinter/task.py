import tkinter as tk
from tkinter import ttk
from ttkthemes import ThemedTk
 
records = [
    ("Martin", "Burian", "Koleje VSB", "FEI"),
    ("Radovan", "Rečka", "Top of the Foodchain", "FEI"),
    ("Petr", "Slavoj", "POREB450", "FEI"),
    ("Bob", "Brown", "POREB211", "FEI"),
    ("Charlie", "Davis", "POREB381", "FEI"),   
    ("John", "Smith", "POREB123", "FEI"),
    ("Alice", "Johnson", "POREB222", "FIT"),
    ("David", "Lee", "POREB333", "FS"),
    ("Emily", "White", "POREB444", "FBI"),
    ("Michael", "Clark", "POREB555", "FSI"),
    ("Jennifer", "Martinez", "POREB666", "FG"),
    ("William", "Taylor", "POREB777", "FEI"),
    ("Jessica", "Anderson", "POREB888", "FIT"),
    ("Christopher", "Wilson", "POREB999", "FS"),
    ("Amanda", "Thomas", "POREB111", "FBI"),
    ("Matthew", "Harris", "POREB222", "FSI"),
    ("Elizabeth", "Martin", "POREB333", "FG"),
    ("Daniel", "Garcia", "POREB444", "FEI"),
    ("Sarah", "Rodriguez", "POREB555", "FIT"),
    ("Ryan", "Lopez", "POREB666", "FS"),
    ("Lauren", "Perez", "POREB777", "FBI"),
    ("Kevin", "Sanchez", "POREB888", "FSI"),
    ("Ashley", "Ramirez", "POREB999", "FG"),
    ("Nicholas", "Torres", "POREB111", "FEI"),
    ("Megan", "Flores", "POREB222", "FIT")
]

class LeftFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack(side="left", fill="y")

        self.subframe = ttk.Frame(self)
        self.subframe.pack(expand=True, fill='both')

        padding = 10
        self.subframe.grid_rowconfigure(0, weight=1)
        self.subframe.grid_columnconfigure(0, weight=1)

        ttk.Button(self.subframe, text=f"Student Info", command=self.show_text_popup).pack(fill="both", padx=padding, pady=padding)
        ttk.Button(self.subframe, text=f"Add Record", command=self.show_treeview_popup).pack(fill="both", padx=padding, pady=padding)
        ttk.Button(self.subframe, text=f"Remove Record", command=self.delete_selected_record).pack(fill="both", padx=padding, pady=padding)
        ttk.Button(self.subframe, text=f"Filter by Name", command=lambda: master.top_right_frame.set_filter_column(0)).pack(fill="both", padx=padding, pady=padding)
        ttk.Button(self.subframe, text=f"Filter by Surname", command=lambda: master.top_right_frame.set_filter_column(1)).pack(fill="both", padx=padding, pady=padding)
        ttk.Button(self.subframe, text=f"Filter by Faculty", command=lambda: master.top_right_frame.set_filter_column(3)).pack(fill="both", padx=padding, pady=padding)
           
    def show_text_popup(self):
        popup = tk.Toplevel(self)
        popup.title("Text Popup")
        text = "Martin Burian - BUR0266\nProjekt Tkinter Python\nAspoň 12 bodů bych ocenil pls xd."
        label = ttk.Label(popup, text=text)
        label.pack(padx=10, pady=10)

    def show_treeview_popup(self):
        popup = tk.Toplevel(self)
        popup.title("Treeview Popup")

        entry_labels = ["Entry 1:", "Entry 2:", "Entry 3:", "Entry 4:"]
        self.entry_values = []

        for label_text in entry_labels:
            label = ttk.Label(popup, text=label_text)
            label.pack(pady=5)
            entry = ttk.Entry(popup)
            entry.pack(pady=5)
            entry.pack(padx=10)
            self.entry_values.append(entry)

        ttk.Button(popup, text="Save Record", command=lambda: self.add_record_to_treeview(popup)).pack(pady=10)

    def add_record_to_treeview(self, popup):
        record_data = [entry.get() for entry in self.entry_values]

        self.master.bottom_right_frame.treeview.insert('', 'end', values=record_data)
        records.append(tuple(record_data)) 

        popup.destroy()

    def delete_selected_record(self):
        selected_items = self.master.bottom_right_frame.treeview.selection()
        for item in selected_items:
            item_values = self.master.bottom_right_frame.treeview.item(item, 'values')
            records.remove(tuple(item_values))   
            self.master.bottom_right_frame.treeview.delete(item)

class TopRightFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack(side="top", fill="both", expand=True)
        self.filter_column = 0   

        self.search_label = ttk.Label(self, text="Search:")
        self.search_label.pack(side="left", padx=5, pady=5)
        self.search_entry = ttk.Entry(self)
        self.search_entry.pack(side="left", fill="x", expand=True, padx=5, pady=5)

        self.search_entry.bind("<KeyRelease>", self.filter_treeview)

        self.remove_all_button = ttk.Button(self, text="Remove All Records", command=self.remove_all_records)
        self.remove_all_button.pack(side="right", padx=5, pady=5)

    def filter_treeview(self, event=None):
        search_query = self.search_entry.get().lower()
 
        self.master.bottom_right_frame.treeview.delete(*self.master.bottom_right_frame.treeview.get_children())
 
        for record in records:
            if search_query in record[self.filter_column].lower():  
                self.master.bottom_right_frame.treeview.insert('', 'end', values=record)

    def remove_all_records(self):
        global records
        records = []  
        self.master.bottom_right_frame.treeview.delete(*self.master.bottom_right_frame.treeview.get_children())   

    def set_filter_column(self, column):
        self.filter_column = column
        self.filter_treeview()

class BottomRightFrame(ttk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack(side="top", fill="both", expand=True)

        padding = 10
        self.treeview = ttk.Treeview(self, columns=("Column 1", "Column 2", "Column 3", "Column 4"), show="headings")
        self.treeview.pack(expand=True, fill="both", padx=padding, pady=padding)

        self.treeview.heading("Column 1", text="Name")
        self.treeview.heading("Column 2", text="Surname")
        self.treeview.heading("Column 3", text="Office Num.")
        self.treeview.heading("Column 4", text="Faculty")

        column_widths = (100, 100, 100, 100)
        for i, width in enumerate(column_widths):
            self.treeview.column(i, width=width)

def main():
    root = ThemedTk(theme="arc")
    root.geometry("700x310")

    left_frame = LeftFrame(root)
    top_right_frame = TopRightFrame(root)
    bottom_right_frame = BottomRightFrame(root)

    left_frame.master.bottom_right_frame = bottom_right_frame
    root.top_right_frame = top_right_frame

    left_frame.pack(side="left", fill="y")
    top_right_frame.pack(fill="x")
    bottom_right_frame.pack(fill="both", expand=True)

    for record in records:
        bottom_right_frame.treeview.insert('', 'end', values=record)

    root.mainloop()

if __name__ == "__main__":
    main()
