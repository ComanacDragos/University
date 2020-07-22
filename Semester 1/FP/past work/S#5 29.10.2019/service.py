'''
1 add
2 show
3 which stars are dangerous
functionalities
'''
class Service:

    def __init__ (self):
        self._stars = []


    def addStar (self, star):
        '''
        Add the new star to the catalogue
        params:
            star - ...
        Raise ValueError if new star too close to existing ones
        '''
        for s in self._stars:
            if s.Location - star.Location < 1:
                raise ValueError ("Stars too close!")
        self._stars.append(star)

    def sortStars (self, cmp):
        '''
        Sort stars by given parameter
        params: 
            cmp - Reference to a comparator function
        Returns the sorted list of stars
        '''
        pass

    def dangerousStars (self, mass, mag):
        '''
        Returns list of dangerous stars
        params:
            mass, mag - mass and magnitude
        '''