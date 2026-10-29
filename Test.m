m = 1500; % mass of the vehicle
tau = 0.3; % Acutator lag time
C_d = 0.3; % Aerodynamic Drag Coefficient
A = 2.2; % Frontal Area of the vehicle
rho = 1.225; % Air Density 
C_rr = 0.3; % Rolling Resistance Coefficient
g = 9.81; % Acceleration due to gravity

v = 0; % Initial velocity
F_drive = 0; % Initial driving Force
theta = 0;
dt = 0.01; % time step

F_drag = 0.5 * rho * C_d * A * v^2;
F_roll = m * g * C_rr * cos(theta);
F_grade = m * g * sin(theta);

