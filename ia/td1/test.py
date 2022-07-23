from VacuumEnvironment import *

a = ReflexVacuumAgent()
res = a.program((loc_A, 'Clean'))
print(res)
res = a.program((loc_B, 'Clean'))
print(res)
res = a.program((loc_A, 'Dirty'))
print(res)
res = a.program((loc_A, 'Dirty'))
print(res)
e = TrivialVacuumEnvironment()
e.add_thing(ModelBasedVacuumAgent())
e.run(5)
