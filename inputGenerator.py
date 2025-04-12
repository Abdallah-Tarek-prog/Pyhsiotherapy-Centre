import random
from dataclasses import dataclass, field



# This is the most obnoxious piece of code I have ever written. But, it works.

@dataclass
class Treatment:
    duration: int


@dataclass
class ET(Treatment):
    def __str__(self):
        return "E"

@dataclass
class UT(Treatment):
    def __str__(self):
        return "U"

@dataclass
class XT(Treatment):
    def __str__(self):
        return "X"


@dataclass
class Patient:
    PT: int
    VT: int
    Treatments: list[Treatment] = field(default_factory=list)
    recovering: bool = False




inputFileString = ""
XRooms = random.randint(1, 10)
EDevices = random.randint(1, 10)
UDevices = random.randint(1, 10)
capacities = []
for i in range(XRooms):
    capacities.append(random.randint(1, 10))
Presc = random.randint(1, 100)
Pcancel = random.randint(1, 100)
PatientsCount = random.randint(1, 10)
Patients = []
for i in range(PatientsCount):
    p = Patient(
        PT=random.randint(1, 100),
        VT=random.randint(1, 100),
        recovering=random.randint(0, 1),
    )
    duration = random.randint(0,20)
    Ttypes = [ET, UT, XT]
    if(p.recovering): 
        p.Treatments.append(Ttypes.pop()(duration))
    else:
        p.Treatments.append(Ttypes.pop(random.randint(0, len(Ttypes)-1))(duration))
    for i in range(2):
        if(random.random() > 0.5): continue
        duration = random.randint(0,20)
        p.Treatments.append(Ttypes.pop(random.randint(0, len(Ttypes)-1))(duration))
    p.Treatments.reverse()
    Patients.append(p)

Patients.sort(key=lambda p: p.VT)

inputFileString = f"{EDevices} {UDevices} {XRooms}\n{' '.join(str(c) for c in capacities)}\n{Presc} {Pcancel}\n{PatientsCount}\n"
def getTreatmentString(tList:list[Treatment]):
    return " ".join(f"{str(t)} {t.duration}" for t in tList)
inputFileString += "\n".join(f"{['N', 'R'][p.recovering]} {p.PT} {p.VT} {len(p.Treatments)} {getTreatmentString(p.Treatments)}" for p in Patients)

print("\n", inputFileString, sep="")


with open("input.txt", "w") as f:
    file = f.write(inputFileString)
