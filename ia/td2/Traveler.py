class Traveler:
    def __init__(self, name, town, goal):
        self.name = name
        self.town = town
        self.goal = goal
        self.status = "critical"
    def show_status(self):
        print("Traveler : ", self.name.upper())
        print("Current town : ", self.town.name.upper(), " located in the ", self.town.region.upper(), " of ", self.town.country.upper())
        print("Destination town : ", self.goal.name.upper(), " located in the ", self.goal.region.upper(), " of ", self.town.country.upper())
        print("Status ", end="")
        if self.status=="critical":
            print("critical : too far away from destination :/")
        if self.status=="medium":
            print("moderated : not too far but still to go")
        if self.status=="good":
            print("good : really close to destination")
        if self.status=="perfect":
            print("perfect : destination reached :)")
    def update_status(self):
        if self.town.country!=self.goal.country:
            self.status = "critical"
        else:
            if self.town.region!=self.goal.region:
                self.status = "medium"
            else:
                if self.town.name!=self.goal.name:
                    self.status = "good"
                else:
                    self.status = "perfect"
