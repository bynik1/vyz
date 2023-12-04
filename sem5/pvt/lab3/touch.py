# Manually calculating the solutions for both equations
import math

# Coefficients for the first equation
a1 = 1
b1 = 36
c1 = -18 * 1024**2

# Discriminant for the first equation
discriminant1 = b1**2 - 4*a1*c1

# Solutions for the first equation
n1_1 = (-b1 + math.sqrt(discriminant1)) / (2*a1)
n1_2 = (-b1 - math.sqrt(discriminant1)) / (2*a1)

# Coefficients for the second equation
a2 = 1
b2 = 2
c2 = -1024**2

# Discriminant for the second equation
discriminant2 = b2**2 - 4*a2*c2

# Solutions for the second equation
n2_1 = (-b2 + math.sqrt(discriminant2)) / (2*a2)
n2_2 = (-b2 - math.sqrt(discriminant2)) / (2*a2)

(n1_1, n1_2), (n2_1, n2_2)
