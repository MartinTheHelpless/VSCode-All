import xml.etree.ElementTree as ET
import random

# vytvoření kořene struktury (třída Element)
# <class class_id='SKJ-2021S'>...</class>
root = ET.Element('class', class_id='SKJ-2021S')

for student_name in ['ABC0123','DEF4567','GHI8901','JKL2345','MNO6789','PQR0123']:
	# každého studenta přidám ke kořenu struktury
	# <student student_id="ABC0123">...</student>
	student = ET.SubElement(root, 'student', student_id=student_name)

	for task_id in range(8):
		# každému studentovi vytvořím úkoly s ohodnocením
		# celkem je v předmětu 8 úkolů k vypracování
		# <task task_id="1">...</task>
		task = ET.SubElement(student, 'task', task_id=str(task_id+1))

		# nastaví hodnotu / text tagu na random hodnotu mezi 0...5
		# <task task_id="8">3</task>
		task.text = str(random.randint(0,5))

# zaobalení třídy Element do třídy ElementTree,
# která podporuje serializaci do souboru
tree = ET.ElementTree(root)
tree.write('skj_class.xml')