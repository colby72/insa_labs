'''class Room:
    def __init__(self, length, width):
        self.length = length
        self.width = width'''

l = int(input("Length of the room : "))
room = [1]*l
asp_pos = l+1
while asp_pos not in [1,l]:
    asp_pos = int(input("Vaccum initial position : "))

def display_room(room):
    print("-----------------")
    print("|", end="")
    for i in room:
        if i==0:
            print(" CLEAN |", end="")
        else:
            print(" DIRTY |", end="")
    print("\n-----------------")
