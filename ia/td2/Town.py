class Town:
    def __init__(self, name, region="centre", country="romania"):
        self.name = name
        self.distances = {}
        self.region = region
        self.country = country
    def add_distance(town, dist):
        self.distances[town] = dist
