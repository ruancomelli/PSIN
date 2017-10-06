def multidimensional_count(multilist, dim):
	if dim > 1:
		return sum(multidimensional_count(minilist, dim-1) for minilist in multilist)
	elif dim == 1:
		return len(multilist)
	else:
		return 0