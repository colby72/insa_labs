from data import *
from algorithms import *

name = input("Enter first traveler name : ")
print("--------------------------------------")
print("MAP : Towns list")
print("--------------------------------------")
i = 0
for t in towns_list:
    print(t.name, " ", end="")
    i += 1
    if i%7==0:
        print()
print("\n\n--------------------------------------")
print("Selecting the initial start town for ", name)
print("--------------------------------------")
#scountry_name = input("Enter the country's name : ")
stown_name = input("Enter the town's name : ")
print("\n--------------------------------------")
print("Selecting the destination town for ", name)
print("--------------------------------------")
#dcountry_name = input("Enter the country's name : ")
dtown_name = input("Enter the town's name : ")
print()
for t in towns_list:
    if t.name==stown_name:
        stown = t
    if t.name==dtown_name:
        dtown = t
traveler1 = Traveler(name, stown, dtown)
traveler1.update_status()

name = input("Enter second traveler name : ")
print("--------------------------------------")
"""print("MAP : Towns list")
print("--------------------------------------")
i = 0
for t in towns_list:
    print(t.name, " ", end="")
    i += 1
    if i%7==0:
        print()
print("\n\n--------------------------------------")
print("Selecting the initial start town for ", name)
print("--------------------------------------")
#scountry_name = input("Enter the country's name : ")
stown_name = input("Enter the town's name : ")
print("\n--------------------------------------")
print("Selecting the destination town for ", name)
print("--------------------------------------")
#dcountry_name = input("Enter the country's name : ")
dtown_name = input("Enter the town's name : ")"""
print()
for t in towns_list:
    if t.name==stown_name:
        stown = t
    if t.name==dtown_name:
        dtown = t
traveler2 = Traveler(name, stown, dtown)
traveler2.update_status()
traveler2.show_status()

path = find_meeting_path_min(stown, dtown)
if path==None:
    print(traveler1.name.upper(), " and ", traveler2.name.upper(), " can't meet :(")
else:
    show_path(path)
    meet_town = path[len(path)//2]
    print(traveler1.name.upper(), " and ", traveler2.name.upper(), " will be meeting in ", meet_town.name.upper())
