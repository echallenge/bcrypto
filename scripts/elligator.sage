#!/usr/bin/sage

var('a b z c gz x y u')

def solve2(x, y, simple = True):
  if simple:
    return map(lambda x: x.full_simplify(), solve(x, y))[0]
  return solve(x, y)[0]

print('Testing the complexity of elligator inversions.')
print('')
print('Generated with scripts/elligator.sage.')
print('')
print('---')
print('')

print('Icart\'s Method (not invertible):')
print('')
print('v = (3 * a - u^4) / (6 * u)')
print('x = (v^2 - b - (u^6 / 27))^(1 / 3) + (u^2 / 3)')
print('')
print(solve2((((3 * a - u^4) / (6 * u))^2 - b - (u^6 / 27))^(1 / 3) + (u^2 / 3) == x, u))
print('')

print('---')
print('')

print('Generalized SSWU (8 preimages):')
print('')
print('x1 = (-b / a) * (1 + (1 / (z^2 * u^4 + z * u^2)))')
print('x2 = z * u^2 * x1')
print('')
print(solve2((-b / a) * (1 + (1 / (z^2 * u^4 + z * u^2))) == x, u, False))
print(solve2(z * u^2 * ((-b / a) * (1 + (1 / (z^2 * u^4 + z * u^2)))) == x, u, False))
print('')

print('Generalized SSWU Unsquared (4 preimages):')
print('')
print('x1 = (-b / a) * (1 + (1 / (z^2 * u^2 + z * u)))')
print('x2 = z * u * x1')
print('')
print(solve2((-b / a) * (1 + (1 / (z^2 * u^2 + z * u))) == x, u))
print(solve2(z * u * ((-b / a) * (1 + (1 / (z^2 * u^2 + z * u)))) == x, u))
print('')

print('Simple SSWU (8 preimages):')
print('')
print('x1 = (-b / a) * (1 + (1 / (u^4 - u^2)))')
print('x2 = -u^2 * x1')
print('')
print(solve2((-b / a) * (1 + (1 / (u^4 - u^2))) == x, u, False))
print(solve2(-u^2 * (-b / a) * (1 + (1 / (u^4 - u^2))) == x, u, False))
print('')

print('Simple SSWU Unsquared (4 preimages):')
print('')
print('x1 = (-b / a) * (1 + (1 / (u^2 - u)))')
print('x2 = -u * x1')
print('')
print(solve2((-b / a) * (1 + (1 / (u^2 - u))) == x, u))
print(solve2(-u * (-b / a) * (1 + (1 / (u^2 - u))) == x, u))
print('')

print('---')
print('')

print('Generalized SVDW (8 preimages):')
print('')
print('t1 = u^2 + g(z)')
print('t2 = 1 / (u^2 * t1)')
print('t3 = u^4 * t2 * c')
print('x1 = ((c - z) / 2) - t3')
print('x2 = t3 - ((c + z) / 2)')
print('x3 = z - (t1^3 * t2 / (3 * z^2))')
print('')
print(solve2(((c - z) / 2) - (u^4 * (1 / (u^2 * (u^2 + gz))) * c) == x, u))
print(solve2((u^4 * (1 / (u^2 * (u^2 + gz))) * c) - ((c + z) / 2) == x, u))
print(solve2(z - ((u^2 + gz)^3 * (1 / (u^2 * (u^2 + gz))) / (3 * z^2)) == x, u))
print('')

print('Generalized SVDW Unsquared (4 preimages):')
print('')
print('t1 = u + g(z)')
print('t2 = 1 / (u * t1)')
print('t3 = u^2 * t2 * c')
print('x1 = ((c - z) / 2) - t3')
print('x2 = t3 - ((c + z) / 2)')
print('x3 = z - (t1^3 * t2 / (3 * z^2))')
print('')
print(solve2(((c - z) / 2) - (u^2 * (1 / (u * (u + gz))) * c) == x, u))
print(solve2((u^2 * (1 / (u * (u + gz))) * c) - ((c + z) / 2) == x, u))
print(solve2(z - ((u + gz)^3 * (1 / (u * (u + gz))) / (3 * z^2)) == x, u))
print('')

print('Simple SVDW (8 preimages):')
print('')
print('x1 = (-1 + c) / 2 - (c * u^2) / (1 + b + u^2)')
print('x2 = (-1 - c) / 2 + (c * u^2) / (1 + b + u^2)')
print('x3 = 1 - (1 + b + u^2)^2 / (3 * u^2)')
print('')
print(solve2((-1 + c) / 2 - (c * u^2) / (1 + b + u^2) == x, u))
print(solve2((-1 - c) / 2 + (c * u^2) / (1 + b + u^2) == x, u))
print(solve2(1 - (1 + b + u^2)^2 / (3 * u^2) == x, u))
print('')

print('Simple SVDW Unsquared (4 preimages):')
print('')
print('x1 = (-1 + c) / 2 - (c * u) / (1 + b + u)')
print('x2 = (-1 - c) / 2 + (c * u) / (1 + b + u)')
print('x3 = 1 - (1 + b + u)^2 / (3 * u)')
print('')
print(solve2((-1 + c) / 2 - (c * u) / (1 + b + u) == x, u))
print(solve2((-1 - c) / 2 + (c * u) / (1 + b + u) == x, u))
print(solve2(1 - (1 + b + u)^2 / (3 * u) == x, u))
print('')

print('---')
print('')

print('Elligator 1')
print('')
print('TODO')
print('')

print('---')
print('')

print('Elligator 2 (4 preimages, though 2 in practice)')
print('')
print('x1 = -a / (1 + z * u^2)')
print('x2 = -x1 - a')
print('')
print(solve2(-a / (1 + z * u^2) == x, u))
print(solve2(-(-a / (1 + z * u^2)) - a == x, u))
print('')

print('---')
print('')

print('Elligator 2 Ristretto (4 preimages)')
print('')
print('r = i * r0^2')
print('ns = a * (r + 1) * (a + d) * (d - a)')
print('c = -1')
print('D = (d * r - a) * (a * r - d)')
print('s = sqrt(ns / D)')
print('s\' = s * r0')
print('s\' = -s\' if not negative')
print('s = s\' if not square')
print('c = r if not square')
print('nt = c * (r - 1) * (d + a)^2 - D')
print('w0 = 2 * s * D')
print('w1 = nt * sqrt(a * d - 1)')
print('w2 = 1 + a * s^2')
print('w3 = 1 - a * s^2')
print('x = w0 * w3')
print('y = w2 * w1')
print('z = w1 * w3')
print('t = w0 * w2')
print('')
var('d s r D r0 i nt')
# Note that w1 and w3 are necessarily 1 if the point is affinized.
# Convert back to jacobi quartic.
print(solve2((1 + a * s^2) == y, s))
print(solve2(2 * s * D == x, D))
# We can now recalculate x as:
print('x2 = 2*s*D')
# We can then check the sign against the point and negate D if necessary.
print(solve2(((d * r - a) * (a * r - d)) == D, r))
print(solve2(c * (r - 1) * (d + a)^2 - D == nt, c))
print(solve2(i * r0^2 == r, r0))
