# -*- coding: utf-8 -*- 
import tkinter as tk
from tkinter import ttk
root = tk.Tk()

def hello():
    print("Ahoj!")

hlavniMenu = tk.Menu(root)

# vytvořit rozbalovací menu a přidat ho k hlavnímu menu
menuSoubor = tk.Menu(hlavniMenu, tearoff=0)
menuSoubor.add_command(label="Otevřít", command=hello)
menuSoubor.add_command(label="Uložit", command=hello)
menuSoubor.add_separator()
menuSoubor.add_command(label="Pryč", command=root.quit)
hlavniMenu.add_cascade(label="Soubor", menu=menuSoubor)

# další rozbalovací menu
menuUpravy = tk.Menu(hlavniMenu, tearoff=0)
menuUpravy.add_command(label="Vyjmout", command=hello)
menuUpravy.add_command(label="Kopírovat", command=hello)
menuUpravy.add_command(label="Vložit", command=hello)
hlavniMenu.add_cascade(label="Upravit", menu=menuUpravy)

menuNapoveda = tk.Menu(hlavniMenu, tearoff=0)
menuNapoveda.add_command(label="O aplikaci", command=hello)
hlavniMenu.add_cascade(label="Nápověda", menu=menuNapoveda)

# zobrazení menu
root.config(menu=hlavniMenu)

root.mainloop()