def test_valid_list ():
    assert valid_list ([15]) == 1
    assert valid_list (["<", 10]) == 1
    assert valid_list (["15"]) == 1
    assert valid_list ([-15]) == 0
    assert valid_list (["-15"]) == 0
    assert valid_list ([">", -10]) == 0
    assert valid_list (["="]) == 0
    assert valid_list (["=",1,2,3]) == 0
    assert valid_list (["="]) == 0
    assert valid_list([]) == 1