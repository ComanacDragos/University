import unittest
from Obstruction.controller.validator import *

class test_validator (unittest.TestCase):
    def test_natural_number(self):
        validator = Validator()
        validator.natural_number(3)

        with self.assertRaises(BadMove):
            validator.natural_number(3.1)

        with self.assertRaises(BadMove):
            validator.natural_number(-3)

        with self.assertRaises(BadMove):
            validator.natural_number("asd")

if __name__ == '__main__':
    unittest.main()
