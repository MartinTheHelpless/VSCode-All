import xml.etree.ElementTree as ET

# Vytvoření nodu v XML
e = ET.Element('tag', {'key1':'val1'}, key2='val2')
e.tag
e.attrib
e.text
e.set('attrib','value')
e.get('attrib')

# XML 2 string
ET.tostring(e)

# String 2 XML
se = ET.fromstring('<string attrib="value">text</string>')

# Přidání potomka rodiči
se = ET.SubElement(e, 'tag', {'key1':'val1'}, key2='val2')
se = ET.Element('tag', {'key1':'val1'}, key2='val2')
e.append(se)

# Iterace přes potomky
for se in e: pass # všichni přímí potomci
for se in e.iter('tag'): pass # rekurzivně všichni potomci s tagem
for se in e.findall('tag'): pass # přímí potomci s tagem

#nalezení potomka
se = e.find('tag') # první potomek s tagem

# Odstranění potomka
e.remove(se)