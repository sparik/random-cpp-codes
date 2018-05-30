import numpy as np

T_MIN = 1
T_MAX = 20

P_MIN = 1
P_MAX = 500

Z_MIN = 1
Z_MAX = 20

S_MIN = 1
S_MAX = 10000


enough_space = False

while not enough_space:
    T = np.random.randint(T_MIN, T_MAX + 1)
    P = np.random.randint(P_MIN, P_MAX + 1)
    Z = np.random.randint(Z_MIN, Z_MAX + 1)
    S = np.random.randint(S_MIN, S_MAX + 1)

    if T + P + Z <= (2 * S + 1) * (2 * S + 1):
        enough_space = True


city_size = (2 * S + 1) * (2 * S + 1)

choices = np.random.choice(city_size, T + P + Z, replace=False)

t_coords = []
p_coords = []
z_coords = []

def to_xy(num):
    x = num // (2 * S + 1)
    y = num % (2 * S + 1)
    
    x -= S
    y -= S

    return (x, y)

for i in range(T):
    t_coords.append(to_xy(choices[i]))

for i in range(T, T + P):
    p_coords.append(to_xy(choices[i]))

for i in range(T + P, T + P + Z):
    z_coords.append(to_xy(choices[i]))


print(T)
for i in range(T):
    print(t_coords[i][0], t_coords[i][1])

print(P)
for i in range(P):
    print(p_coords[i][0], p_coords[i][1])

print(Z)
for i in range(Z):
    print(z_coords[i][0], z_coords[i][1])
