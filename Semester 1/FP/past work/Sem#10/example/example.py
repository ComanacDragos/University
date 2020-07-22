# by default, classes inherit object
# object has an __str__ defined
# object has no len defined
class Animal(object):
    def __init__(self, name):
        self._name = name

    def getName (self):
        return self._name

    def __str__(self):
        return "animal: " + str(self._name) + " says " + str(self.speak())

    def speak(self):
        return None


class Cat(Animal):
    def __init__(self, name):
        super().__init__(name)

    def speak(self):
        return "meow"

c = Cat("Fluffy")
print(c)
# 1. search for Cat.__str__ -> doesn't


'''
1. You can use the code you already have in Animal
2. You can use animal and cat interchangeably

'''