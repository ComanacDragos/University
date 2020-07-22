def has_character_map(str1, str2):
    if len(str1) != len(str2):
        return False
    cont = 0
    n = len(str1)
    dict = {}
    while cont < n:
        if str1[cont] in dict:
            if dict[str1[cont]] != str2[cont]:
                return False
        dict[str1[cont]] = str2[cont]
        cont = cont + 1
    return True



print(has_character_map('abc', 'def'))
# True
print(has_character_map('aac', 'def'))
# False
