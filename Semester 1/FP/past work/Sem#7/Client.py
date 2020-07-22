class Client:
    def __init__(self, clientId, name, age):
        self._clientId = clientId
        self.Name = name
        self.Age = age

    @property
    def Id(self):
        return self._clientId

    @property
    def Name(self):
        return self._name

    @Name.setter
    def Name(self, value):
        if value == None or len(value) < 3:
            raise ValueError("Client name too short")
        self._name = value

    @property
    def Age(self):
        return self._age

    @Age.setter
    def Age(self, value):
        if value == None or value < 18:
            raise ValueError("Client must be 18!")
        self._age = value

    def __eq__(self, z):
        if isinstance(z, Client) == False:
            return False
        return self.Id == z.Id

    def __str__(self):
        return "Id=" + str(self.Id) + ", Name=" + str(self.Name) + ", Age="+str(self.Age)

    def __repr__(self):
        return str(self)
