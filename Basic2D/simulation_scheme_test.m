clc; clear all; close all;
t_start = 0;
t_end   = 60;
dt      = 10/1000;

t = t_start:dt:t_end;

d_theta = [0 nan(1, length(t)-1)];
theta   = [0 nan(1, length(t)-1)];

for k = 1:length(t) - 1
    
    if (k == 50)
        impulse = .5;
    else
        impulse = 0;
    end
    
    d_theta(k+1) = d_theta(k) + dt * impulse;
    
    theta(k+1) = theta(k) + dt * d_theta(k);
end

%% Plot

figure(1);
hold on; grid on;
plot(t, theta, 'b');
plot(t, d_theta, 'r');
h = legend('$\theta$', '$\dot{\theta}$');
set(h, 'Interpreter', 'latex');


