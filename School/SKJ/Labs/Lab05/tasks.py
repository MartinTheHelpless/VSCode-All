import xml.etree.ElementTree as ET

def create_student(xml_root, student_id):
    '''
    Vytvořte studenta dle loginu.
    Ujistěte se, že student neexistuje, jinak: raise Exception('student already exists')
    ''' 
    existing_students = xml_root.find(f"./student[@student_id='{student_id}']")
    if existing_students is not None:
        raise Exception('student already exists')
 
    new_student = ET.SubElement(xml_root, "student")
    new_student.set("student_id", student_id)

def remove_student(xml_root, student_id):
    '''
    Odstraňte studenta dle loginu
    '''
    student = xml_root.find(f".//student[@student_id='{student_id}']")
    if student is not None:
        xml_root.remove(student)

def set_task_points(xml_root, student_id, task_id, points):
    '''
    Přepište body danému studentovi u jednoho tasku
    '''
    student = xml_root.find(f"./student[@student_id='{student_id}']")
    task = student.find(f"./task[@task_id='{task_id}']")
    if task is not None:
        task.text = str(points)

def create_task(xml_root, student_id, task_id, points):
    '''
    Pro daného studenta vytvořte task s body.
    Ujistěte se, že task (s task_id) u studenta neexistuje, jinak: raise Exception('task already exists')
    '''
    task = xml_root.find(f"./student[@student_id='{student_id}']/task[@task_id='{task_id}']")
    if task is not None:
        raise Exception('task already exists')

    student = xml_root.find(f".//student[@student_id='{student_id}']")
    task = ET.SubElement(student, "task")
    task.set("task_id", task_id)
    task.text =  str(points)

def remove_task(xml_root, task_id):
    '''
    Napříč všemi studenty smažte task s daným task_id
    '''
    for student in xml_root.findall(".//student"):
        task = student.find(f"./task[@task_id='{task_id}']")
        if task is not None:
            student.remove(task)
