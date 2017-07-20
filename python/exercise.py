flatten_lst = lambda lst:[m for n_lst in lst for m in flatten_lst(n_lst)] if type(lst) is list else [lst]
print(flatten_lst([1,['a','b'],['c','d',['e','f']],56,78]))