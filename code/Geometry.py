from collections import namedtuple
import math

class Point(namedtuple("_Point", "x y")):
    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)
    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)
    def __mul__(self, scalar):
        return Point(scalar * self.x, scalar * self.y)
    def __truediv__(self, scalar):
        return Point(self.x / scalar, self.y / scalar)
    __rmul__ = __mul__
    def dist2(self):
        return self.x**2 + self.y**2
    def dist(self):
        return math.sqrt(self.dist2())
    __abs__ = dist
    def theta(self):
        return math.atan2(self.y, self.x)
    def dot(self, other):
        return self.x*other.x + self.y*other.y
    def cross(self, other):
        return self.x*other.y - self.y * other.x
    def unit(self):
        return (1/abs(self)) * self
    def rotate(self, theta):
        cos_t = math.cos(theta)
        sin_t = math.sin(theta)
        return Point(self.x*cos_t - self.y*sin_t,
                     self.x*sin_t + self.y*cos_t)
    def perp(self):
        return Point(-self.y, self.x)

class Circle(namedtuple("_Circle", "center radius")):
    pass

def circle_circle_intersect(circle1, circle2):
    a, r1 = circle1
    b, r2 = circle2
    if (a == b):
        if r1 == r2:
            raise ValueError
        return []
    vec = b - a
    d2 = vec.dist2()
    sum = r1 + r2
    dif = r1 - r2
    p = (d2 + r1 * r1 - r2 * r2) / (d2 * 2)
    h2 = r1 * r1 - p * p * d2
    if sum * sum < d2 or dif * dif > d2:
        return []
    mid = a + vec * p
    per = vec.perp() * math.sqrt(max(0, h2) / d2)
    return [mid + per, mid - per]


def circle_tangents(circle1, circle2):
    """
    Get 0, 1, or 2 outer tangents as a list of pairs of points.
    Negate r2 to get the inner tangents.
    """
    c1, r1 = circle1
    c2, r2 = circle2
    d = c2 - c1
    dr = r1 - r2
    d2 = d.dist2()
    h2 = d2 - dr * dr
    if d2 == 0 or h2 < 0:
        return []
    out = []
    for sign in (-1, 1):
        v = (d * dr + d.perp() * math.sqrt(h2) * sign) / d2
        pair = (c1 + v * r1,
                c2 + v * r2)
        out.append(pair)
    if h2 == 0:
        out.pop()
    return out


def circle_line_intersect(circle, a, b):
    """a and b are endpoints"""
    assert isinstance(a, Point) and isinstance(b, Point)
    c, r = circle
    ab = b - a
    p = a + ab * (c - a).dot(ab) / ab.dist2()
    s = Point.cross(b-a, c-a)
    h2 = r*r - s * s / ab.dist2()
    if h2 < 0:
        return ()
    if h2 == 0:
        return (p,)
    h = ab.unit() * math.sqrt(h2)
    return (p - h, p + h)

def segment_intersection(seg1, seg2):
    a, b = seg1
    c, d = seg2
    oa = Point.cross(d-c, a-c)
    ob = Point.cross(d-c, b-c)
    oc = Point.cross(b-a, c-a)
    od = Point.cross(b-a, d-a)
    if on_segment(*seg1, c):
        return c
    if on_segment(*seg1, d):
        return d
    if on_segment(*seg2, a):
        return a
    if on_segment(*seg2, b):
        return b
    if oa * ob < 0 and oc * od < 0:
        return (a * ob - b * oa) / (ob - oa)
    return None
    # set < P > s;
    # if (onSegment(c, d, a)) s.insert(a);
    # if (onSegment(c, d, b)) s.insert(b);
    # if (onSegment(a, b, c)) s.insert(c);
    # if (onSegment(a, b, d)) s.insert(d);
    # return {all(s)};


def on_segment(start, end, x):
    u = start - x
    v = end - x
    return u.cross(v) == 0 and u.dot(v) <= 0

def distance_to_segment(start, end, x):
    if start == end:
        return (start-x).dist()
    d = (end-start).dist2()
    t = min(d, max(0, (x-start).dot(end-start)))
    return abs( (x-start)*d - (end-start)*t ) / d

def in_polygon(poly, point):
    """poly is a list of points"""
    wind = 0
    for i, p in enumerate(poly):
        q = poly[(i + 1) % len(poly)]
        # maybe handle on_segment here
        if p.y <= point.y:
            if q.y > point.y:
                # upward crossing
                if turnLeft(p, q, point):
                    wind += 1
        else:
            if q.y <= point.y:
                if turnLeft(q, p, point):
                    wind -= 1
    return wind


def turnLeft(p0, p1, p2):
    # Are the points counterclockwise-oriented?
    u = p1 - p0
    v = p2 - p1
    return u.cross(v) >= 0


def hull_one_side(points):
    hull = []
    for point in points:
        while len(hull) >= 2 and turnLeft(hull[-2], hull[-1], point):
            hull.pop()
        hull.append(point)
    return hull

def convex_hull(points):
    if len(points) <= 1:
        return points
    points = sorted(points)
    h1 = hull_one_side(points)
    points.reverse()
    h1.pop()
    h2 = hull_one_side(points)
    h2.pop()
    h1.extend(h2)
    return h1

def shoelace(points):
    return sum(points[i-1].cross(points[i])
               for i in range(len(points))) / 2
