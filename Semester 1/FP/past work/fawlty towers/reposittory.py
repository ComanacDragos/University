from domain import *


class RoomRepository:
    def __init__(self):
        self.rooms = []
        self.load_file()

    def load_file (self):
        f = open("file.txt", "r")
        lines = f.readlines()
        for i in lines:
            i = i.strip()
            i = i.split(",")
            r = Room(i[0], i[1])
            self.rooms.append(r)
            print(r)


class ReservationRepository():
    def __init__(self, RoomRepository):
        self.roomRepo = RoomRepository
        self.reservations = []
        self.load_file()

    @staticmethod
    def create_date (self, dd, mm):
        d = date(2018, mm, dd)
        return d


    def load_file (self):
        f = open("reservations.txt", "r")
        lines = f.readlines()
        for i in lines:
            i = i.strip().split(",")


ReservationRepository([])