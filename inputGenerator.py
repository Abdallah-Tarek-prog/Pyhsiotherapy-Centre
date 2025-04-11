import random
from dataclasses import dataclass

# 3 1 2 
# 10 5 
# 10 30 
# 4 
# N 30 25 3 E 5 U 12 X 10 
# R 30 35 3 U 6 E 5 X 10 
# R 50 40 1 X 5 
# N 40 40 2 X 15 U 10
@dataclass
class Treatment:
    duration:int

@dataclass
class ET(Treatment):
    pass
@dataclass
class UT(Treatment):
    duration:int
@dataclass
class XT(Treatment):
    duration:int

@dataclass
class Patient:
    recovering:bool = False
    PT:int
    VT:int
    Treatments:list[Treatment]


with open("input.txt", "w") as f:
    file = f.read()

inputFileString = ""
XRooms = random.randint(1, 10)
EDevices = random.randint(1, 10)
UDevices = random.randint(1, 10)
capacities = []
for i in range(XRooms):
    capacities.append(random.randint(1,10))
Presc = random.randint(1,100)
Pcancel = random.randint(1,100)
PatientsCount = random.randint(1,100)
Patients = []
for i in range(PatientsCount):
    p = Patient(
        recovering=random.randint(0,1),
        PT= random.randint(1, 100),
        VT= random.randint(1, 100),
    )
    