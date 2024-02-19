CODES: dict[str, str] = {
    "1": "_g_1_",
    "2": "_d_2_",
    "3": "_J_3_",
    "4": "_a_4_",
    "5": "_V_5_",
    "6": "_v_6_",
    "7": "_D_7_",
    "8": "_u_8_",
    "9": "_Y_9_",
}

def unicode_to_str(s: str) -> str:
    val: str = str(ord(s))
    out: str = ""
    for i in val:
        out += CODES[i]
    return out

def reverse_unicode(s: str) -> str:
    reversed_codes: dict[str, str] = {v: k for k, v in CODES.items()}
    val: str = ""
    
    def something(code):
        nonlocal val, s
        if s.startswith(code):
            val += reversed_codes[code]
            s = s[len(code):]

    def iterwe():
        nonlocal s
        yield True if s else False
    
    while s:
        [something(code) for code in reversed_codes]

    return chr(int(val))
import numpy as np
import matplotlib.pyplot as plt

# Given data from the chart
times = np.array([1.46, 1.50, 1.64, 1.70, 1.87, 2.04, 2.17, 2.42])  # times in seconds
masses = np.array([900, 1000, 1100, 1250, 1500, 1750, 2000, 2500])  # masses in grams

# Converting masses to kilograms
masses_kg = masses / 1000

# Distance covered is 1.00 meters for all trials
distance = 1.00  # in meters

# Using kinematic equation: distance = (initial_velocity * time) + (0.5 * acceleration * time^2)
# Here, initial_velocity = 0 (starting from rest), so we can solve for acceleration as:
# distance = (0.5 * acceleration * time^2) => acceleration = 2 * distance / time^2

# Calculate accelerations for each mass
accelerations = 2 * distance / times**2

# Graph 1: Acceleration vs. Total Mass
plt.figure(figsize=(10, 6))
plt.plot(masses_kg, accelerations, 'o-', label='Acceleration vs. Mass')
plt.title('Acceleration vs. Total Mass')
plt.xlabel('Total Mass (kg)')
plt.ylabel('Acceleration (m/s^2)')
plt.grid(True)
plt.legend()
plt.savefig('acceleration_vs_mass.png')
plt.close()

# Graph 2: Acceleration vs. 1/Total Mass
inverse_masses = 1 / masses_kg
plt.figure(figsize=(10, 6))
plt.plot(inverse_masses, accelerations, 'o-', label='Acceleration vs. 1/Mass')
plt.title('Acceleration vs. 1/Total Mass')
plt.xlabel('1/Total Mass (1/kg)')
plt.ylabel('Acceleration (m/s^2)')
plt.grid(True)
plt.legend()
plt.savefig('acceleration_vs_inverse_mass.png')
plt.close()

# Graph 3: 1/Acceleration vs. Total Mass
inverse_accelerations = 1 / accelerations
plt.figure(figsize=(10, 6))
plt.plot(masses_kg, inverse_accelerations, 'o-', label='1/Acceleration vs. Mass')
plt.title('1/Acceleration vs. Total Mass')
plt.xlabel('Total Mass (kg)')
plt.ylabel('1/Acceleration (s^2/m)')
plt.grid(True)
plt.legend()
plt.savefig('inverse_acceleration_vs_mass.png')
plt.close()

# Return the paths to the saved graphs
graph_paths = {
    "acceleration_vs_mass": "acceleration_vs_mass.png",
    "acceleration_vs_inverse_mass": "acceleration_vs_inverse_mass.png",
    "inverse_acceleration_vs_mass": "inverse_acceleration_vs_mass.png"
}

graph_paths, accelerations

