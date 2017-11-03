import numpy as np

def intersect_with_xy(normalVector, origin):
	xy_normal_versor = [0, 0, 1]

	a = normalVector[0]
	b = normalVector[1]
	c = normalVector[2]
	d = np.dot(normalVector, origin)

	director = list(np.cross(normalVector, xy_normal_versor))
	director = director[0:2]

	if a != 0:
		point = [d/a, 0]
	else:
		point = [0, d/b]

	line = (director, point)

	return line

def isInside(point, limits):
	(xmin, xmax, ymin, ymax) = limits
	(x, y) = point

	return xmin <= x and x <= xmax and ymin <= y and y <= ymax

def getExtremes(line, limits):
	(xmin, xmax, ymin, ymax) = limits

	begin = (0, 0)
	end = (0, 0)

	(director, point) = line

	u = director[0]
	v = director[1]

	x = point[0]
	y = point[1]

	if u == 0:
		begin = (x, ymin)
		end = (x, ymax)

		return (isInside(begin, limits) and isInside(end, limits), begin, end)
	elif v == 0:
		begin = (xmin, y)
		end = (xmax, y)

		return (isInside(begin, limits) and isInside(end, limits), begin, end)

	a = v/u
	b = y - v*x/u
	# y = a*x + b

	xmin_intersect = (xmin, a*xmin + b)
	xmax_intersect = (xmax, a*xmax + b)
	ymin_intersect = ((ymin-b)/a, ymin)
	ymax_intersect = ((ymax-b)/a, ymax)

	if isInside(xmin_intersect, limits):
		begin = xmin_intersect

		if isInside(xmax_intersect, limits):
			end = xmax_intersect
			return (True, begin, end)

		if isInside(ymin_intersect, limits):
			end = ymin_intersect
			return (True, begin, end)

		if isInside(ymax_intersect, limits):
			end = ymax_intersect
			return (True, begin, end)

	elif isInside(xmax_intersect, limits):
		begin = xmax_intersect

		if isInside(ymin_intersect, limits):
			end = ymin_intersect
			return (True, begin, end)

		if isInside(ymax_intersect, limits):
			end = ymax_intersect
			return (True, begin, end)

	elif isInside(ymin_intersect, limits):
		begin = ymin_intersect

		if isInside(ymax_intersect, limits):
			end = ymax_intersect
			return (True, begin, end)

	else:
		return (False, begin, end)

def getIntersectPoints(normalVector, origin, limits):
	line = intersect_with_xy(normalVector, origin)
	return getExtremes(line, limits)